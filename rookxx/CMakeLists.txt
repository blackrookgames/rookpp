cmake_minimum_required(VERSION 3.16)

project(rookxx VERSION 1.0.0.0
    DESCRIPTION "rookxx by Black Rook Games"
    LANGUAGES CXX)

if(WIN32)
    message("Detected Windows")
    # set(exeOptions "WIN32")
elseif(UNIX)
    message("Detected Unix")
    # set(exeOptions "")
else()
    message("Unknown OS")
    # set(exeOptions "")
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

set(src )

set(dir "")
set(src ${src} 
    hdr${dir}/Items.h)

set(dir /bitman)
set(src ${src} 
    hdr${dir}/BitPnt.h src${dir}/BitPnt.cpp 
    hdr${dir}/BitPtr.h src${dir}/BitPtr.cpp 
    hdr${dir}/BPtr.h
    hdr${dir}/ConstBitPnt.h src${dir}/ConstBitPnt.cpp 
    hdr${dir}/ConstBitPtr.h src${dir}/ConstBitPtr.cpp)

set(dir /collection)
set(src ${src} 
    hdr${dir}/AttachableList.h
    hdr${dir}/AttachableListConstIterator.h
    hdr${dir}/AttachableListIterator.h)

set(dir /collection/voidptr)
set(src ${src} 
    hdr${dir}/VoidPtrConstIterator.h src${dir}/VoidPtrConstIterator.cpp 
    hdr${dir}/VoidPtrIterator.h src${dir}/VoidPtrIterator.cpp 
    hdr${dir}/VoidPtrList.h src${dir}/VoidPtrList.cpp 
    hdr${dir}/VoidPtrListConstIterator.h src${dir}/VoidPtrListConstIterator.cpp 
    hdr${dir}/VoidPtrListIterator.h src${dir}/VoidPtrListIterator.cpp 
    hdr${dir}/VoidPtrQueue.h src${dir}/VoidPtrQueue.cpp 
    hdr${dir}/VoidPtrSegCol.h src${dir}/VoidPtrSegCol.cpp 
    hdr${dir}/VoidPtrSegColConstIterator.h src${dir}/VoidPtrSegColConstIterator.cpp 
    hdr${dir}/VoidPtrSegColIterator.h src${dir}/VoidPtrSegColIterator.cpp 
    hdr${dir}/VoidPtrSegColSegment.h src${dir}/VoidPtrSegColSegment.cpp 
    hdr${dir}/VoidPtrStack.h src${dir}/VoidPtrStack.cpp)

set(dir /ramen)
set(src ${src} 
    hdr${dir}/DataReader.h src${dir}/DataReader.cpp
    hdr${dir}/DataWriter.h src${dir}/DataWriter.cpp
    hdr${dir}/Serializable.h
    hdr${dir}/SmartReader.h src${dir}/SmartReader.cpp
    hdr${dir}/SmartWriter.h src${dir}/SmartWriter.cpp)

set(dir /ramen/huffman)
set(src ${src} 
    hdr${dir}/HuffmanLeaf.h src${dir}/HuffmanLeaf.cpp
    hdr${dir}/HuffmanNode.h src${dir}/HuffmanNode.cpp
    hdr${dir}/HuffmanNodeType.h
    hdr${dir}/HuffmanParent.h src${dir}/HuffmanParent.cpp
    hdr${dir}/HuffmanTree.h src${dir}/HuffmanTree.cpp)

add_library(rookxx SHARED ${src})
target_include_directories(rookxx PUBLIC hdr)