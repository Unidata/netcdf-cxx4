######
# Build doxygen documentation if need be.
######

IF(ENABLE_DOXYGEN)

  FILE(GLOB COPY_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*)
  FILE(COPY ${COPY_FILES} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)

  ##
  # Set some configuration variables so that they
  # are redundant with autotools.
  ##
  SET(abs_top_srcdir ${CMAKE_CURRENT_SOURCE_DIR}/..)
  SET(abs_builddir ${CMAKE_CURRENT_BINARY_DIR})

  ##
  # Create general doxyfiles
  ##
  CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in
    ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)

  ##
  # Generate User Documentation
  ##
  ADD_CUSTOM_TARGET(doc_all ALL
    ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Generating CXX4 API Documentation" VERBATIM)

ENDIF(ENABLE_DOXYGEN)
