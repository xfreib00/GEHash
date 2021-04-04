cmake_minimum_required(VERSION 3.14...3.20)

option(GEHASH_DOCS "Build GEHash documentation." OFF)

project(GEHash
        DESCRIPTION "Producing hash functions using Grammatical evolution"
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS ON)

include(cmake/gram.cmake)
include(cmake/lua.cmake)
include(cmake/nlohmann_json.cmake)

add_subdirectory(src)

if (GEHASH_DOCS)
        add_subdirectory("doc")
        message(STATUS "GEHash documentation: ${PROJECT_BINARY_DIR}/doc/html/index.html")
endif ()