#                                               -*- Autoconf -*-
# This is part of Unidata's netCDF package. Copyright 2005-2011, see
# the COPYRIGHT file for more information.

AC_PREREQ([2.66])
AC_INIT([netCDF-cxx4], [4.3.1], [support-netcdf@unidata.ucar.edu])

# Create the VERSION file, which contains the package version from
# AC_INIT.
echo -n AC_PACKAGE_VERSION>VERSION
AC_SUBST(PACKAGE_VERSION)

AC_MSG_NOTICE([netCDF-cxx4 AC_PACKAGE_VERSION])

# Keep libtool macros in an m4 directory.
AC_CONFIG_MACRO_DIR([m4])

# Find out about the host/target we're building on/for.
AC_CANONICAL_HOST
AC_CANONICAL_TARGET

# We will output a config.h.
AC_CONFIG_HEADERS([config.h])

# This call is required by automake.
AM_INIT_AUTOMAKE([foreign dist-zip subdir-objects])
AM_MAINTAINER_MODE()

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


####
# Doxygen and doxygen-related options.
####
AC_ARG_ENABLE([doxygen],
  [AS_HELP_STRING([--enable-doxygen],
    [Enable generation of documentation.])])
test "x$enable_doxygen" = xyes || enable_doxygen=no
AM_CONDITIONAL([BUILD_DOCS], [test "x$enable_doxygen" = xyes])


##
# Eventually set these depending on an upcoming 'build release docs'
# option.  See configure.ac in netcdf-c for guidance.
##
AC_SUBST([DOXYGEN_CSS_FILE], [])
AC_SUBST([DOXYGEN_HEADER_FILE], [])
AC_SUBST([DOXYGEN_SEARCHENGINE], ["YES"])

##
# Is doxygen installed? If so, have configure construct the Doxyfile.
##
AC_CHECK_PROGS([DOXYGEN], [doxygen])
if test -z "$DOXYGEN"; then
   AC_MSG_WARN([Doxygen not found - documentation will not be built])
fi

# Is graphviz/dot installed? If so, we'll use dot to create
# graphs in the documentation.
AC_CHECK_PROGS([DOT], [dot])
if test -z "$DOT"; then
   AC_MSG_WARN([dot not found - will use simple charts in documentation])
   HAVE_DOT=NO
elif test "x$enable_dot" = xno; then
   HAVE_DOT=NO
else
   HAVE_DOT=YES
fi

# If we have doxygen, and it's enabled, then process the file.
if test "x$enable_doxygen" != xno; then
   if test -n "$DOXYGEN"; then
        AC_SUBST(HAVE_DOT)
        AC_CONFIG_FILES([docs/Doxyfile])
   fi
# Note: the list of files to input to doxygen
# has been moved to docs/Doxyfile.in so
# that make distcheck works correctly.
# Any new inputs should be inserted into
# docs/Doxyfile.in and possibley docs/Makefile.am
fi

#####
# End Doxygen and doxygen-related options.
#####

# Valgrind tests don't work with shared builds because of some libtool
# weirdness.
if test "x$enable_shared" = xyes; then
   if test "x$enable_valgrind_tests" = xyes; then
      AC_MSG_ERROR([No valgrind tests with shared libraries])
   fi
fi

AC_MSG_NOTICE([finding other utilities])

# Set up libtool.
AC_MSG_NOTICE([setting up libtool])
LT_PREREQ([2.2])
LT_INIT

# Checks for programs.
AC_PROG_CXX
AC_PROG_AWK
AC_PROG_CC
AC_PROG_CPP
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET

# Checks for header files.
AC_CHECK_HEADERS([stddef.h stdlib.h string.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_TYPE_SIZE_T
AC_CHECK_TYPES([ptrdiff_t])

# Checks for library functions.
AC_FUNC_MALLOC

# Check to see if any macros must be set to enable large (>2GB) files.
AC_SYS_LARGEFILE

# User supplied nc-config
AC_ARG_WITH([nc-config],
    [AS_HELP_STRING([--with-nc-config=DIR],
        [directory containing nc-config (if not in PATH)])],,
    [])

# Find nc-config, either from user supplied PATH, or system PATH
AS_CASE([$with_nc_config],
    ["yes"], [AC_MSG_ERROR([You must supply a path to --with-nc-config])],
    ["no"], [AC_MSG_NOTICE([Not using nc-config])],
    [AC_PATH_PROG([NCCONF], [nc-config], [], [$with_nc_config$PATH_SEPARATOR$PATH])])

# If we found nc-config, use that to check NetCDF capabilities
# otherwise, try and find the header/libraries and check directly
AS_IF([test "x$ac_cv_path_NCCONF" != "x"],
    [
      AC_MSG_NOTICE([checking output of nc-config])
      nc_build_v2=`$ac_cv_path_NCCONF --has-nc2`
      nc_build_v4=`$ac_cv_path_NCCONF --has-nc4`
      nc_has_logging=`$ac_cv_path_NCCONF --has-logging`
      nc_has_dap=`$ac_cv_path_NCCONF --has-dap`
      nc_has_pnetcdf=`$ac_cv_path_NCCONF --has-pnetcdf`
    ],
    [
      # See if these functions are in the library.
      AC_CHECK_HEADERS([netcdf.h], [], [AC_MSG_ERROR([netcdf.h could not be found. Please set CPPFLAGS.])])
      AC_SEARCH_LIBS([nc_create], [netcdf], [], [])
      AC_CHECK_FUNCS([nc_def_opaque nccreate nc_set_log_level oc_open nc_use_parallel_enabled])

      # Whether we build/test some functionality depends on what we found in
      # the C library.
      nc_build_v2=$ac_cv_func_nccreate
      nc_build_v4=$ac_cv_func_nc_def_opaque
      nc_has_logging=$ac_cv_func_nc_set_log_level
      nc_has_dap=$ac_cv_func_oc_open
      nc_has_pnetcdf=$ac_cv_func_nc_use_parallel_enabled
    ])

###
# Check for Filter support
###
AC_CHECK_LIB([netcdf],[nc_def_var_filter],[nc_has_filters=yes],[nc_has_filters=no])

if test "x$nc_has_filters" != xno; then
   # Do we want to run
   AC_MSG_CHECKING([whether filter testing should be run])
   AC_ARG_ENABLE([filter-testing],
              [AS_HELP_STRING([--disable-filter-testing],
                              [Do not run filter test and example; requires shared libraries and netCDF-4])])
   test "x$enable_filter_testing" = xno || enable_filter_testing=yes
   AC_MSG_RESULT($enable_filter_testing)
fi

AM_CONDITIONAL(ENABLE_FILTER_TESTING, [test x$enable_filter_testing = xyes])


AC_MSG_CHECKING([netCDF v2 API present])
AC_MSG_RESULT([$nc_build_v2])

AC_MSG_CHECKING([netCDF-4 present])
AC_MSG_RESULT([$nc_build_v4])

AC_MSG_CHECKING([netCDF has logging])
AC_MSG_RESULT([$nc_has_logging])

AC_MSG_CHECKING([netCDF has dap])
AC_MSG_RESULT([$nc_has_dap])

AC_MSG_CHECKING([netCDF has pnetcdf])
AC_MSG_RESULT([$nc_has_pnetcdf])

AC_MSG_CHECKING([netCDF has filter support])
AC_MSG_RESULT([$nc_has_filters])

if test "x$nc_build_v4" = xyes; then
   AC_DEFINE([USE_NETCDF4], [1], [if true, build netCDF-4])
else
   AC_ERROR([NetCDF must be built with netCDF-4 enabled.])
fi

AM_CONDITIONAL([USE_NETCDF4], [test "x$nc_build_v4" = xyes])
AM_CONDITIONAL([BUILD_V2], [test "x$nc_build_v2" = xyes])
AM_CONDITIONAL([USE_LOGGING], [test "x$nc_has_logging" = xyes])
AM_CONDITIONAL([BUILD_DAP], [test "x$nc_has_dap" = xyes])
AM_CONDITIONAL([BUILD_PARALLEL], [test "x$nc_has_pnetcdf" = xyes])
AM_CONDITIONAL([NC_HAS_FILTERS], [test "x$nc_has_filters" = xyes])
AM_CONDITIONAL([BUILD_DOCS], [test x$enable_doxygen = xyes])
AM_CONDITIONAL(USE_VALGRIND_TESTS, [test "x$enable_valgrind_tests" = xyes])

# Flags for ncxx4-config script; by design $prefix, $includir, $libdir,
# etc.  are left as shell variables in the script so as to facilitate
# relocation
NC_LIBS="-lnetcdf_c++4"
if test "x$enable_shared" != xyes; then
   NC_LIBS="$LDFLAGS $NC_LIBS $LIBS"
fi

case "x$target_os" in
xsolaris*)
  NEWNCLIBS=""
  for x in $NC_LIBS ; do
    case "$x" in
    -L*) r=`echo "$x" | sed -e 's|^-L|-R|'`
	 NEWNCLIBS="$NEWNCLIBS $x $r"
	 ;;
    *)	 NEWNCLIBS="$NEWNCLIBS $x" ;;
    esac
  done
  NC_LIBS="$NEWNCLIBS"
  ;;
*);;
esac

AC_SUBST(NC_LIBS,[$NC_LIBS])
AC_SUBST(HAS_DAP,[$nc_has_dap])
AC_SUBST(HAS_NC2,[$nc_build_v2])
AC_SUBST(HAS_NC4,[$nc_build_v4])
AC_SUBST(NC_HAS_FILTERS, [$nc_has_filters])
AC_SUBST(ENABLE_FILTER_TESTING, [$enable_filter_testing])
# This would be true for a cmake build.
AC_SUBST([ISCMAKE], [])

# This would be true for a visual studio build.
AC_SUBST([MSVC], [])

AC_MSG_NOTICE([generating header files and makefiles])
AC_CONFIG_FILES(test_common.sh:test_common.in)
AC_CONFIG_FILES([Makefile
                 cxx4/Makefile
                 examples/Makefile
                 docs/Makefile
                 ncxx4-config
                 netcdf-cxx4.pc],
                 [test -f  ncxx4-config && chmod 755 ncxx4-config ])



if test "x$nc_has_filters" = xyes; then
   AC_CONFIG_FILES(cxx4/findplugin.sh:cxx4/findplugin.in)

   if test "x$enable_filter_testing" != xno; then
      AC_CONFIG_FILES(plugins/Makefile)
      AC_CONFIG_FILES([examples/tst_filter.sh:examples/tst_filter.sh], [chmod ugo+x examples/tst_filter.sh])
      AC_CONFIG_FILES(examples/findplugin.sh:examples/findplugin.in)
   fi
fi


AC_OUTPUT()
