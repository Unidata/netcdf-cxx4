## This is a CMake file, part of Unidata's netcdf-cxx package.

INCLUDE_DIRECTORIES(".")

###
# Set up headers.
###

SET(CXX_HEADERS ncAtt.h ncCheck.h ncDim.h ncException.h ncGroup.h ncOpaqueType.h ncVar.h ncVlenType.h ncCompoundType.h ncEnumType.h ncFile.h ncGroupAtt.h ncType.h ncVarAtt.h ncByte.h ncChar.h ncShort.h ncInt.h ncFloat.h ncDouble.h ncUbyte.h ncUshort.h ncUint.h ncInt64.h ncUint64.h ncString.h)

###
# Set up sources.
###

SET(CXX_SOURCES ncAtt.cpp ncCheck.cpp ncCompoundType.cpp ncDim.cpp ncEnumType.cpp ncException.cpp ncFile.cpp ncGroup.cpp ncGroupAtt.cpp ncOpaqueType.cpp ncType.cpp ncVar.cpp ncVarAtt.cpp ncVlenType.cpp ncByte.cpp ncChar.cpp ncShort.cpp ncInt.cpp ncFloat.cpp ncDouble.cpp ncUbyte.cpp ncUshort.cpp ncUint.cpp ncInt64.cpp ncUint64.cpp ncString.cpp)

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

ENDIF()

ADD_LIBRARY(netcdf-cxx4 ${CXX_HEADERS} ${CXX_SOURCES})
TARGET_LINK_LIBRARIES(netcdf-cxx4 ${NETCDF_C_LIBRARY} ${EXTRA_DEPS})
SET_TARGET_PROPERTIES(netcdf-cxx4 PROPERTIES
  VERSION ${NCXX_LIB_VERSION}
  SOVERSION ${NCXX_SO_VERSION}
  )