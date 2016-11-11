## This file should be placed in the root directory of your project.
## Then modify the CMakeLists.txt file in the root directory of your
## project to incorporate the testing dashboard.
##
## # The following are required to submit to the CDash dashboard:
##   ENABLE_TESTING()
##   INCLUDE(CTest)

set(DART_TESTING_TIMEOUT "4800")

set(CTEST_PROJECT_NAME "netcdf-cxx4")
set(CTEST_NIGHTLY_START_TIME "00:00:00 MDT")
SET(CTEST_SITE "linuxdev")

set(CTEST_DROP_METHOD "http")
set(CTEST_DROP_SITE "my.cdash.org")
set(CTEST_DROP_LOCATION "/submit.php?project=netcdf-cxx4")
set(CTEST_DROP_SITE_CDASH TRUE)
