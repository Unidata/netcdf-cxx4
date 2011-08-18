#                                               -*- Autoconf -*-
## Process this file with autoconf to produce a configure script.

# This is part of Unidata's netCDF package. Copyright 2005-2011, see
# the COPYRIGHT file for more information.

# Running autoconf on this file will trigger a warning if 
# autoconf is not at least the specified version.
AC_PREREQ([2.59])

# Initialize with name, version, and support email address. 
AC_INIT([netCDF-cxx4], [4.2-beta2], [support-netcdf@unidata.ucar.edu])

# Create the VERSION file, which contains the package version from
# AC_INIT.
echo -n AC_PACKAGE_VERSION>VERSION
AC_SUBST(PACKAGE_VERSION)

AC_MSG_NOTICE([netCDF-cxx4 AC_PACKAGE_VERSION])

# Keep libtool macros in an m4 directory.
AC_CONFIG_MACRO_DIR([m4])

# Find out about the host we're building on.
AC_CANONICAL_HOST

# Find out about the target we're building for.
AC_CANONICAL_TARGET

# We will output a config.h.
AC_CONFIG_HEADERS([config.h])

# This call is required by automake.
AM_INIT_AUTOMAKE([foreign dist-bzip2 dist-zip dist-tarZ subdir-objects])

# Check for the existance of this file before proceeding.
AC_CONFIG_SRCDIR([cxx4/ncByte.cpp])

AC_MSG_NOTICE([checking user options])

# Does the user want to do some extra tests?
AC_MSG_CHECKING([whether netCDF extra tests should be run (developers only)])
AC_ARG_ENABLE([extra-tests],
              [AS_HELP_STRING([--enable-extra-tests],
                              [run some extra tests that may not pass because of known issues])])
test "x$enable_extra_tests" = xyes || enable_extra_tests=no
AC_MSG_RESULT($enable_extra_tests)
if test "x$enable_extra_tests" = xyes; then
   AC_DEFINE([EXTRA_TESTS], [1], [if true, run extra tests which may not work yet])
fi
AM_CONDITIONAL(EXTRA_TESTS, [test x$enable_extra_tests = xyes])

# Does the user want to run tests for large files (> 2GiB)?
AC_MSG_CHECKING([whether large file (> 2GB) tests should be run])
AC_ARG_ENABLE([large-file-tests],
              [AS_HELP_STRING([--enable-large-file-tests],
                              [Run tests which create very large data files (~13 GB disk space
                              required, but it will be recovered when tests are complete). See
                              option --with-temp-large to specify temporary directory])])
test "x$enable_large_file_tests" = xyes || enable_large_file_tests=no
AC_MSG_RESULT($enable_large_file_tests)
AM_CONDITIONAL(LARGE_FILE_TESTS, [test x$enable_large_file_tests = xyes])
if test "x$enable_large_file_tests" = xyes; then
   AC_DEFINE([LARGE_FILE_TESTS], [1], [do large file tests])
fi

# Does the user want to run benchmarks?
AC_MSG_CHECKING([whether benchmaks should be run (experimental)])
AC_ARG_ENABLE([benchmarks],
              [AS_HELP_STRING([--enable-benchmarks],
                              [Run benchmarks tests (if any).])])
test "x$enable_benchmarks" = xyes || enable_benchmarks=no
AC_MSG_RESULT($enable_benchmarks)
AM_CONDITIONAL(BUILD_BENCHMARKS, [test x$enable_benchmarks = xyes])

# If the env. variable TEMP_LARGE is set, or if
# --with-temp-large=<directory>, use it as a place for the large
# (i.e. > 2 GiB) files created during the large file testing.
AC_MSG_CHECKING([where to put large temp files if large file tests are run])
AC_ARG_WITH([temp-large],
            [AS_HELP_STRING([--with-temp-large=<directory>],
                            [specify directory where large files (i.e. >2 GB) \
                            will be written, if large files tests are run with
                            --enable-large-file-tests])],
            [TEMP_LARGE=$with_temp_large])
TEMP_LARGE=${TEMP_LARGE-.}
AC_MSG_RESULT($TEMP_LARGE)
#AC_SUBST(TEMP_LARGE)
AC_DEFINE_UNQUOTED([TEMP_LARGE], ["$TEMP_LARGE"], [Place to put very large netCDF test files.])

AC_MSG_NOTICE([finding C++ compiler (will not be used if C++ API is not desired)])
AC_PROG_CXX

# Set up libtool.
AC_MSG_NOTICE([setting up libtool])
LT_PREREQ([2.2])
LT_INIT

# Valgrind tests don't work with shared builds because of some libtool
# weirdness.
if test "x$enable_shared" = xyes; then
   if test $enable_valgrind_tests = yes; then
      AC_MSG_ERROR([No valgrind tests with shared libraries])
   fi
fi

AC_MSG_NOTICE([finding other utilities])

# Find the install program.
AC_PROG_INSTALL

# Check to see if any macros must be set to enable large (>2GB) files.
AC_SYS_LARGEFILE

# For nightly build testing, output CC, FC, etc.
#echo "CPPFLAGS=$CPPFLAGS CC=$CC CFLAGS=$CFLAGS CXX=$CXX CXXFLAGS=$CXXFLAGS FC=$FC FCFLAGS=$FCFLAGS F77=$F77 FFLAGS=$FFLAGS LDFLAGS=$LDFLAGS LIBS=$LIBS FLIBS=$FLIBS F90LIBS=$F90LIBS" >> comps.txt

AC_MSG_NOTICE([checking types, headers, and functions])

dnl AC_CHECK_HEADER(stdlib.h, ,AC_DEFINE([NO_STDLIB_H], [], [no stdlib.h]))
dnl AC_CHECK_HEADER(sys/types.h, ,AC_DEFINE([NO_SYS_TYPES_H], [], [no sys_types.h]))
dnl AC_CHECK_HEADERS([sys/param.h])
dnl #AC_CHECK_HEADERS([locale.h])
dnl AC_HEADER_DIRENT
dnl AC_HEADER_STDC
dnl AC_HEADER_SYS_WAIT
dnl AC_HEADER_TIME
dnl AC_CHECK_HEADERS([locale.h stdio.h stdarg.h errno.h ctype.h fcntl.h malloc.h stdlib.h string.h \
dnl 			   strings.h unistd.h sys/stat.h getopt.h sys/time.h sys/resource.h])
dnl AC_FUNC_VPRINTF

dnl # Check for <stdbool.h> that conforms to C99 requirements
dnl AC_HEADER_STDBOOL

dnl # Check for these functions...
dnl AC_CHECK_FUNCS([strlcat strerror snprintf strchr strrchr mktemp strcat strcpy strdup \
dnl 			strcasecmp strtod strtoll strtoull getrlimit gettimeofday fsync MPI_Comm_f2c])
dnl AC_FUNC_ALLOCA
dnl AC_CHECK_DECLS([isnan, isinf, isfinite, signbit],,,[#include <math.h>])
dnl AC_STRUCT_ST_BLKSIZE
dnl UD_CHECK_IEEE
dnl AC_TYPE_SIZE_T
dnl AC_TYPE_OFF_T
dnl AC_CHECK_TYPES([ssize_t, ptrdiff_t, uchar, longlong])
dnl AC_C_CHAR_UNSIGNED
dnl AC_C_BIGENDIAN
dnl AC_CHECK_SIZEOF(short)
dnl AC_CHECK_SIZEOF(int)
dnl AC_CHECK_SIZEOF(long)
dnl AC_CHECK_SIZEOF(float)
dnl AC_CHECK_SIZEOF(double)
dnl AC_CHECK_SIZEOF(off_t)
dnl AC_CHECK_SIZEOF(size_t)

# See if these functions are in the library.
AC_CHECK_FUNCS([nc_def_opaque nccreate nc_set_log_level nc_use_parallel_enabled])

# Automake conditionals need to be called, whether the answer is yes
# or no.
AM_CONDITIONAL(USE_VALGRIND_TESTS, [test "x$enable_valgrind_tests" = xyes])
AM_CONDITIONAL(USE_NETCDF4, [test x$enable_netcdf_4 = xyes])

dnl # Flags for nc-config script; by design $prefix, $includir, $libdir,
dnl # etc.  are left as shell variables in the script so as to facilitate
dnl # relocation
dnl if test "x$with_netcdf_c_lib" = x ; then 
dnl    NC_LIBS="-lnetcdf"
dnl else
dnl    NC_LIBS="$with_netcdf_c_lib"
dnl fi
dnl if test "x$enable_shared" != xyes; then
dnl    NC_LIBS="$LDFLAGS $NC_LIBS $LIBS"
dnl fi	 

dnl case "x$target_os" in
dnl xsolaris*) 
dnl   NEWNCLIBS=""
dnl   for x in $NC_LIBS ; do
dnl     case "$x" in
dnl     -L*) r=`echo "$x" | sed -e 's|^-L|-R|'`
dnl 	 NEWNCLIBS="$NEWNCLIBS $x $r"
dnl 	 ;;
dnl     *)	 NEWNCLIBS="$NEWNCLIBS $x" ;;
dnl     esac
dnl   done
dnl   NC_LIBS="$NEWNCLIBS"
dnl   ;;
dnl *);;
dnl esac

dnl NC_FLIBS="-lnetcdff $NC_LIBS"

dnl AC_SUBST(NC_LIBS,[$NC_LIBS])
dnl AC_SUBST(NC_FLIBS,[$NC_FLIBS])
dnl AC_SUBST(HAS_DAP,[$enable_dap])
dnl AC_SUBST(HAS_NC2,[$nc_build_v2])
dnl AC_SUBST(HAS_NC4,[$enable_netcdf_4])
dnl AC_SUBST(HAS_HDF4,[$enable_hdf4])
dnl AC_SUBST(HAS_PNETCDF,[$enable_pnetcdf])
dnl AC_SUBST(HAS_HDF5,[$enable_netcdf_4])
dnl AC_SUBST(HAS_F77,[$nc_build_f77])
dnl AC_SUBST(HAS_F90,[$nc_build_f90])
dnl AC_SUBST(HAS_CXX,[$nc_build_cxx])
dnl AC_SUBST(HAS_SZLIB,[$nc_has_szlib])

# Access netcdf specific version of config.h
#AH_BOTTOM([#include "ncconfigure.h"])

##################################################
# Uncomment this to keep a copy of autoconf defines at this point, for
# debugging purposes.
# cp confdefs.h my_config.h

AC_MSG_NOTICE([generating header files and makefiles])
AC_CONFIG_FILES([Makefile
                 cxx4/Makefile
                 examples/Makefile])
#                 nc-config
#                 [test -f  nc-config && chmod 755 nc-config ]

AC_OUTPUT()

