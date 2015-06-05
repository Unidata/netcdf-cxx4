## This is a CMake file, part of Unidata's netcdf-cxx package.

INCLUDE_DIRECTORIES(".")

###
# Set up headers and sources
###

file(GLOB CXX_HEADERS *.h)
file(GLOB CXX_SOURCES nc*.cpp)

###
# Set up tests.
###
IF(NCXX_ENABLE_TESTS)

  add_bin_test(cxx4 test_classic)
  add_bin_test(cxx4 test_group)
  add_bin_test(cxx4 test_dim)
  add_bin_test(cxx4 test_att)
  add_bin_test(cxx4 test_var)
  add_bin_test(cxx4 test_var2)
  add_bin_test(cxx4 test_type)
  add_bin_test(cxx4 test_open_close)

ENDIF()

ADD_LIBRARY(netcdf-cxx4 ${CXX_SOURCES})
TARGET_LINK_LIBRARIES(netcdf-cxx4 ${NETCDF_C_LIBRARY} ${EXTRA_DEPS})
SET_TARGET_PROPERTIES(netcdf-cxx4 PROPERTIES
  VERSION ${NCXX_LIB_VERSION}
  SOVERSION ${NCXX_SO_VERSION}
  )