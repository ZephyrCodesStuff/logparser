cmake_minimum_required(VERSION 3.15)
project(logfile_parser_cpp LANGUAGES CXX)

# Make our local cmake modules (including FindANTLR.cmake) discoverable
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/../../antlr4/runtime/Cpp/cmake")

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

# Prefer local prebuilt C++ runtime if present (lib + headers)
if(NOT ANTLR_RUNTIME_LIBRARY AND NOT ANTLR_LIBRARY)
    set(_local_runtime_lib "${CMAKE_CURRENT_LIST_DIR}/../../antlr4/runtime/Cpp/dist/libantlr4-runtime.dylib")
    set(_local_runtime_inc "${CMAKE_CURRENT_LIST_DIR}/../../antlr4/runtime/Cpp/runtime/src")
    if(EXISTS "${_local_runtime_lib}" AND EXISTS "${_local_runtime_inc}")
        set(ANTLR_RUNTIME_LIBRARY "${_local_runtime_lib}" CACHE FILEPATH "Path to ANTLR C++ runtime library" FORCE)
        set(ANTLR_RUNTIME_INCLUDE_DIR "${_local_runtime_inc}" CACHE PATH "Path to ANTLR C++ runtime include dir" FORCE)
    endif()
endif()

# Find ANTLR runtime (expects a FindANTLR.cmake in the module path)
find_package(ANTLR REQUIRED)

# Add your executable
add_executable(main main.cpp)

# Modern C++ settings
set_target_properties(main PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

# Link to the ANTLR runtime. Support several possible Find module conventions.
if(TARGET ANTLR4::Runtime)
    target_link_libraries(main PRIVATE ANTLR4::Runtime)
elseif(TARGET ANTLR::Runtime)
    target_link_libraries(main PRIVATE ANTLR::Runtime)
elseif(DEFINED ANTLR_RUNTIME_LIBRARY)
    target_link_libraries(main PRIVATE ${ANTLR_RUNTIME_LIBRARY})
elseif(DEFINED ANTLR_LIBRARY)
    target_link_libraries(main PRIVATE ${ANTLR_LIBRARY})
else()
    message(FATAL_ERROR "ANTLR runtime target or variables not found. Verify FindANTLR.cmake")
endif()

# Add include directories if the find module provided them
if(DEFINED ANTLR_RUNTIME_INCLUDE_DIR)
    target_include_directories(main PRIVATE ${ANTLR_RUNTIME_INCLUDE_DIR})
elseif(DEFINED ANTLR_INCLUDE_DIRS)
    target_include_directories(main PRIVATE ${ANTLR_INCLUDE_DIRS})
endif()

# Configure ANTLR-generated sources from `./gen`
if(EXISTS "${CMAKE_CURRENT_LIST_DIR}/gen/SensorLog.g4")
    ANTLR_TARGET(LogfileParser "${CMAKE_CURRENT_LIST_DIR}/gen/SensorLog.g4"
        PACKAGE logfile
        OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/gen"
        DEPENDS_ANTLR
    )

    add_custom_target(
        GenerateLogfileParser
        DEPENDS ${ANTLR_LogfileParser_CXX_OUTPUTS}
    )

    add_dependencies(main GenerateLogfileParser)

    target_sources(main PRIVATE ${ANTLR_LogfileParser_CXX_OUTPUTS})

    target_include_directories(main PRIVATE
        ${CMAKE_CURRENT_BINARY_DIR}/gen
    )

    if(DEFINED ANTLR_RUNTIME_INCLUDE_DIR)
        target_include_directories(main PRIVATE ${ANTLR_RUNTIME_INCLUDE_DIR})
    elseif(DEFINED ANTLR_INCLUDE_DIRS)
        target_include_directories(main PRIVATE ${ANTLR_INCLUDE_DIRS})
    endif()
else()
    message(FATAL_ERROR "Grammar file 'gen/SensorLog.g4' not found")
endif()