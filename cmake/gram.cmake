include(FetchContent)

FetchContent_Declare(
    gram
    GIT_REPOSITORY https://github.com/xfreib00/gram.git
    GIT_TAG     origin/wrapper_fix
    GIT_CONFIG  advice.detachedHead=false
)

# make catch dependency avalible
FetchContent_MakeAvailable(gram)

# set up include dir for use in project
SET(gram_INCLUDE_DIR "${gram_SOURCE_DIR}/include/")

# print out status that Gram library is prepared for use
MESSAGE(STATUS "Gram library ready")