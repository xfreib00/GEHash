include(FetchContent)

FetchContent_Declare(
        catch
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v2.13.4
)

# make catch dependency avalible
FetchContent_MakeAvailable(catch)

# set up include dir variable
set(catch_INCLUDE_DIR "${catch_SOURCE_DIR}/single_include/catch2/")

# print out status that Catch2 library is prepared for use
MESSAGE(STATUS "Catch2 ready")
