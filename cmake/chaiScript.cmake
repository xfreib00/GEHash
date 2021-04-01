include(FetchContent)

FetchContent_Declare(
    chaiscript
    GIT_REPOSITORY https://github.com/ChaiScript/ChaiScript.git
    GIT_TAG v6.1.0)

FetchContent_GetProperties(chaiscript)
if(NOT chaiscript_POPULATED)
    MESSAGE(STATUS "Downloading ChaiScript")
    FetchContent_Populate(chaiscript)
    add_subdirectory(${chaiscript_SOURCE_DIR} ${chaiscript_BINARY_DIR})
endif()

SET(chaiscript_INCLUDE_DIR "${chaiscript_SOURCE_DIR}/include/")

MESSAGE(STATUS "ChaiScript ready")