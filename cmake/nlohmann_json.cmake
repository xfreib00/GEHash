include(FetchContent)

FetchContent_Declare(
    json
    GIT_REPOSITORY https://github.com/ArthurSonzogni/nlohmann_json_cmake_fetchcontent
    GIT_TAG v3.9.1)

FetchContent_GetProperties(json)
if(NOT json_POPULATED)
    MESSAGE(STATUS "Downloading Nlohmann JSON")
    FetchContent_Populate(json)
    add_subdirectory(${json_SOURCE_DIR} ${json_BINARY_DIR})
endif()

SET(json_INCLUDE_DIR "${json_SOURCE_DIR}/include/nlohmann/")

MESSAGE(STATUS "Nlohmann JSON ready")