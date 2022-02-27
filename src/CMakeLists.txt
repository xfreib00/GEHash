# Author: Adam Freiberg (xfreib00@stud.fit.vutbr.cz)
# Brief: Source files CMakeLists.txt file
# Version: 0.1
# Copyright (c) 2021

# include header file directories
include_directories(${PROJECT_SOURCE_DIR}/include)

# set C++ flags for standard build and debug
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -march=native -mtune=native")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} -O3 -march=native -mtune=native -g")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -pg")

# create executable
add_executable(${PROJECT_NAME}
    main.cpp
    GEHash.cpp
    GEEvolution.cpp
    GELogger.cpp
    GEEvaluator.cpp
    ${HEADER_FILES}
)

# include dependency directories
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
    SYSTEM INTERFACE ${chaiscript_BINARY_DIR}/src
)

# link dependencies to executable
target_link_libraries(${PROJECT_NAME} PRIVATE
    gram
    nlohmann_json::nlohmann_json
    project_options
    project_warnings
    ${CMAKE_DL_LIBS}
    ${CMAKE_THREAD_LIBS_INIT}
)