# Author: Adam Freiberg (xfreib00@stud.fit.vutbr.cz)
# Brief: Source code of function for setting up and enabling clang-tidy
# Version: 0.1
# Copyright (c) 2021

function(generate_static_analysis)

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
        endif(CLANGTIDY)

    endif(ENABLE_CLANG_TIDY)

endfunction(generate_static_analysis)