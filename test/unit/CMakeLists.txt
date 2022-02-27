# Author: Adam Freiberg (xfreib00@stud.fit.vutbr.cz)
# Brief: Unit test CMakeLists.txt file
# Version: 0.1
# Copyright (c) 2020

add_executable(utest
            unit_main.cpp)

target_include_directories(utest
            PRIVATE ${catch_INCLUDE_DIR})

target_link_libraries(utest PRIVATE Catch2::Catch2)

append_coverage_compiler_flags()
setup_target_for_coverage_lcov(
    NAME GEHash-test-coverage
    EXECUTABLE utest
    DEPENDENCIES GEHash-test-coverage
    EXCLUDE "../../build*"
)

add_test(NAME UnitTests
	 COMMAND utest
)