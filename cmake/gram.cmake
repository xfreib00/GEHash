include(FetchContent)

FetchContent_Declare(
    gram
    GIT_REPOSITORY https://github.com/jansvoboda11/gram.git
    GIT_TAG origin/master
)

FetchContent_MakeAvailable(gram)

set(gram_INCLUDE_DIR "${GEHash_SOURCE_DIR}/include/gram/")