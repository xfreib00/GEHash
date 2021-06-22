function(generate_doxygen)

  option(ENABLE_DOCS "Enable generating doxygen documentation" OFF)
  option(ENABLE_MAN "Enable generating man pages for classes" OFF)
  if(ENABLE_DOCS)

    # find doxygen package
    find_package(Doxygen
                 REQUIRED dot
                 OPTIONAL_COMPONENTS mscgen dia)

    # set doxyfile options before calling doxygen
    set(DOXYGEN_CALLER_GRAPH YES)
    set(DOXYGEN_CALL_GRAPH YES)
    set(DOXYGEN_EXTRACT_ALL YES)
    set(DOXYGEN_EXTRACT_PRIVATE YES)
    set(DOXYGEN_USE_MDFILE_AS_MAINPAGE ${CMAKE_SOURCE_DIR}/README.md)

    if(ENABLE_MAN)
      set(DOXYGEN_GENERATE_MAN YES)
    endif(ENABLE_MAN)

    set(DOXYGEN_EXCLUDE ${PROJECT_SOURCE_DIR}/src/main.cpp ${PROJECT_BINARY_DIR})

    # create target docs
    doxygen_add_docs(docs
                     ${PROJECT_SOURCE_DIR}/src/ ${PROJECT_SOURCE_DIR}/include/
                     ALL
                     COMMENT "Generate documentation")

  endif(ENABLE_DOCS)

  endfunction()