# Author: Adam Freiberg (xfreib00@stud.fit.vutbr.cz)
# Brief: Source files CMakeLists.txt file
# Version: 0.1
# Copyright (c) 2020

# include header file directories
include_directories(${PROJECT_SOURCE_DIR}/include)

# set C++ flags for standard build and debug
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -march=native -mtune=native -Wall -Wextra -pedantic")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -pg")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


# create executable
add_executable(${PROJECT_NAME}
    main.cpp
    GEHash.cpp
    evolution.cpp
    logger.cpp
    evaluator.cpp
    ${HEADER_FILES}
)

# include dependecy directories
target_include_directories(${PROJECT_NAME}
    PUBLIC ${json_INCLUDE_DIR}
    PUBLIC ${chaiscript_INCLUDE_DIR}
    PUBLIC ${gram_INCLUDE_DIR}
    PUBLIC ${gram_BINARY_DIR}
)

# set directories for linker to search for dependencies
target_link_directories(${PROJECT_NAME}
    PRIVATE ${gram_BINARY_DIR}/src
    PRIVATE ${json_BINARY_DIR}/src
    PRIVATE ${chaiscript_BINARY_DIR}/src
)

# link dependecies to executable
target_link_libraries(${PROJECT_NAME} PRIVATE gram
                        PRIVATE nlohmann_json::nlohmann_json
                        ${CMAKE_DL_LIBS}
                        ${CMAKE_THREAD_LIBS_INIT})