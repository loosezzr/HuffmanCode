cmake_minimum_required(VERSION 3.30)
project(HuffmanCode)

set(CMAKE_CXX_STANDARD 20)

# Include directories
include_directories(${CMAKE_SOURCE_DIR})

# Source files
set(SOURCES
    main.cpp
    Huffman/HuffmanCodec.cpp
    BitStream/BitStream.cpp
)

add_executable(HuffmanCode ${SOURCES})
