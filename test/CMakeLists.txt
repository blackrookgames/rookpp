cmake_minimum_required(VERSION 3.16)

project(test VERSION 1.0.0.0
    DESCRIPTION "test by Black Rook Games"
    LANGUAGES CXX)

cmake_path(ABSOLUTE_PATH CMAKE_SOURCE_DIR OUTPUT_VARIABLE cmakedir)

if(WIN32)
    message("Detected Windows")
    add_compile_definitions(__OS_WIN32__)
    set(rookxx_f "librookxx.dll")
elseif(UNIX)
    message("Detected Unix")
    add_compile_definitions(__OS_UNIX__)
    set(rookxx_f "librookxx.so")
else()
    message("Unknown OS")
    set(rookxx_f "")
endif()

set(rookxx_d "${cmakedir}/../rookxx")

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

add_custom_target(PreBuildSetup
    COMMAND ${CMAKE_COMMAND} -E echo "Running pre-build setup script..."
    COMMAND bash ${cmakedir}/CMakeLists.copy.sh 
        "${CMAKE_CURRENT_BINARY_DIR}/Debug" 
        "${rookxx_d}/build/Debug/${rookxx_f}"
    COMMENT "Executing pre-build setup tasks"
)

add_executable(test main.cpp ${src_src} ${src_hdr})
add_dependencies(test PreBuildSetup)
target_include_directories(test PUBLIC hdr)
target_include_directories(test PUBLIC "${rookxx_d}/hdr")
target_link_directories(test PUBLIC "${rookxx_d}/build/Debug")
target_link_libraries(test PUBLIC "${rookxx_f}")