#include <atomic>
#include <iostream>
#include <thread>

#include "parallelism.hpp"
#include "types.hpp"
#include "utils.hpp"

ParsedSection parse_section(
    const uint8_t* data, size_t length,
    const std::unordered_map< uint32_t, size_t >& id2idx,
    const std::vector< Device >& devices )
{
    ParsedSection result{ 0, {}, false };

    // each section must be at least 5 bytes (4-byte id + 1-byte checksum)
    if ( length < 5 ) return result;

    // checksum is last byte (XOR of all previous bytes)
    uint8_t cs = 0;
    for ( size_t i = 0; i + 1 < length; ++i )
        cs ^= data[i];
    if ( cs != data[length - 1] ) return result;

    uint32_t id = read_le< uint32_t >( data );
    auto it = id2idx.find( id );
    if ( it == id2idx.end() ) return result;

    result.device_id = id;
    const Device& dev = devices[it->second];
    size_t entrySize = calc_entry_size( dev );
    if ( entrySize == 0 ) return result;

    size_t payload_len = length - 1 - 4;  // remove checksum and id
    size_t num_entries = payload_len / entrySize;
    const uint8_t* cursor = data + 4;

    result.entries.reserve( num_entries );

    for ( size_t e = 0; e < num_entries; ++e )
    {
        std::vector< std::string > entry;
        entry.reserve( dev.fields.size() );

        const uint8_t* p = cursor + e * entrySize;
        for ( size_t f = 0; f < dev.fields.size(); ++f )
        {
            const auto& ftype = dev.fields[f].type;
            entry.push_back( read_field_as_string( p, ftype ) );
            p += typename_to_size( ftype );
        }
        result.entries.push_back( std::move( entry ) );
    }

    result.valid = true;
    return result;
}

// Lock-free parallel processing using per-thread buffers
void process_sections_parallel(
    const std::vector< uint8_t >& fileBytes,
    const std::vector< Section >& sections,  // Using offset-based sections
    std::vector< Device >& devices,
    const std::unordered_map< uint32_t, size_t >& id2idx, unsigned num_threads )
{
    if ( num_threads == 0 ) num_threads = std::thread::hardware_concurrency();

    std::atomic< size_t > corrupt_count{ 0 };
    std::atomic< size_t > next_section{ 1 };  // Skip header section

    // Per-thread results - no locking needed!
    std::vector< ThreadResults > threadResults;
    threadResults.reserve( num_threads );
    for ( unsigned i = 0; i < num_threads; ++i )
        threadResults.emplace_back( devices.size() );

    auto worker = [&]( unsigned thread_id ) {
        ThreadResults& myResults = threadResults[thread_id];

        while ( true )
        {
            size_t si = next_section.fetch_add( 1 );
            if ( si >= sections.size() ) break;

            const auto& sec = sections[si];
            const uint8_t* data = fileBytes.data() + sec.offset;

            ParsedSection parsed =
                parse_section( data, sec.length, id2idx, devices );

            if ( !parsed.valid )
            {
                corrupt_count.fetch_add( 1 );
                continue;
            }

            // Add to thread-local buffer (no locking!) with sequence key
            auto it = id2idx.find( parsed.device_id );
            if ( it != id2idx.end() )
            {
                size_t device_idx = it->second;
                // Each entry keeps its index within the section; combine with section index
                uint64_t section_idx = static_cast< uint64_t >( si );
                for ( size_t entry_idx = 0; entry_idx < parsed.entries.size();
                      ++entry_idx )
                {
                    uint64_t seq_key = ( section_idx << 32 ) |
                                       static_cast< uint64_t >( entry_idx );
                    myResults.add_entry( device_idx, seq_key,
                                         parsed.entries[entry_idx] );
                }
            }
        }
    };

    // Launch threads
    std::vector< std::thread > threads;
    threads.reserve( num_threads );
    for ( unsigned i = 0; i < num_threads; ++i )
        threads.emplace_back( worker, i );

    // Wait for completion
    for ( auto& t : threads )
        t.join();
    // Merge results (single-threaded, no contention) preserving sequence order
    for ( size_t dev_idx = 0; dev_idx < devices.size(); ++dev_idx )
    {
        // Collect all (seq_key, entry) pairs from all threads
        std::vector< std::pair< uint64_t, const std::vector< std::string >* > >
            allEntries;
        for ( const auto& threadResult : threadResults )
        {
            const auto& buf = threadResult.deviceBuffers[dev_idx];
            allEntries.reserve( allEntries.size() + buf.size() );
            for ( const auto& p : buf )
                allEntries.emplace_back( p.first, &p.second );
        }

        // Sort by seq_key to restore global order
        std::sort(
            allEntries.begin(), allEntries.end(),
            []( const auto& a, const auto& b ) { return a.first < b.first; } );

        // Append in order
        for ( const auto& p : allEntries )
        {
            const auto& entry = *p.second;
            for ( size_t f = 0;
                  f < entry.size() && f < devices[dev_idx].fields.size(); ++f )
                devices[dev_idx].fields[f].data.push_back( entry[f] );
        }
    }

    // Optional: report corrupt sections
    if ( corrupt_count.load() > 0 )
    {
        std::cout << "Parsing done. Corrupt sections: " << corrupt_count.load()
                  << "\n";
    }
}
