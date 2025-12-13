cmake_minimum_required(VERSION 3.16)

project(rookxx VERSION 1.0.0.0
    DESCRIPTION "rookxx by Black Rook Games"
    LANGUAGES CXX)

cmake_path(ABSOLUTE_PATH CMAKE_SOURCE_DIR OUTPUT_VARIABLE cmakedir)

if(WIN32)
    message("Detected Windows")
    add_compile_definitions(__OS_WIN32__)
elseif(UNIX)
    message("Detected Unix")
    add_compile_definitions(__OS_UNIX__)
else()
    message("Unknown OS")
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

set(src_src )

file(GLOB_RECURSE src_hdr "hdr/*.h")
file(GLOB_RECURSE src_src_pool "src/*.cpp")
foreach (path ${src_src_pool})
    file(RELATIVE_PATH relpath ${cmakedir} ${path})
    if (NOT ${relpath} IN_LIST src_src)
        set(src_src ${src_src} ${relpath})
    endif()
endforeach()

add_library(rookxx SHARED ${src_src} ${src_hdr})
target_include_directories(rookxx PUBLIC hdr)