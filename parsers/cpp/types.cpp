#include "types.hpp"
#include <charconv>
#include <cstdio>
#include "utils.hpp"

// Fast integer to string conversion
inline std::string fast_itoa( int64_t value )
{
    char buffer[32];
    auto [ptr, ec] = std::to_chars( buffer, buffer + sizeof( buffer ), value );
    return std::string( buffer, ptr );
}

// Fast unsigned integer to string conversion
inline std::string fast_utoa( uint64_t value )
{
    char buffer[32];
    auto [ptr, ec] = std::to_chars( buffer, buffer + sizeof( buffer ), value );
    return std::string( buffer, ptr );
}

// Fast float to string conversion with controlled precision
inline std::string fast_ftoa( double value )
{
    char buffer[64];
    auto [ptr, ec] = std::to_chars( buffer, buffer + sizeof( buffer ), value,
                                    std::chars_format::general, 6 );
    if ( ec == std::errc{} ) return std::string( buffer, ptr );
    // Fallback for edge cases
    snprintf( buffer, sizeof( buffer ), "%.6g", value );
    return std::string( buffer );
}

size_t calc_entry_size( const Device& dev )
{
    size_t s = 0;
    for ( const auto& f : dev.fields )
        s += typename_to_size( f.type );
    return s;
}

size_t typename_to_size( const std::string& type )
{
    if ( type == "s8" || type == "u8" ) return 1;
    if ( type == "s16" || type == "u16" ) return 2;
    if ( type == "s32" || type == "u32" ) return 4;
    if ( type == "s64" || type == "u64" ) return 8;
    if ( type == "float" ) return sizeof( float );
    if ( type == "double" ) return sizeof( double );
    return 0;
}

// convert field value at byte buffer to string according to type
std::string read_field_as_string( const uint8_t* ptr, const std::string& type )
{
    if ( type == "u8" )
    {
        uint8_t v = read_le< uint8_t >( ptr );
        return fast_utoa( v );
    }
    if ( type == "u16" )
    {
        uint16_t v = read_le< uint16_t >( ptr );
        return fast_utoa( v );
    }
    if ( type == "u32" )
    {
        uint32_t v = read_le< uint32_t >( ptr );
        return fast_utoa( v );
    }
    if ( type == "u64" )
    {
        uint64_t v = read_le< uint64_t >( ptr );
        return fast_utoa( v );
    }
    if ( type == "s8" )
    {
        int8_t v = read_le< int8_t >( ptr );
        return fast_itoa( v );
    }
    if ( type == "s16" )
    {
        int16_t v = read_le< int16_t >( ptr );
        return fast_itoa( v );
    }
    if ( type == "s32" )
    {
        int32_t v = read_le< int32_t >( ptr );
        return fast_itoa( v );
    }
    if ( type == "s64" )
    {
        int64_t v = read_le< int64_t >( ptr );
        return fast_itoa( v );
    }
    if ( type == "float" )
    {
        float v = read_le< float >( ptr );
        return fast_ftoa( v );
    }
    if ( type == "double" )
    {
        double v = read_le< double >( ptr );
        return fast_ftoa( v );
    }
    return std::string();
}
