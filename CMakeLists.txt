# This is a CMake file, part of Unidata's netCDF-CXX4 package.

##################################
# Set Project Properties
##################################

#Minimum required CMake Version
cmake_minimum_required(VERSION 2.8.12)

#Project Name
PROJECT(NCXX C CXX)
set(PACKAGE "netcdf-cxx4" CACHE STRING "")

#####
# Version Info:
#
# Release Version
# Library Version
# SO Version
#
# SO Version is computed from library version. See:
# http://www.gnu.org/software/libtool/manual/libtool.html#Libtool-versioning
#####

SET(NCXX_VERSION_MAJOR 4)
SET(NCXX_VERSION_MINOR 3)
SET(NCXX_VERSION_PATCH 1)
SET(NCXX_VERSION_NOTE "")
SET(NCXX_VERSION ${NCXX_VERSION_MAJOR}.${NCXX_VERSION_MINOR}.${NCXX_VERSION_PATCH}${NCXX_VERSION_NOTE})
SET(VERSION ${NCXX_VERSION})
SET(NCXX_LIB_VERSION 1.1.0)
SET(NCXX_SO_VERSION 1)
SET(PACKAGE_VERSION ${VERSION})

# Get system configuration, Use it to determine osname, os release, cpu. These
# will be used when committing to CDash.
find_program(UNAME NAMES uname)
IF(UNAME)
  macro(getuname name flag)
    exec_program("${UNAME}" ARGS "${flag}" OUTPUT_VARIABLE "${name}")
  endmacro(getuname)
  getuname(osname -s)
  getuname(osrel  -r)
  getuname(cpu    -m)
  set(TMP_BUILDNAME "${osname}-${osrel}-${cpu}" CACHE STRING "Build name variable for CDash")
ENDIF()

###
# Allow for some customization of the buildname.
# This will make it easier to identify different builds,
# based on values passed from command line/shell scripts.
#
# For ctest scripts, we can use CTEST_BUILD_NAME.
###

SET(BUILDNAME_PREFIX "" CACHE STRING "")
SET(BUILDNAME_SUFFIX "" CACHE STRING "")

IF(BUILDNAME_PREFIX)
  SET(TMP_BUILDNAME "${BUILDNAME_PREFIX}-${TMP_BUILDNAME}")
ENDIF()

IF(BUILDNAME_SUFFIX)
  SET(TMP_BUILDNAME "${TMP_BUILDNAME}-${BUILDNAME_SUFFIX}")
ENDIF()

IF(NOT BUILDNAME)
  SET(BUILDNAME "${TMP_BUILDNAME}" CACHE STRING "Build name variable for CDash")
ENDIF()
###
# End BUILDNAME customization.
###


# For CMAKE_INSTALL_{LIBDIR,INCLUDEDIR,...}
INCLUDE(GNUInstallDirs)

IF(MSVC)
  SET(GLOBAL PROPERTY USE_FOLDERS ON)
ENDIF()

#Add custom CMake Module
SET(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules/"
  CACHE INTERNAL "Location of our custom CMake modules.")

# auto-configure style checks, other CMake modules.
INCLUDE(${CMAKE_ROOT}/Modules/CheckLibraryExists.cmake)
INCLUDE(${CMAKE_ROOT}/Modules/CheckIncludeFile.cmake)
INCLUDE(${CMAKE_ROOT}/Modules/CheckTypeSize.cmake)
INCLUDE(${CMAKE_ROOT}/Modules/CheckFunctionExists.cmake)
INCLUDE(${CMAKE_ROOT}/Modules/CheckCXXSourceCompiles.cmake)
INCLUDE(${CMAKE_ROOT}/Modules/CheckCSourceCompiles.cmake)
INCLUDE(${CMAKE_ROOT}/Modules/TestBigEndian.cmake)
INCLUDE(${CMAKE_ROOT}/Modules/CheckSymbolExists.cmake)
INCLUDE(${CMAKE_ROOT}/Modules/GetPrerequisites.cmake)

INCLUDE(CheckCCompilerFlag)
FIND_PACKAGE(PkgConfig QUIET)

# A macro to check if a C linker supports a particular flag.
MACRO(CHECK_CXX_LINKER_FLAG M_FLAG M_RESULT)
  SET(T_REQ_FLAG "${CMAKE_REQUIRED_FLAGS}")
  SET(CMAKE_REQUIRED_FLAGS "${M_FLAG}")
  CHECK_CXX_SOURCE_COMPILES("int main() {return 0;}" ${M_RESULT})
  SET(CMAKE_REQUIRED_FLAGS "${T_REQ_FLAG}")
ENDMACRO()

# Set the build type.
IF(NOT CMAKE_BUILD_TYPE)
  SET(CMAKE_BUILD_TYPE DEBUG CACHE STRING "Choose the type of build, options are: None, Debug, Release."
    FORCE)
ENDIF()

# Set build type uppercase
STRING(TOUPPER ${CMAKE_BUILD_TYPE} CMAKE_BUILD_TYPE)

# Determine the configure date.

EXECUTE_PROCESS(
  COMMAND date
  OUTPUT_VARIABLE CONFIG_DATE
  )
IF(CONFIG_DATE)
	string(STRIP ${CONFIG_DATE} CONFIG_DATE)
ENDIF()

# Check to see if we have bash.
FIND_PROGRAM(HAVE_BASH bash)
IF(HAVE_BASH)
  STRING(COMPARE EQUAL "${HAVE_BASH}" "C:/Windows/System32/bash.exe" IS_BASH_EXE)
  IF(NOT IS_BASH_EXE)
    MESSAGE(STATUS "Found bash: ${HAVE_BASH}")
  ELSE()
    MESSAGE(STATUS "Ignoring ${HAVE_BASH}")
    SET(HAVE_BASH "")
  ENDIF()
ELSE()
  MESSAGE(STATUS "Bash shell not found; disabling shell script tests.")
ENDIF()

##
# Allow for extra dependencies.
##

SET(EXTRA_DEPS "")

################################
# End Project Properties
################################

################################
# Utility Macros
################################

# A function used to create autotools-style 'yes/no' definitions.
# If a variable is set, it 'yes' is returned. Otherwise, 'no' is
# returned.
#
# Also creates a version of the ret_val prepended with 'NC',
# when feature is true, which is used to generate netcdf_meta.h.
FUNCTION(is_disabled feature ret_val)
  IF(${feature})
    SET(${ret_val} "no" PARENT_SCOPE)
  ELSE()
    SET(${ret_val} "yes" PARENT_SCOPE)
    SET("NC_${ret_val}" 1 PARENT_SCOPE)
  ENDIF(${feature})
ENDFUNCTION()

FUNCTION(is_enabled feature ret_val)
  IF(${feature})
    SET(${ret_val} "yes" PARENT_SCOPE)
    SET("NC_${ret_val}" 1 PARENT_SCOPE)
  ELSE()
    SET(${ret_val} "no" PARENT_SCOPE)
    SET("NC_${ret_val}" 0 PARENT_SCOPE)
  ENDIF(${feature})
ENDFUNCTION()

###
# A macro to add a binary test.
###
MACRO(add_bin_test prefix F)
  SET(CUR_TEST "${prefix}_${F}")
  ADD_EXECUTABLE(${CUR_TEST} ${F}.cpp)
  TARGET_LINK_LIBRARIES(${CUR_TEST}
    netcdf-cxx4
    ${NETCDF_C_LIBRARY}
    ${EXTRA_LIBS}
    )
  IF(MSVC)
    SET_TARGET_PROPERTIES(${CUR_TEST}
      PROPERTIES LINK_FLAGS_DEBUG " /NODEFAULTLIB:MSVCRT"
      )
  ENDIF()
  ADD_TEST(${CUR_TEST} ${EXECUTABLE_OUTPUT_PATH}/${CUR_TEST})
  ###
  # If visual studio,
  # do a little bit of housekeeping/reorganization.
  ###
  IF(MSVC)
    SET_PROPERTY(TEST ${CUR_TEST} PROPERTY FOLDER "tests/")
    SET_TARGET_PROPERTIES(${CUR_TEST} PROPERTIES RUNTIME_OUTPUT_DIRECTORY
      ${CMAKE_CURRENT_BINARY_DIR})
    SET_TARGET_PROPERTIES(${CUR_TEST} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG
      ${CMAKE_CURRENT_BINARY_DIR})
    SET_TARGET_PROPERTIES(${CUR_TEST} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE
      ${CMAKE_CURRENT_BINARY_DIR})
  ENDIF()
ENDMACRO()


###
# A macro to add a shell test.
###
MACRO(add_sh_test prefix F)
  IF(HAVE_BASH)
    ADD_TEST(${prefix}_${F} bash "-c" "export srcdir=${CMAKE_CURRENT_SOURCE_DIR};export TOPSRCDIR=${CMAKE_SOURCE_DIR};${CMAKE_CURRENT_BINARY_DIR}/${F}.sh")
  ENDIF()
ENDMACRO()

# Build a binary used by a script, but don't make a test out of it.
MACRO(build_bin_test F)
  ADD_EXECUTABLE(${F} ${F}.cpp)
  TARGET_LINK_LIBRARIES(${F} netcdf-cxx4 ${ALL_TLL_LIBS})
  IF(MSVC)
    SET_TARGET_PROPERTIES(${F}
      PROPERTIES LINK_FLAGS_DEBUG " /NODEFAULTLIB:MSVCRT"
      )
    SET_TARGET_PROPERTIES(${F} PROPERTIES RUNTIME_OUTPUT_DIRECTORY
      ${CMAKE_CURRENT_BINARY_DIR})
    SET_TARGET_PROPERTIES(${F} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG
      ${CMAKE_CURRENT_BINARY_DIR})
    SET_TARGET_PROPERTIES(${F} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE
      ${CMAKE_CURRENT_BINARY_DIR})
  ENDIF()
ENDMACRO()

################################
# End Utility Macros
################################

################################
# Set CTest Properties
################################

ENABLE_TESTING()
INCLUDE(CTest)

##
# Copy the CTest customization file into binary directory, as required.
##
FILE(COPY ${CMAKE_CURRENT_SOURCE_DIR}/CTestCustom.cmake DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

##
# Set Memory test program for non-MSVC based builds.
# Assume valgrind for now.
##
IF(NOT MSVC)
  SET(CTEST_MEMORYCHECK_COMMAND valgrind CACHE STRING "")
ENDIF()

##
# Set variable to define the build type.
##
INCLUDE(GenerateExportHeader)

ENABLE_TESTING()
INCLUDE(CTest)

################################
# End CTest Properties
################################

################################
# User Options
################################

##
# Default building shared libraries.
# BUILD_SHARED_LIBS is provided by/used by
# CMake directly.
##
OPTION(BUILD_SHARED_LIBS "Configure netcdf-cxx as a shared library." ON)
IF(BUILD_SHARED_LIBS)
  SET(CMAKE_POSITION_INDEPENDENT_CODE ON)
ENDIF()

##
# Enable doxygen-generated documentation.
##
OPTION(ENABLE_DOXYGEN "Enable generation of doxygen-based documentation." OFF)
IF(ENABLE_DOXYGEN)
  FIND_PACKAGE(Doxygen REQUIRED)
  FIND_PROGRAM(NCXX_DOT NAMES dot)
  IF(NCXX_DOT)
    SET(HAVE_DOT YES CACHE STRING "")
  ELSE(NCXX_DOT)
    SET(HAVE_DOT NO CACHE STRING "")
  ENDIF(NCXX_DOT)
ENDIF()

OPTION(NCXX_ENABLE_TESTS "Enable tests. Run with 'make test'." ON)
IF(NCXX_ENABLE_TESTS)
  # Options for CTest-based tests, dashboards.
  SET(NCXX_CTEST_PROJECT_NAME "netcdf-cxx4" CACHE STRING "Project Name for CTest-based testing purposes.")
  SET(NCXX_CTEST_DROP_SITE "cdash.unidata.ucar.edu" CACHE STRING "Dashboard location for CTest-based testing purposes.")
  SET(NCXX_CTEST_DROP_LOC_PREFIX "" CACHE STRING "Prefix for Dashboard location on remote server when using CTest-based testing.")

  FIND_PROGRAM(HOSTNAME_CMD NAMES hostname)
  IF(NOT MSVC)
    SET(HOSTNAME_ARG "-s")
  ENDIF()
  IF(HOSTNAME_CMD)
    EXEC_PROGRAM(${HOSTNAME_CMD} ARGS "${HOSTNAME_ARG}" OUTPUT_VARIABLE HOSTNAME)
    SET(NCXX_CTEST_SITE "${HOSTNAME}" CACHE STRING "Hostname of test machine.")
  ENDIF()

  IF(NCXX_CTEST_SITE)
    SET(SITE "${NCXX_CTEST_SITE}" CACHE STRING "")
  ENDIF()

  # Create a CTestConfig file from the template.
  CONFIGURE_FILE("${CMAKE_CURRENT_SOURCE_DIR}/CTestConfig.cmake.in"
    "${CMAKE_CURRENT_SOURCE_DIR}/CTestConfig.cmake"
    @ONLY
    )

ENDIF()

##
# Mark some options as advanced.
##
MARK_AS_ADVANCED(NCXX_CTEST_PROJECT_NAME
  NCXX_CTEST_DROP_SITE
  NCXX_CTEST_DROP_LOC_PREFIX
)


################################
# End User Options
################################

################################
# Seek out dependent libraries.
################################


###
# Find NetCDF
###
IF(NOT netCDF_LIBRARIES AND NOT netCDF_INCLUDE_DIR)
  FIND_PACKAGE(netCDF QUIET)
ELSE()
  SET(netCDF_FOUND TRUE)
ENDIF()

IF (netCDF_FOUND)
  INCLUDE_DIRECTORIES(SYSTEM ${netCDF_INCLUDE_DIR})
  SET(NETCDF_C_LIBRARY ${netCDF_LIBRARIES})
  SET(NETCDF_C_INCLUDE_DIR ${netCDF_INCLUDE_DIR})
ELSE()
  # netCDF not properly packaged. Try to find it manually.
  FIND_LIBRARY(NETCDF_C_LIBRARY NAMES netcdf libnetcdf)
  IF(NOT NETCDF_C_LIBRARY)
    MESSAGE(FATAL_ERROR "libnetcdf not found. Please reinstall and try again.")
  ELSE()
    MESSAGE(STATUS "Found netcdf: ${NETCDF_C_LIBRARY}")
    FIND_PATH(NC_H_INCLUDE_DIR "netcdf.h")
    IF(NOT NC_H_INCLUDE_DIR)
      MESSAGE(FATAL_ERROR "Directory containing netcdf.h cannot be found. Please reinstall and try again.")
    ELSE()
      GET_FILENAME_COMPONENT(netCDF_LIB_DIR "${NETCDF_C_LIBRARY}" REALPATH)
      INCLUDE_DIRECTORIES(SYSTEM ${NC_H_INCLUDE_DIR})
    ENDIF()
  ENDIF()
ENDIF()

###
# Check to see if netcdf-c was built with parallel.
###
CHECK_LIBRARY_EXISTS(${NETCDF_C_LIBRARY} nc_use_parallel_enabled "" NC_IS_PARALLEL)
IF(NC_IS_PARALLEL)
  SET(BUILD_PARALLEL ${NC_IS_PARALLEL} CACHE STRING "")
ENDIF()

###
# Check to see if netcdf-c was built with plugin support.
###
CHECK_LIBRARY_EXISTS(${NETCDF_C_LIBRARY} nc_def_var_filter "" NC_HAS_DEF_VAR_FILTER)
IF(NC_HAS_DEF_VAR_FILTER)
  SET(HAS_DEF_VAR_FILTER ${NC_HAS_DEF_VAR_FILTER} CACHE STRING "")
ENDIF(NC_HAS_DEF_VAR_FILTER)

###
# Find HDF5
###
IF(MSVC)
  SET(SEARCH_PACKAGE_NAME ${HDF5_PACKAGE_NAME})
  FIND_PACKAGE(HDF5 NAMES ${SEARCH_PACKAGE_NAME} COMPONENTS C HL NO_MODULES REQUIRED ${NC_HDF5_LINK_TYPE})
ELSE(MSVC)
  FIND_PACKAGE(HDF5 COMPONENTS C HL REQUIRED)
ENDIF(MSVC)

CHECK_LIBRARY_EXISTS(${HDF5_C_LIBRARY_hdf5} H5free_memory "" HAVE_H5FREE_MEMORY)
IF(NOT HAVE_H5FREE_MEMORY)
  MESSAGE(STATUS "Plugin support requires libhdf5 with H5Free support. Your libhdf5 install does not provide H5Free.  Please install a newer version of libhdf5 if you require plugin compression support.")
  SET(NC_HAS_DEF_VAR_FILTER "")
ENDIF()

################################
# End 'seek out dependent libraries'
################################



################################
# Compiler Configuration
################################

##
# Supress unused variable and parameter warnings, for the time being,
# on GCC.
#
# Also, set some other default compiler flags.
##

IF(CMAKE_COMPILER_IS_GNUCC OR APPLE)
  SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -Wall -Wno-unused-variable -Wno-unused-parameter")
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wno-unused-variable -Wno-unused-parameter")

  OPTION(ENABLE_COVERAGE_TESTS "Enable compiler flags needed to perform coverage tests." OFF)
  OPTION(ENABLE_CONVERSION_WARNINGS "Enable warnings for implicit conversion from 64 to 32-bit datatypes." ON)
  OPTION(ENABLE_LARGE_FILE_TESTS "Enable large file tests." OFF)

  # Debugging flags
  SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -Wall")

  # Check to see if -Wl,--no-undefined is supported.
  CHECK_CXX_LINKER_FLAG("-Wl,--no-undefined" LIBTOOL_HAS_NO_UNDEFINED)

  IF(LIBTOOL_HAS_NO_UNDEFINED)
    SET(CMAKE_SHARED_LINKER_FLAGS_DEBUG "${CMAKE_SHARED_LINKER_FLAGS_DEBUG} -Wl,--no-undefined")
  ENDIF()
  SET(CMAKE_REQUIRED_FLAGS "${TMP_CMAKE_REQUIRED_FLAGS}")

  # Coverage tests need to have optimization turned off.
  IF(ENABLE_COVERAGE_TESTS)
    SET(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -g -O0 -fprofile-arcs -ftest-coverage")
    SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fprofile-arcs -ftest-coverage")
    MESSAGE(STATUS "Coverage Tests: On.")
  ENDIF()

    # Warnings for 64-to-32 bit conversions.
  IF(ENABLE_CONVERSION_WARNINGS)
    CHECK_CXX_COMPILER_FLAG(-Wconversion CXX_HAS_WCONVERSION)
    CHECK_CXX_COMPILER_FLAG(-Wshorten-64-to-32 CXX_HAS_SHORTEN_64_32)

    IF(CXX_HAS_SHORTEN_64_32)
      SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wshorten-64-to-32")
    ENDIF()
    IF(CXX_HAS_WCONVERSION)
      SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wconversion")
    ENDIF()

  ENDIF(ENABLE_CONVERSION_WARNINGS)

ENDIF(CMAKE_COMPILER_IS_GNUCC OR APPLE)

# End default linux gcc & apple compiler options.


ADD_DEFINITIONS()

# Supress CRT Warnings.
# Only necessary for Windows
IF(MSVC)
  ADD_DEFINITIONS(-D_CRT_SECURE_NO_WARNINGS)
ENDIF()


################################
# End Compiler Configuration
################################

################################
# Configuration for post-install RPath
# Adapted from http://www.cmake.org/Wiki/CMake_RPATH_handling
################################

IF(NOT MSVC)
  # use, i.e. don't skip the full RPATH for the build tree
  SET(CMAKE_SKIP_BUILD_RPATH  FALSE)

  # when building, don't use the install RPATH already
  # (but later on when installing)
  SET(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)

  if(APPLE)
    set(CMAKE_MACOSX_RPATH ON)
  endif(APPLE)

  # add the automatically determined parts of the RPATH
  # which point to directories outside the build tree to the install RPATH
  SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

  # the RPATH to be used when installing,
  # but only if it's not a system directory
  LIST(FIND
    CMAKE_PLATFORM_IMPLICIT_LINK_DIRECTORIES
    "${CMAKE_INSTALL_FULL_LIBDIR}"
    isSystemDir
    )
  IF("${isSystemDir}" STREQUAL "-1")
    SET(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_FULL_LIBDIR}")
  ENDIF()

ENDIF()

################################
# End configuration for post-install RPath
################################


################################
# Configure, print libnetcdf-cxx.settings
# file.
################################

# Set variables to mirror those used by autoconf.
# This way we don't need to maintain two separate template
# files.
SET(host_cpu "${cpu}")
SET(host_vendor "${osname}")
SET(host_os "${osrel}")
SET(abs_top_builddir "${CMAKE_CURRENT_BINARY_DIR}")

SET(CC_VERSION "${CMAKE_C_COMPILER}")
SET(CXX_VERSION "${CMAKE_CXX_COMPILER}")

# Build *FLAGS for libnetcdf.settings.
SET(CFLAGS "${CMAKE_C_FLAGS} ${CMAKE_C_FLAGS_${CMAKE_BUILD_TYPE}}")
SET(CXXFLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_${CMAKE_BUILD_TYPE}}")
SET(LDFLAGS "${CMAKE_SHARED_LINKER_FLAGS} ${CMAKE_SHARED_LINKER_FLAGS_${CMAKE_BUILD_TYPE}}")

is_disabled(BUILD_SHARED_LIBS enable_static)
is_enabled(BUILD_SHARED_LIBS enable_shared)

# Remove libnetcdf from NC_LIBS.
STRING(REPLACE "-lnetcdf-cxx4 " "" TMP_NCXX_LIBS "${NCXX_LIBS}")
SET(LIBS "${TMP_NCXX_LIBS}")

CONFIGURE_FILE(
  "${CMAKE_CURRENT_SOURCE_DIR}/libnetcdf-cxx.settings.in"
  "${CMAKE_CURRENT_BINARY_DIR}/libnetcdf-cxx.settings"
  @ONLY
  )

# Read in settings file, print out.
# Avoid using system-specific calls so that this
# might also work on Windows.
FILE(
  READ "${CMAKE_CURRENT_BINARY_DIR}/libnetcdf-cxx.settings"
  LIBNETCDFCXX_SETTINGS
  )
MESSAGE(${LIBNETCDFCXX_SETTINGS})

# Install libnetcdf-cxx.settings file into same location
# as the libraries.
INSTALL(
  FILES "${NCXX_BINARY_DIR}/libnetcdf-cxx.settings"
  DESTINATION "${CMAKE_INSTALL_LIBDIR}"
  COMPONENT libraries
  )

#####
# End libnetcdf-cxx.settings section.
#####

#####
# Begin ncxx4-config section
#####

FILE(MAKE_DIRECTORY ${NCXX_BINARY_DIR}/tmp)
CONFIGURE_FILE("${CMAKE_CURRENT_SOURCE_DIR}/ncxx4-config.cmake.in"
        "${NCXX_BINARY_DIR}/tmp/ncxx4-config" @ONLY)
FILE(COPY "${NCXX_BINARY_DIR}/tmp/ncxx4-config"
        DESTINATION ${NCXX_BINARY_DIR}/
        FILE_PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE)

INSTALL(PROGRAMS ${NCXX_BINARY_DIR}/ncxx4-config
        DESTINATION ${CMAKE_INSTALL_BINDIR}
        COMPONENT utilities)

#####
# End ncxx4-config section
#####

#####
# Build test_common.sh
#####
SET(EXTRA_DIST ${EXTRA_DIST} ${CMAKE_SOURCE_DIR}/test_common.in)
SET(TOPSRCDIR "${CMAKE_SOURCE_DIR}")
SET(TOPBUILDDIR "${CMAKE_BINARY_DIR}")
configure_file(${CMAKE_SOURCE_DIR}/test_common.in ${CMAKE_BINARY_DIR}/test_common.sh @ONLY NEWLINE_STYLE LF)

#####
# Options
#####

include(CMakePackageConfigHelpers)

# Create export configuration
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/netCDF/netCDFCxxConfigVersion.cmake"
  VERSION ${NCXX_VERSION}
  COMPATIBILITY SameMajorVersion
  )

install(
  FILES
  "${CMAKE_CURRENT_BINARY_DIR}/netCDF/netCDFCxxConfigVersion.cmake"
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/netCDFCxx
  COMPONENT headers
  )


#####
# Traverse into subdirectories.
#####



##
# Set up include directories.
##
INCLUDE_DIRECTORIES(cxx4 examples)

ADD_SUBDIRECTORY(cxx4)
ADD_SUBDIRECTORY(examples)

IF(NC_HAS_DEF_VAR_FILTER)
  #####
  # Build cxx4/findplugin.sh
  #####
  SET(ISCMAKE "1")
  CONFIGURE_FILE(${CMAKE_SOURCE_DIR}/cxx4/findplugin.in ${CMAKE_BINARY_DIR}/cxx4/findplugin.sh @ONLY NEWLINE_STYLE LF)
  CONFIGURE_FILE(${CMAKE_SOURCE_DIR}/examples/findplugin.in ${CMAKE_BINARY_DIR}/examples/findplugin.sh @ONLY NEWLINE_STYLE LF)

  ADD_SUBDIRECTORY(plugins)
ENDIF(NC_HAS_DEF_VAR_FILTER)

IF(ENABLE_DOXYGEN)
  ADD_SUBDIRECTORY(docs)
ENDIF()



##
# CPack, CMakeInstallation.cmake file.
##
INCLUDE(CMakeInstallation.cmake)
