## This is a automake file, part of Unidata's netCDF package.
# Copyright 2011, see the COPYRIGHT file for more information.

# This file builds the new C++-4 interface.

# Point pre-preprocessor to netcdf-4 directory (libsrc4).
LDADD = $(top_builddir)/cxx4/libnetcdf_c++4.la  -lnetcdf

# This is our output library.
lib_LTLIBRARIES = libnetcdf_c++4.la

# For rules updating the version info, see
# http://www.gnu.org/s/libtool/manual/html_node/Updating-version-info.html
libnetcdf_c__4_la_LDFLAGS = -version-info 2:0:1 -no-undefined

# These headers will be installed in the users header directory.
include_HEADERS = netcdf ncAtt.h ncCheck.h ncDim.h ncException.h	\
ncGroup.h ncOpaqueType.h ncVar.h ncVlenType.h ncCompoundType.h		\
ncEnumType.h ncFile.h ncGroupAtt.h ncType.h ncVarAtt.h ncByte.h		\
ncChar.h ncShort.h ncInt.h ncFloat.h ncDouble.h ncUbyte.h ncUshort.h	\
ncUint.h ncInt64.h ncUint64.h ncString.h

# Library source.
libnetcdf_c__4_la_SOURCES = ncAtt.cpp ncCheck.cpp ncCompoundType.cpp	\
ncDim.cpp ncEnumType.cpp ncException.cpp ncFile.cpp ncGroup.cpp		\
ncGroupAtt.cpp ncOpaqueType.cpp ncType.cpp ncVar.cpp ncVarAtt.cpp	\
ncVlenType.cpp ncByte.cpp ncChar.cpp ncShort.cpp ncInt.cpp ncFloat.cpp	\
ncDouble.cpp ncUbyte.cpp ncUshort.cpp ncUint.cpp ncInt64.cpp		\
ncUint64.cpp ncString.cpp

# These are the tests.
TESTFILES = test_classic$(EXEEXT) test_group$(EXEEXT)	\
test_dim$(EXEEXT) test_att$(EXEEXT) test_var$(EXEEXT)	\
test_var2$(EXEEXT) test_type$(EXEEXT) test_open_close$(EXEEXT) \
test_ncFile_Flags$(EXEEXT)

test_classic_SOURCES = test_classic.cpp
test_group_SOURCES = test_group.cpp
test_dim_SOURCES = test_dim.cpp
test_att_SOURCES = test_att.cpp test_utilities.h
test_var_SOURCES = test_var.cpp test_utilities.h
test_var2_SOURCES = test_var2.cpp test_utilities.h
test_type_SOURCES = test_type.cpp test_utilities.h
test_open_close_SOURCES = test_open_close.cpp test_utilities.h
test_ncFile_Flags_SOURCES = test_ncFile_Flags.cpp test_utilities.h


# Build and run these tests.
check_PROGRAMS = $(TESTFILES)
TESTS = $(TESTFILES)

CLEANFILES = firstFile.cdf test*.nc

EXTRA_DIST = test_filter.cpp

# Empty file that gets time-stamped after docs are generated
doxygen_stamp: $(libnetcdf_c__4_la_SOURCES) $(include_HEADERS)
	doxygen
	touch doxygen_stamp
