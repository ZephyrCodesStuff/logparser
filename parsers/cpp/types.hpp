#pragma once

#include <cstdint>
#include <string>
#include <vector>

struct Field {
    std::string name;
    std::string type;
    std::string unit;
    std::vector< std::string > data;  // store as strings for simple CSV output
};

struct Device {
    std::string name;
    uint32_t id;
    std::vector< Field > fields;
};

struct Section {
    size_t offset;
    size_t length;
};

// compute entry size for a device
size_t calc_entry_size( const Device& dev );
size_t typename_to_size( const std::string& type );
std::string read_field_as_string( const uint8_t* ptr, const std::string& type );
