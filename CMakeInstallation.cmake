#####
# Contains variables and settings used
# by the CMake build system in order to
# build binary installers.
#####

SET(CPACK_PACKAGE_VENDOR "Unidata")

##
# Declare exclusions list used when building a source file.
# NOTE!! This list uses regular expressions, NOT wildcards!!
##
SET(CPACK_SOURCE_IGNORE_FILES "${CPACK_SOURCE_IGNORE_FILES}"
  "${CMAKE_CURRENT_BINARY_DIR}/*"
  "/myhtml/*"
  "/.svn/"
  "my.*\\\\.sh"
  "/.deps/"
  "/.libs"
  "/html/"
  ".*\\\\.jar"
  ".*\\\\.jdl"
  ".*\\\\.sed"
  ".*\\\\.proto"
  ".*\\\\.texi"
  ".*\\\\.example"
  "Make0"
  "/obsolete/"
  "/unknown/"
  ".*~"
  )

###
# Set options specific to the
# Nullsoft Installation System (NSIS)
###

SET(CPACK_PACKAGE_CONTACT "NetCDF Support <support-netcdf@unidata.ucar.edu>")

IF(WIN32)
  SET(CPACK_NSIS_MODIFY_PATH ON)
  SET(CPACK_NSIS_DISPLAY_NAME "NetCDF ${netCDF_VERSION}")
  SET(CPACK_NSIS_PACKAGE_NAME "NetCDF ${netCDF_VERSION}")
  SET(CPACK_NSIS_HELP_LINK "https://www.unidata.ucar.edu/netcdf")
  SET(CPACK_NSIS_URL_INFO_ABOUT "https://www.unidata.ucar.edu/netcdf")
  SET(CPACK_NSIS_CONTACT "support-netcdf@unidata.ucar.edu")
  SET(CPACK_NSIS_ENABLE_UNINSTALL_BEFORE_INSTALL ON)
  SET(CPACK_NSIS_MENU_LINKS
	"https://www.unidata.ucar.edu/netcdf" "Unidata Website"
	"https://docs.unidata.ucar.edu/netcdf-c" "NetCDF Stable Documentation"
    "https://docs.unidata.ucar.edu/netcdf-cxx4" "NetCDF CXX4 Stable Documentation"
	"https://docs.unidata.ucar.edu/netcdf-c" "NetCDF Unstable Documentation")

ENDIF()

###
# Set debian-specific options used when
# creating .deb.
#
# http://www.cmake.org/Wiki/CMake:CPackPackageGenerators
###

# This should be set using the output of dpkg --print-architecture.
FIND_PROGRAM(NC_DPKG NAMES dpkg)
IF(NC_DPKG)
  execute_process(COMMAND "${NC_DPKG}" "--print-architecture" OUTPUT_VARIABLE dpkg_arch OUTPUT_STRIP_TRAILING_WHITESPACE)
  SET(CPACK_DEBIAN_PACKAGE_NAME "netcdf4-cxx4-dev")
  SET(CPACK_DEBIAN_PACKAGE_ARCHITECTURE "${dpkg_arch}")
  SET(CPACK_DEBIAN_PACKAGE_DEPENDS "zlib1g (>= 1:1.2.3.4), libhdf5-7 (>= 1.8.11), libcurl4-openssl-dev (>= 7.22.0)")
ENDIF()


##
# Set Copyright, License info for CPack.
##
CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/COPYRIGHT
  ${CMAKE_CURRENT_BINARY_DIR}/COPYRIGHT.txt
  @ONLY
  )

SET(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_BINARY_DIR}/COPYRIGHT.txt")
IF(NOT CPACK_PACK_VERSION)
  SET(CPACK_PACKAGE_VERSION ${VERSION})
ENDIF()

IF(UNIX)
  SET(CPACK_GENERATOR "STGZ" "TBZ2" "DEB" "ZIP")
ENDIF()

IF(APPLE)
  SET(CPACK_SOURCE_GENERATOR "TGZ")
  SET(CPACK_GENERATOR "PackageMaker" "STGZ" "TBZ2" "TGZ" "ZIP")
ENDIF()

##
# Create an 'uninstall' target.
##
CONFIGURE_FILE(
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
  IMMEDIATE @ONLY)


ADD_CUSTOM_TARGET(uninstall
  COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)

##
# Customize some of the package component descriptions
##

set(CPACK_COMPONENT_LIBRARIES_DESCRIPTION
  "The NetCDF-CXX4 Libraries")
set(CPACK_COMPONENT_HEADERS_DESCRIPTION
  "Header files for use with NetCDF-CXX4")
set(CPACK_COMPONENT_DOCUMENTATION_DESCRIPTION
  "The NetCDF-CXX4 user documentation.")

INCLUDE(CPack)
