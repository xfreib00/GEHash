# set option for using static analyzers
option(ENABLE_CLANG_TIDY "Use clang-tidy for static analysis" OFF)

if(ENABLE_CLANG_TIDY)

    # find clang tidy executable
    find_program(CLANGTIDY clang-tidy)

    if(CLANGTIDY)
        # if found set clang tidy for project
        set(CMAKE_CXX_CLANG_TIDY ${CLANGTIDY} -extra-arg=-Wno-unknown-warning-option)
    else()
        # otherwise print out error message
        message(SEND_ERROR "Clang-tidy requested but executable not found")
    endif()

endif()