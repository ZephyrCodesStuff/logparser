cmake_minimum_required(VERSION 2.8.12...3.15)
project(logfile_parser_cpp LANGUAGES CXX)

# Use the static runtime on MSVC so the produced binaries do not depend on the
# redistributable DLLs. This also matches the statically built ANTLR runtime.
if(MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()

set(_antlr_runtime_is_static OFF)

# Prefer a known Homebrew install or project-local jar if present
if(NOT ANTLR_EXECUTABLE)
    if(EXISTS "/opt/homebrew/Cellar/antlr/4.13.2/antlr-4.13.2-complete.jar")
        set(ANTLR_EXECUTABLE "/opt/homebrew/Cellar/antlr/4.13.2/antlr-4.13.2-complete.jar" CACHE FILEPATH "Path to ANTLR jar" FORCE)
    endif()
    set(_local_jar "${CMAKE_CURRENT_LIST_DIR}/../../third_party/antlr/antlr-4.13.2-complete.jar")
    if(EXISTS "${_local_jar}")
        set(ANTLR_EXECUTABLE "${_local_jar}" CACHE FILEPATH "Path to ANTLR jar" FORCE)
    endif()
endif()

# Try to find ANTLR runtime package/config first (optional). If not found,
# FetchContent will obtain the ANTLR sources and build the runtime.
find_package(ANTLR QUIET)

# If find_package didn't provide usable imported/alias targets or variables,
# try fetching the antlr4 repository via FetchContent and building the C++ runtime
# so consumers can link against a known target. This will be attempted before
# falling back to any repository-local bundled runtime sources.
if(NOT TARGET ANTLR4::Runtime AND NOT TARGET ANTLR::Runtime)

    include(FetchContent)

    # Ensure the fetched ANTLR runtime is built statically. This keeps the
    # Windows binary self-contained and avoids shipping libantlr4 DLLs.
    set(ANTLR4_BUILD_SHARED OFF CACHE BOOL "Build ANTLR4 shared runtime" FORCE)
    set(ANTLR4_BUILD_STATIC ON CACHE BOOL "Build ANTLR4 static runtime" FORCE)
    set(ANTLR4_INSTALL OFF CACHE BOOL "Skip installing ANTLR4 runtime" FORCE)
    if(MSVC)
        set(ANTLR4_WITH_STATIC_CRT ON CACHE BOOL "Link ANTLR4 runtime against the static Microsoft CRT" FORCE)
    endif()

    # Only fetch/build if we don't already have runtime variables pointing to a prebuilt lib.
    if(NOT DEFINED ANTLR_RUNTIME_LIBRARY AND NOT DEFINED ANTLR_LIBRARY)
        message(STATUS "Attempting to FetchContent antlr/antlr4 to build the C++ runtime")

        FetchContent_Declare(
            antlr4
            GIT_REPOSITORY https://github.com/antlr/antlr4.git
            GIT_TAG dev # This one has fixes not yet merged into main, as of 2025-10-16
        )

        # This will clone into the build directory and make antlr4_SOURCE_DIR available.
        FetchContent_MakeAvailable(antlr4)

        # Make ANTLR CMake helper macros discoverable if provided by the fetched source.
        if(DEFINED antlr4_SOURCE_DIR)
            set(_antlr_cmake_dir "${antlr4_SOURCE_DIR}/runtime/Cpp/cmake")
            if(EXISTS "${_antlr_cmake_dir}")
                list(APPEND CMAKE_MODULE_PATH "${_antlr_cmake_dir}")
                # Also include any helper cmake files so macros (e.g. ANTLR_TARGET)
                # become available in this directory scope.
                file(GLOB _antlr_cmake_files "${_antlr_cmake_dir}/*.cmake")
                foreach(_cmake_file IN LISTS _antlr_cmake_files)
                    include(${_cmake_file})
                endforeach()
            endif()
        endif()

        # If the fetched project didn't already add the runtime as a target, add it explicitly.
        if(NOT (TARGET antlr4_shared OR TARGET antlr4_static))
            if(EXISTS "${antlr4_SOURCE_DIR}/runtime/Cpp/CMakeLists.txt")
                add_subdirectory("${antlr4_SOURCE_DIR}/runtime/Cpp" "${CMAKE_CURRENT_BINARY_DIR}/antlr4-runtime-fetch")

                # After adding the runtime subdirectory, ensure the runtime's cmake helpers
                # are available on CMAKE_MODULE_PATH for macros like ANTLR_TARGET.
                if(EXISTS "${antlr4_SOURCE_DIR}/runtime/Cpp/cmake")
                    list(APPEND CMAKE_MODULE_PATH "${antlr4_SOURCE_DIR}/runtime/Cpp/cmake")
                    file(GLOB _antlr_cmake_files2 "${antlr4_SOURCE_DIR}/runtime/Cpp/cmake/*.cmake")
                    foreach(_cmake_file2 IN LISTS _antlr_cmake_files2)
                        include(${_cmake_file2})
                    endforeach()
                endif()
            endif()
        endif()

        # Create alias targets matching common Find module conventions so existing code can link unchanged.
        if(TARGET antlr4_static)
            if(NOT TARGET ANTLR4::Runtime)
                add_library(ANTLR4::Runtime ALIAS antlr4_static)
            endif()
            if(NOT TARGET ANTLR::Runtime)
                add_library(ANTLR::Runtime ALIAS antlr4_static)
            endif()
            set(_antlr_runtime_is_static ON)
        elseif(TARGET antlr4_shared)
            if(NOT TARGET ANTLR4::Runtime)
                add_library(ANTLR4::Runtime ALIAS antlr4_shared)
            endif()
            if(NOT TARGET ANTLR::Runtime)
                add_library(ANTLR::Runtime ALIAS antlr4_shared)
            endif()
        else()
            message(STATUS "FetchContent provided antlr4 but runtime targets not found; will try bundled runtime or Find module variables")
        endif()
    endif()
endif()

# Add your executable
add_executable(logparser main.cpp)

# Add source files
target_sources(logparser PRIVATE
    parallelism.hpp
    parallelism.cpp
    types.hpp
    types.cpp
    utils.hpp
)

# Modern C++ settings
set_target_properties(logparser PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

# For Windows, we have to define `NOMINMAX` to prevent Windows headers from defining `min` and `max` macros.
if(MSVC)
    target_compile_definitions(logparser PRIVATE NOMINMAX)
endif()

# Link to the ANTLR runtime. Support several possible Find module conventions.
if(TARGET ANTLR4::Runtime)
    target_link_libraries(logparser PRIVATE ANTLR4::Runtime)
elseif(TARGET ANTLR::Runtime)
    target_link_libraries(logparser PRIVATE ANTLR::Runtime)
elseif(DEFINED ANTLR_RUNTIME_LIBRARY)
    target_link_libraries(logparser PRIVATE ${ANTLR_RUNTIME_LIBRARY})
elseif(DEFINED ANTLR_LIBRARY)
    target_link_libraries(logparser PRIVATE ${ANTLR_LIBRARY})
else()
    message(FATAL_ERROR "ANTLR runtime target or variables not found. Verify FindANTLR.cmake")
endif()

if(_antlr_runtime_is_static)
    target_compile_definitions(logparser PRIVATE ANTLR4CPP_STATIC)
endif()

# Add include directories if the find module provided them
if(DEFINED ANTLR_RUNTIME_INCLUDE_DIR)
    target_include_directories(logparser PRIVATE ${ANTLR_RUNTIME_INCLUDE_DIR})
elseif(DEFINED ANTLR_INCLUDE_DIRS)
    target_include_directories(logparser PRIVATE ${ANTLR_INCLUDE_DIRS})
endif()

# Configure ANTLR-generated sources from `./gen`
if(EXISTS "${CMAKE_CURRENT_LIST_DIR}/gen/SensorLog.g4")
    if(COMMAND ANTLR_TARGET)
        ANTLR_TARGET(LogfileParser "${CMAKE_CURRENT_LIST_DIR}/gen/SensorLog.g4"
            PACKAGE logfile
            OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/gen"
            DEPENDS_ANTLR
        )

        add_custom_target(
            GenerateLogfileParser
            DEPENDS ${ANTLR_LogfileParser_CXX_OUTPUTS}
        )

        add_dependencies(logparser GenerateLogfileParser)

        target_sources(logparser PRIVATE ${ANTLR_LogfileParser_CXX_OUTPUTS})

        target_include_directories(logparser PRIVATE
            ${CMAKE_CURRENT_BINARY_DIR}/gen
        )

        if(DEFINED ANTLR_RUNTIME_INCLUDE_DIR)
            target_include_directories(logparser PRIVATE ${ANTLR_RUNTIME_INCLUDE_DIR})
        elseif(DEFINED ANTLR_INCLUDE_DIRS)
            target_include_directories(logparser PRIVATE ${ANTLR_INCLUDE_DIRS})
        endif()
    else()
        message(FATAL_ERROR "ANTLR_TARGET macro not found. Ensure ANTLR CMake helpers are discoverable.\nEither install ANTLR CMake package and set ANTLR_DIR/CMAKE_PREFIX_PATH, or allow CMake to fetch antlr4 (check FetchContent and network).")
    endif()
else()
    message(FATAL_ERROR "Grammar file 'gen/SensorLog.g4' not found")
endif()