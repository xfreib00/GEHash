include(FetchContent)

set(GRAM_BUILD_TESTS ON CACHE INTERNAL "Build tests for Gram lib")

FetchContent_Declare(
    gram
    GIT_REPOSITORY https://github.com/jansvoboda11/gram.git
    GIT_TAG     origin/main
    GIT_CONFIG  advice.detachedHead=false
)

if (NOT gram_POPULATED)
    FetchContent_Populate(gram)
    message(STATUS "Gram source dir: ${gram_SOURCE_DIR}")
    message(STATUS "Gram binary dir: ${gram_BINARY_DIR}")
    add_subdirectory(${gram_SOURCE_DIR} ${gram_BINARY_DIR}) 
endif()

message(STATUS "Gram include dir: ${gram_SOURCE_DIR}/include")