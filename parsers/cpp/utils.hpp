#pragma once

#include <cstdint>
#include <cstring>

template < typename T >
T read_le( const uint8_t* ptr )
{
    T v;
    std::memcpy( &v, ptr, sizeof( T ) );
    return v;
}
