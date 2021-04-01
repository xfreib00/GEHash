cmake_minimum_required(VERSION 3.14...3.20)

option(GEHASH_DOCS "Build GEHash documentation." OFF)

project(GEHash
        DESCRIPTION "Producing hash functions using Grammatical evolution"
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

include(cmake/gram.cmake)
include(cmake/chaiScript.cmake)
include(cmake/nlohmann_json.cmake)

add_subdirectory(src)

if (GEHASH_DOCS)
        add_subdirectory("doc")
        message(STATUS "GEHash documentation: ${PROJECT_BINARY_DIR}/doc/html/index.html")
endif ()