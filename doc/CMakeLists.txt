# Author: Adam Freiberg (xfreib00@stud.fit.vutbr.cz)
# Brief: Documentation CMakeLists.txt file
# Version: 0.1
# Copyright (c) 2020

# try to find Doxygen
find_package(Doxygen)

if (DOXYGEN_FOUND)
    #set input and output doxyfile
    SET(DOXYGEN_IN ${PROJECT_SOURCE_DIR}/doc/Doxyfile.in)
    SET(DOXYGEN_OUT ${PROJECT_SOURCE_DIR}/doc/Doxyfile)

    # create doxyfile using doxyfile.in
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
    message(STATUS "Doxygen: Doxyfile generated")

    # add docs target
    add_custom_target(docs ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating documentation with Doxygen"
        VERBATIM
    )
# if Doxygen not found print error message
else(DOXYGEN_FOUND)
    message("Doxygen needs to be installed to generate documentation.")
endif(DOXYGEN_FOUND)