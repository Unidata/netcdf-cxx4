## This is a CMake file, part of Unidata's netcdf-cxx package.

SET(CXX_HEADERS ncAtt.h ncCheck.h ncDim.h ncException.h ncGroup.h ncOpaqueType.h ncVar.h ncVlenType.h ncCompoundType.h ncEnumType.h ncFile.h ncGroupAtt.h ncType.h ncVarAtt.h ncByte.h ncChar.h ncShort.h ncInt.h ncFloat.h ncDouble.h ncUbyte.h ncUshort.h ncUint.h ncInt64.h ncUint64.h ncString.h)

SET(CXX_SOURCES ncAtt.cpp ncCheck.cpp ncCompoundType.cpp ncDim.cpp ncEnumType.cpp ncException.cpp ncFile.cpp ncGroup.cpp ncGroupAtt.cpp ncOpaqueType.cpp ncType.cpp ncVar.cpp ncVarAtt.cpp ncVlenType.cpp ncByte.cpp ncChar.cpp ncShort.cpp ncInt.cpp ncFloat.cpp ncDouble.cpp ncUbyte.cpp ncUshort.cpp ncUint.cpp ncInt64.cpp ncString.cpp)

ADD_LIBRARY(ncxx OBJECT ${CXX_HEADERS} ${CXX_SOURCES})