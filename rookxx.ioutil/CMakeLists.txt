cmake_minimum_required(VERSION 3.16)
project(rookxx.ioutil VERSION 1.0.0.0
    DESCRIPTION "rookxx.ioutil by Black Rook Games"
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DDEBUG")

if(WIN32)
    message("Detected Windows")
    set(libOptions "")
    set(rookxx_f "librookxx.dll")
elseif(UNIX)
    message("Detected Unix")
    set(libOptions "")
    set(rookxx_f "librookxx.so")
else()
    message("Unknown OS")
    set(libOptions "")
    set(rookxx_f "")
endif()

set(rookxx_d "${CMAKE_SOURCE_DIR}/../rookxx")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

set(src )

set(dir "")
set(src ${src} 
    hdr${dir}/IO.h src${dir}/IO.cpp)

add_custom_target(PreBuildSetup
    COMMAND ${CMAKE_COMMAND} -E echo "Running pre-build setup script..."
    COMMAND bash ${CMAKE_SOURCE_DIR}/CMakeLists.copy.sh 
        "${CMAKE_CURRENT_BINARY_DIR}/Debug" 
        "${rookxx_d}/build/Debug/${rookxx_f}" 
    COMMENT "Executing pre-build setup tasks"
)

add_library(rookxx.ioutil SHARED ${libOptions} ${src})
add_dependencies(rookxx.ioutil PreBuildSetup)
target_include_directories(rookxx.ioutil PUBLIC hdr)
target_include_directories(rookxx.ioutil PUBLIC "${rookxx_d}/hdr")
target_link_directories(rookxx.ioutil PUBLIC "${rookxx_d}/build/Debug")
target_link_libraries(rookxx.ioutil PUBLIC "${rookxx_f}")