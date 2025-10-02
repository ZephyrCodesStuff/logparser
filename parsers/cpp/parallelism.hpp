#pragma once
#pragma once

#include <cstdint>
#include <unordered_map>
#include <utility>
#include <vector>

#include "types.hpp"

// Parse a single section (thread-safe, no locking needed)
struct ParsedSection {
    uint32_t device_id;
    std::vector< std::vector< std::string > > entries;  // [entry][field]
    bool valid;
};

// Per-thread result buffer (no locking needed)
// We store a sequence key with each entry so we can merge them in the
// original section/entry order at the end. The key is a 64-bit value
// where the high 32 bits are the section index and the low 32 bits
// are the entry index within the section.
struct ThreadResults {
    // [device][ (seq_key, entry) ]
    std::vector<
        std::vector< std::pair< uint64_t, std::vector< std::string > > > >
        deviceBuffers;

    ThreadResults( size_t num_devices ) : deviceBuffers( num_devices ) {}

    void add_entry( size_t device_idx, uint64_t seq_key,
                    const std::vector< std::string >& entry )
    {
        deviceBuffers[device_idx].emplace_back( seq_key, entry );
    }
};

// Function declarations
ParsedSection parse_section(
    const uint8_t* data, size_t length,
    const std::unordered_map< uint32_t, size_t >& id2idx,
    const std::vector< Device >& devices );

void process_sections_parallel(
    const std::vector< uint8_t >& fileBytes,
    const std::vector< Section >& sections, std::vector< Device >& devices,
    const std::unordered_map< uint32_t, size_t >& id2idx,
    unsigned num_threads = 0 );
