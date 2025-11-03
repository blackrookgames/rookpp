cmake_minimum_required(VERSION 3.16)
project(test VERSION 1.0.0.0
    DESCRIPTION "test by Black Rook Games"
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DDEBUG")

if(WIN32)
    message("Detected Windows")
    set(exeOptions "")
    set(rookxx_f "librookxx.dll")
    set(rookxx_ioutil_f "librookxx.ioutil.dll")
elseif(UNIX)
    message("Detected Unix")
    set(exeOptions "")
    set(rookxx_f "librookxx.so")
    set(rookxx_ioutil_f "librookxx.ioutil.so")
else()
    message("Unknown OS")
    set(exeOptions "")
    set(rookxx_f "")
    set(rookxx_ioutil_f "")
endif()

set(rookxx_d "${CMAKE_SOURCE_DIR}/../rookxx")
set(rookxx_ioutil_d "${CMAKE_SOURCE_DIR}/../rookxx.ioutil")

# set the output directory for built objects.
# This makes sure that the dynamic library goes into the build directory automatically.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

add_custom_target(PreBuildSetup
    COMMAND ${CMAKE_COMMAND} -E echo "Running pre-build setup script..."
    COMMAND bash ${CMAKE_SOURCE_DIR}/CMakeLists.copy.sh 
        "${CMAKE_CURRENT_BINARY_DIR}/Debug" 
        "${rookxx_d}/build/Debug/${rookxx_f}" 
        "${rookxx_ioutil_d}/build/Debug/${rookxx_ioutil_f}" 
    COMMENT "Executing pre-build setup tasks"
)

add_executable(test ${exeOptions} main.cpp)
add_dependencies(test PreBuildSetup)
target_include_directories(test PUBLIC hdr)
target_include_directories(test PUBLIC "${rookxx_d}/hdr")
target_include_directories(test PUBLIC "${rookxx_ioutil_d}/hdr")
target_link_directories(test PUBLIC "${rookxx_d}/build/Debug")
target_link_directories(test PUBLIC "${rookxx_ioutil_d}/build/Debug")
target_link_libraries(test PUBLIC "${rookxx_f}")
target_link_libraries(test PUBLIC "${rookxx_ioutil_f}")