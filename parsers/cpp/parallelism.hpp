#pragma once

#include <unordered_map>
#include <vector>

#include "types.hpp"

// Parse a single section (thread-safe, no locking needed)
struct ParsedSection {
    uint32_t device_id;
    std::vector< std::vector< std::string > > entries;  // [entry][field]
    bool valid;
};

// Per-thread result buffer (no locking needed)
struct ThreadResults {
    std::vector< std::vector< std::vector< std::string > > >
        deviceBuffers;  // [device][entry][field]

    ThreadResults( size_t num_devices ) : deviceBuffers( num_devices ) {}

    void add_entry( size_t device_idx, const std::vector< std::string >& entry )
    {
        deviceBuffers[device_idx].push_back( entry );
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
