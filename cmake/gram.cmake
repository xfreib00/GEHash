include(FetchContent)

set(GRAM_BUILD_TESTS ON CACHE INTERNAL "Build tests for Gram lib")

FetchContent_Declare(
    gram
    GIT_REPOSITORY https://github.com/jansvoboda11/gram.git
    GIT_TAG     origin/main
    GIT_CONFIG  advice.detachedHead=false
)

FetchContent_MakeAvailable(gram)

set(gram_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include/gram/include/")
