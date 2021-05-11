# Author: Adam Freiberg (xfreib00@stud.fit.vutbr.cz)
# Brief: Top level CMakeLists.txt file
# Version: 0.1
# Copyright (c) 2020

# set minimum version to 3.14 to support FetchContent
cmake_minimum_required(VERSION 3.14...3.20)

# set option to build Doxygen documentation
option(GEHASH_DOCS "Build GEHash documentation." OFF)

# project info
project(GEHash
        DESCRIPTION "Producing hash functions using Grammatical evolution"
        LANGUAGES CXX)

# if this is the main app set compilation options and testing
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)

        # forbid to build in folder with source files
        file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" LOC_PATH)
        if(EXISTS "${LOC_PATH}")
        message(FATAL_ERROR "You cannot build in a source directory (or any directory with a CMakeLists.txt file). Please make a build subdirectory. Feel free to remove CMakeCache.txt and CMakeFiles.")
        endif()

        # set C++ standards
        set(CMAKE_CXX_STANDARD_REQUIRED ON)
        set(CMAKE_CXX_STANDARD 17)
        set(CMAKE_CXX_EXTENSIONS ON)

        # test code
        include(CTest)
        include(CodeCoverage)

endif()

# find threads package used by dependencies
find_package(Threads REQUIRED)

# download and set up dependencies
include(cmake/gram.cmake)
include(cmake/chaiScript.cmake)
include(cmake/nlohmann_json.cmake)
include(cmake/StaticAnalyzers.cmake)

# add source file directory
add_subdirectory(src)

# build docs using Doxygen
if (GEHASH_DOCS)
        add_subdirectory("doc")
        message(STATUS "GEHash documentation: ${PROJECT_BINARY_DIR}/doc/html/index.html")
endif ()

# enable testing
if(BUILD_TESTING)
        add_subdirectory(tests)
endif()