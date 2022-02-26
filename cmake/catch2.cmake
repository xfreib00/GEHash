# Author: Adam Freiberg (xfreib00@stud.fit.vutbr.cz)
# Brief: Source code to download Catch2 library dependency
# Version: 0.1
# Copyright (c) 2021

include(FetchContent)

FetchContent_Declare(
        catch
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v2.13.4
)

# make catch dependency available
FetchContent_MakeAvailable(catch)

# set up include dir variable
set(catch_INCLUDE_DIR "${catch_SOURCE_DIR}/single_include/catch2/")

# print out status that Catch2 library is prepared for use
MESSAGE(STATUS "Catch2 ready")
