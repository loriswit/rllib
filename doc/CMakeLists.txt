find_package(Doxygen REQUIRED)

set(DOXYGEN_CONFIG ${PROJECT_BINARY_DIR}/doc/Doxyfile)
configure_file(${PROJECT_SOURCE_DIR}/doc/Doxyfile.in ${DOXYGEN_CONFIG} @ONLY)

add_custom_target(doc ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_CONFIG}
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
