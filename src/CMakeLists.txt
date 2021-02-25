include_directories(../include)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -pg")

add_executable(gehash
    main.cpp
)

target_include_directories(gehash PRIVATE
    ${GEHash_SOURCE_DIR}/include
    ${gram_INCLUDE_DIR}
)

target_link_libraries(gehash gram)