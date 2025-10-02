#pragma once

#ifdef _WIN32
    #include <windows.h>
#else
    #include <fcntl.h>
    #include <sys/mman.h>
    #include <sys/stat.h>
    #include <unistd.h>
#endif

#include <cstdint>
#include <filesystem>
#include <stdexcept>
#include <string>

namespace fs = std::filesystem;

// Simple RAII wrapper for a read-only memory-mapped file
class MappedFile {
   public:
    MappedFile( const fs::path& path ) : map_( nullptr ), size_( 0 )
    {
        std::string p = path.string();
#ifdef _WIN32
        HANDLE h = CreateFileA( p.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL,
                                OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL );
        if ( h == INVALID_HANDLE_VALUE )
            throw std::runtime_error( "Failed to open file" );
        LARGE_INTEGER li;
        if ( !GetFileSizeEx( h, &li ) )
        {
            CloseHandle( h );
            throw std::runtime_error( "Failed to stat file" );
        }
        size_ = static_cast< size_t >( li.QuadPart );
        HANDLE fm = CreateFileMappingA( h, NULL, PAGE_READONLY, 0, 0, NULL );
        if ( !fm )
        {
            CloseHandle( h );
            throw std::runtime_error( "CreateFileMapping failed" );
        }
        map_ = MapViewOfFile( fm, FILE_MAP_READ, 0, 0, 0 );
        CloseHandle( fm );
        CloseHandle( h );
        if ( !map_ && size_ > 0 )
            throw std::runtime_error( "MapViewOfFile failed" );
#else
        int fd = open( p.c_str(), O_RDONLY );
        if ( fd < 0 ) throw std::runtime_error( "Failed to open file" );
        struct stat st;
        if ( fstat( fd, &st ) != 0 )
        {
            close( fd );
            throw std::runtime_error( "fstat failed" );
        }
        size_ = static_cast< size_t >( st.st_size );
        if ( size_ > 0 )
        {
            map_ = mmap( nullptr, size_, PROT_READ, MAP_PRIVATE, fd, 0 );
            if ( map_ == MAP_FAILED )
            {
                close( fd );
                throw std::runtime_error( "mmap failed" );
            }
        } else {
            map_ = nullptr;
        }
        close( fd );
#endif
    }

    ~MappedFile()
    {
#ifdef _WIN32
        if ( map_ ) UnmapViewOfFile( map_ );
#else
        if ( map_ ) munmap( map_, size_ );
#endif
    }

    const uint8_t* data() const
    {
        return static_cast< const uint8_t* >( map_ );
    }
    size_t size() const { return size_; }

   private:
    void* map_;
    size_t size_;
};
