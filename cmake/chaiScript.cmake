include(FetchContent)

# set options before fetching ChaiScript dependency
set(BUILD_MODULES OFF CACHE INTERNAL "chaiScript modules")
set(BUILD_TESTING OFF CACHE INTERNAL "chaiScript tests")

FetchContent_Declare(
    chaiscript
    GIT_REPOSITORY https://github.com/ChaiScript/ChaiScript.git
    GIT_TAG v6.1.0
)

# make ChaiScript dependency avalible
FetchContent_MakeAvailable(chaiscript)

# set up include dir variable
SET(chaiscript_INCLUDE_DIR "${chaiscript_SOURCE_DIR}/include/")

# print out status that ChaiScript library is prepared for use
MESSAGE(STATUS "ChaiScript ready")