include(FetchContent)

FetchContent_Declare(
    json
    GIT_REPOSITORY https://github.com/ArthurSonzogni/nlohmann_json_cmake_fetchcontent
    GIT_TAG v3.9.1
)

# make Nlohmann's JSON dependency avalible
FetchContent_MakeAvailable(json)

# set up include dir to be used in project
SET(json_INCLUDE_DIR "${json_SOURCE_DIR}/include/nlohmann/")

# print out status that Nlohmann's JSON library is prepared for use
MESSAGE(STATUS "Nlohmann's JSON ready")