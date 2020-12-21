add_custom_target(dmt-docs ALL ${DOXYGEN_EXECUTABLE}
                  WORKING_DIRECTORY ${CMAKE_INSTALL_PREFIX}/docs
                  COMMENT "Generating HTML documentation" VERBATIM)
