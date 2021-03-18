cmake_minimum_required(VERSION 3.14...3.19)

project(GEHash
        DESCRIPTION "Producing hash functions using Grammatical evolution"
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)

include(cmake/gram.cmake)

add_subdirectory(src)
