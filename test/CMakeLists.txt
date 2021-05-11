# Author: Adam Freiberg (xfreib00@stud.fit.vutbr.cz)
# Brief: Test folder main CMakeLists.txt file
# Version: 0.1
# Copyright (c) 2020

# download dependency
include(${PROJECT_SOURCE_DIR}/cmake/catch2.cmake)

# add test subdirectory
add_subdirectory(unit)