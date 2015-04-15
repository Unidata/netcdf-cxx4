# This is a CMake file, part of Unidata's netCDF-CXX4 package.

##################################
# Set Project Properties
##################################

#Minimum required CMake Version
cmake_minimum_required(VERSION 2.8.12)

#Project Name
PROJECT(NCXX C CXX)
set(PACKAGE "netcdf-cxx" CACHE STRING "")

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
SET(NCXX_VERSION_MINOR 2)
SET(NCXX_VERSION_PATCH 1)
SET(NCXX_VERSION_NOTE "")
SET(netCDF_VERSION ${NCXX_VERSION_MAJOR}.${NCXX_VERSION_MINOR}.${NCXX_VERSION_PATCH}${NCXX_VERSION_NOTE})
SET(VERSION ${NCXX_VERSION})
SET(NCXX_VERSION ${NCXX_VERSION})
SET(NCXX_LIB_VERSION 1.0.2)
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
  set(BUILDNAME "${osname}-${osrel}-${cpu}" CACHE STRING "Build name variable for CDash")
ENDIF()
# For CMAKE_INSTALL_LIBDIR
INCLUDE(GNUInstallDirs)

IF(MSVC)
  SET(GLOBAL PROPERTY USE_FOLDERS ON)
ENDIF()

#Add custom CMake Module
SET(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules/"
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
FILE(COPY ${CMAKE_SOURCE_DIR}/CTestCustom.cmake DESTINATION ${CMAKE_BINARY_DIR})

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

OPTION(NCXX_ENABLE_TESTS "Enable tests. Run with 'make test'." ON)
IF(NCXX_ENABLE_TESTS)
  # Options for CTest-based tests, dashboards.
  SET(NCXX_CTEST_PROJECT_NAME "netcdf-cxx4" CACHE STRING "Project Name for CTest-based testing purposes.")
  SET(NCXX_CTEST_DROP_SITE "my.cdash.org" CACHE STRING "Dashboard location for CTest-based testing purposes.")
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
  CONFIGURE_FILE("${CMAKE_SOURCE_DIR}/CTestConfig.cmake.in"
    "${CMAKE_SOURCE_DIR}/CTestConfig.cmake"
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
      INCLUDE_DIRECTORIES(SYSTEM ${NC_H_INCLUDE_DIR})
    ENDIF()
  ENDIF()
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
# Configure, print libnetcdf-cxx.settings
# file.
################################

# Set variables to mirror those used by autoconf.
# This way we don't need to maintain two separate template
# files.
SET(host_cpu "${cpu}")
SET(host_vendor "${osname}")
SET(host_os "${osrel}")
SET(abs_top_builddir "${CMAKE_BINARY_DIR}")

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
  @ONLY)

# Read in settings file, print out.
# Avoid using system-specific calls so that this
# might also work on Windows.
FILE(READ "${CMAKE_CURRENT_BINARY_DIR}/libnetcdf-cxx.settings"
  LIBNETCDFCXX_SETTINGS)
MESSAGE(${LIBNETCDFCXX_SETTINGS})

# Install libnetcdf-cxx.settings file into same location
# as the libraries.
INSTALL(FILES "${NCXX_BINARY_DIR}/libnetcdf-cxx.settings"
  DESTINATION "${CMAKE_INSTALL_LIBDIR}"
  COMPONENT libraries)

#####
# End libnetcdf-cxx.settings section.
#####

#####
# Traverse into subdirectories.
#####

##
# Set up include directories.
##
INCLUDE_DIRECTORIES(cxx4 examples)

ADD_SUBDIRECTORY(cxx4)
ADD_SUBDIRECTORY(examples)