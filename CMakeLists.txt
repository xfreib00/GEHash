# Author: Adam Freiberg (xfreib00@stud.fit.vutbr.cz)
# Brief: Top level CMakeLists.txt file
# Version: 0.1
# Copyright (c) 2020

# set minimum version to 3.14 to support FetchContent
cmake_minimum_required(VERSION 3.14...3.20)

# project info
project(GEHash
        DESCRIPTION "Generating hash functions for IPv6 hashing with Grammatical evolution"
        LANGUAGES CXX)

# if this is the main app set compilation options and testing
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)

        # forbid to build in folder with source files
        file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" LOC_PATH)
        if(EXISTS "${LOC_PATH}")
                message(FATAL_ERROR "You cannot build in a source directory (or any directory with a CMakeLists.txt file). Please make a build subdirectory. Feel free to remove CMakeCache.txt and CMakeFiles.")
        endif()

        # use folders for IDE's
        set_property(GLOBAL PROPERTY USE_FOLDERS ON)

        # set C++ standards
        set(CMAKE_CXX_STANDARD_REQUIRED ON)
        set(CMAKE_CXX_STANDARD 17)
        set(CMAKE_CXX_EXTENSIONS ON)

        # test code
        include(CTest)

endif()

# include standard options for project
include(cmake/StandardOptions.cmake)

# create "library" interface to accumulate project options
add_library(project_options INTERFACE)
target_compile_features(project_options INTERFACE cxx_std_17)

# find threads package used by dependencies
find_package(Threads REQUIRED)

# create "library" interface to set standard warnings
add_library(project_warnings INTERFACE)

# include standard warnings and set them on previously created interface
include(cmake/StandardWarnings.cmake)
std_warnings(project_warnings)

# download and set up dependencies
include(cmake/gram.cmake)
include(cmake/chaiScript.cmake)
include(cmake/nlohmann_json.cmake)

# add static analyzers
include(cmake/StaticAnalyzers.cmake)
generate_static_analysis()

# add doxygen suport
include(cmake/Doxygen.cmake)
generate_doxygen()

# add sanitizers
include(cmake/Sanitizers.cmake)
use_sanitizers(project_options)

# add source file directory
add_subdirectory(src)

# enable testing
if(BUILD_TESTING)
        add_subdirectory(tests)
endif()
