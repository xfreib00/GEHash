function(use_sanitizers project_name)

    # check if copiler is either GCC or Clang, which features sanitizers
    if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL ".*Clang")

        # flag to enable generating coverage report
        OPTION(ENABLE_COVERAGE "Enable generating coverage report" OFF)

        # if coverage is set, prepare compiler and linker options
        if(ENABLE_COVERAGE)
            target_compile_options(${project_name} INTERFACE --coverage -O0 -g)
            target_link_libraries(${project_name} INTERFACE --coverage)
        endif()

        # initialize sanitizer option string
        SET(SANITIZER "")

        # flag to add address sanitizer to list of sanitizers
        OPTION(ENABLE_SANITIZER_ADDRESS "Enable address sanitizer" OFF)

        if(ENABLE_SANITIZER_ADDRESS)
            list(APPEND SANITIZERS "address")
        endif()

        # flag to add leak sanitizer to list of sanitizers
        OPTION(ENABLE_SANITIZER_LEAK "Enable leak sanitizer" OFF)

        if(ENABLE_SANITIZER_LEAK)
            list(APPEND SANITIZERS "leak")
        endif()

        # flag to add undefined behaviour sanitizers to list of sanitizers
        option(ENABLE_SANITIZER_UNDEFINED_BEHAVIOR "Enable undefined behavior sanitizer" OFF)

        if(ENABLE_SANITIZER_UNDEFINED_BEHAVIOR)
            list(APPEND SANITIZERS "undefined")
        endif()

        # join all items in SANITIZERS list to one item called LIST_OF_SANITIZERS
        list(JOIN SANITIZERS "," LIST_OF_SANITIZERS)

    endif() # endif of compiler id

    # check if string of sanitizers was set
    if(LIST_OF_SANITIZERS)

        # if string is not empty set compile and linker options
        if(NOT "${LIST_OF_SANITIZERS}" STREQUAL "")

            target_compile_options(${project_name} INTERFACE -fsanitize=${LIST_OF_SANITIZERS})
            target_link_options(${project_name} INTERFACE -fsanitize=${LIST_OF_SANITIZERS})

        endif() # endif string is not empty

    endif(LIST_OF_SANITIZERS)

endfunction(use_sanitizers)