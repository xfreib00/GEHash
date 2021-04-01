include_directories(${PROJECT_SOURCE_DIR}/include)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -pg")

add_executable(${PROJECT_NAME}
    main.cpp
    GEHash.cpp
    evolution.cpp
    logger.cpp
    evaluator.cpp
    ${HEADER_FILES}
)

target_include_directories(${PROJECT_NAME}
    PUBLIC ${json_INCLUDE_DIR}
    PUBLIC ${chaiscript_INCLUDE_DIR}
    PUBLIC ${gram_INCLUDE_DIR}
    PUBLIC ${gram_BINARY_DIR}
)

target_link_directories(${PROJECT_NAME}
    PRIVATE ${gram_BINARY_DIR}/src
    PRIVATE ${json_BINARY_DIR}/src
    PRIVATE ${chaiscript_BINARY_DIR}/src
)

target_link_libraries(${PROJECT_NAME} PRIVATE gram
                        PRIVATE chaiscript
                        PRIVATE nlohmann_json::nlohmann_json)