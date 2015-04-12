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
SET(NCXX_LIB_VERSION 7.2.1)
SET(NCXX_SO_VERSION 7)
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
MACRO(CHECK_C_LINKER_FLAG M_FLAG M_RESULT)
  SET(T_REQ_FLAG "${CMAKE_REQUIRED_FLAGS}")
  SET(CMAKE_REQUIRED_FLAGS "${M_FLAG}")
  CHECK_C_SOURCE_COMPILES("int main() {return 0;}" ${M_RESULT})
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
