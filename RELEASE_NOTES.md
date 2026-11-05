# Release Notes {#RELEASE_NOTES}

\brief Release notes file for the netcdf-cxx4 package.

This file contains a high-level description of this package's evolution. Releases are in reverse chronological order (most recent first).

Note that this file was created and maintained starting with the `netcdf-cxx4 4.3.0 release`.

## netCDF-CXX4 4.3.2 TBD


## What's Changed
* [Bug Fix][Compression] Fixed an issue where `plugins/` were not being properly built.  See [GitHub #82](https://github.com/Unidata/netcdf-cxx4/issues/82) for more information.
* Merge changes from the v4.3.1 prep branch piecemeal back upstream by @@WardF in https://github.com/Unidata/netcdf-cxx4/pull/72
* [CMake] Remove debug info from release builds by @@bilke in https://github.com/Unidata/netcdf-cxx4/pull/76
* Install netCDFCxxConfig.cmake by @@ZedThree in https://github.com/Unidata/netcdf-cxx4/pull/62
* Fix cmake build on macOS with hdf5 1.13.0 and cmake 3.17.2 by @@5tefan in https://github.com/Unidata/netcdf-cxx4/pull/92
* Export CMake targets so build directory can be used directly by @@ZedThree in https://github.com/Unidata/netcdf-cxx4/pull/100
* Fix the build with -no-undefined. by @@orbea in https://github.com/Unidata/netcdf-cxx4/pull/103
* Fix build issue in plugins/ directory. by @@WardF in https://github.com/Unidata/netcdf-cxx4/pull/83
* Fix clang build on OSX by @@WardF in https://github.com/Unidata/netcdf-cxx4/pull/112
* docs migration by @@oxelson in https://github.com/Unidata/netcdf-cxx4/pull/116
* Resolve bad delete #98 by @@twsearle in https://github.com/Unidata/netcdf-cxx4/pull/117
* Remove duplicate line from Makefile.am by @@hmaarrfk in https://github.com/Unidata/netcdf-cxx4/pull/118
* Report test errors correctly by @@ZedThree in https://github.com/Unidata/netcdf-cxx4/pull/122
* Fix searching parent/children groups in `NcGroup::getCoordVar[s]` by @@ZedThree in https://github.com/Unidata/netcdf-cxx4/pull/121
* Fix tests on bigendian machines by @@opoplawski in https://github.com/Unidata/netcdf-cxx4/pull/74
* add const qualifier to NcFile header signatures by @@hellkite500 in https://github.com/Unidata/netcdf-cxx4/pull/130
* Fix a bunch of warnings from casts by @@ZedThree in https://github.com/Unidata/netcdf-cxx4/pull/135
* Remove global `g_ncid` by @@ZedThree in https://github.com/Unidata/netcdf-cxx4/pull/145
* remove unused file_id, avoid compiler warnings by @@garyjg in https://github.com/Unidata/netcdf-cxx4/pull/150
* Mark NcException::what() as override for std::exception::what() by @@PhilMiller in https://github.com/Unidata/netcdf-cxx4/pull/152
* Enforce C++ std 11 in build system. by @@WardF in https://github.com/Unidata/netcdf-cxx4/pull/147
* Remove deprecated exec_program cmake command by @@truenicfel in https://github.com/Unidata/netcdf-cxx4/pull/158
* CMake: Don't add uninstall target and CPack config if not top-level by @@ZedThree in https://github.com/Unidata/netcdf-cxx4/pull/141
* Updated Copyright by @@WardF in https://github.com/Unidata/netcdf-cxx4/pull/163
* Add NcFile::getPath() by @@Shooter23 in https://github.com/Unidata/netcdf-cxx4/pull/164
* Use HAVE_NC_SET_LOG_LEVEL to determine usage of nc_set_log_level by @@opoplawski in https://github.com/Unidata/netcdf-cxx4/pull/162
* Fix issue using 'make check' on MacOS by @@WardF in https://github.com/Unidata/netcdf-cxx4/pull/170
* CMake: Don't use glob to get sources by @@ZedThree in https://github.com/Unidata/netcdf-cxx4/pull/137
* Fix filter test by @@ZedThree in https://github.com/Unidata/netcdf-cxx4/pull/138
* CI: Add basic workflow by @@ZedThree in https://github.com/Unidata/netcdf-cxx4/pull/139
* Fix some warnings in tests by @@ZedThree in https://github.com/Unidata/netcdf-cxx4/pull/140
* Add `NcType::isNonPrimitive()` helper function to reduce duplication by @@ZedThree in https://github.com/Unidata/netcdf-cxx4/pull/142
* Modernise loops by @@ZedThree in https://github.com/Unidata/netcdf-cxx4/pull/143
* Revert change in f5ecc3a due to unexpected test failures on MacOS. by @@WardF in https://github.com/Unidata/netcdf-cxx4/pull/171
* Add initial docker-based regression testing. by @@WardF in https://github.com/Unidata/netcdf-cxx4/pull/172

## New Contributors
* @@bilke made their first contribution in https://github.com/Unidata/netcdf-cxx4/pull/76
* @@5tefan made their first contribution in https://github.com/Unidata/netcdf-cxx4/pull/92
* @@orbea made their first contribution in https://github.com/Unidata/netcdf-cxx4/pull/103
* @@oxelson made their first contribution in https://github.com/Unidata/netcdf-cxx4/pull/116
* @@twsearle made their first contribution in https://github.com/Unidata/netcdf-cxx4/pull/117
* @@hmaarrfk made their first contribution in https://github.com/Unidata/netcdf-cxx4/pull/118
* @@opoplawski made their first contribution in https://github.com/Unidata/netcdf-cxx4/pull/74
* @@hellkite500 made their first contribution in https://github.com/Unidata/netcdf-cxx4/pull/130
* @@garyjg made their first contribution in https://github.com/Unidata/netcdf-cxx4/pull/150
* @@PhilMiller made their first contribution in https://github.com/Unidata/netcdf-cxx4/pull/152
* @@truenicfel made their first contribution in https://github.com/Unidata/netcdf-cxx4/pull/158
* @@Shooter23 made their first contribution in https://github.com/Unidata/netcdf-cxx4/pull/164

**Full Changelog**: https://github.com/Unidata/netcdf-cxx4/compare/v4.3.1...wellspring-v4.3.2.wif

## netCDF-CXX4 v4.3.1 September 12, 2019

### Requirements

* netCDF-C 4.6.0 or greater

### Changes

* [Enhancement] Added cmake support to distribution files created by `make dist`.
* [Bug Fix] Added `ncFile::create()`, also added a new `open` function and constructor to allow for more flexibility when opening a file.  See [GitHub #55](https://github.com/Unidata/netcdf-cxx4/issues/55) for more information.
* [Enhancement] Addressed an issue reported with `Intel Compilers 17.0.0`. See [GitHub #41](https://github.com/Unidata/netcdf-cxx4/issues/41) for more information.
* [Enhancement] Updated how `configure` determines information about the existing netCDF-C install.  See [GitHub pull request #39](https://github.com/Unidata/netcdf-cxx4/pull/39) for more information.
* Corrected an issue where cmake-based builds weren't generating `ncxx4-config`.  See [GitHub pull request #37](https://github.com/Unidata/netcdf-cxx4/pull/37) for more information.


## netcdf-cxx4 v4.3.0 released May 13, 2016

* Fixed an issue where the tests were failing silently, and the underlying `NcType` class could not properly determine the type name or type size reliably. See [GitHub issue #30](https://github.com/Unidata/netcdf-cxx4/issues/30) for more information.
* Changed `NCXX_ENABLE_DOXYGEN` option to an easier-to-remember `ENABLE_DOXYGEN`.
* Added `--enable-doxygen`, `-DNCXX_ENABLE_DOXYGEN=ON` options to allow generation of netCDF-CXX4 documentation via doxygen using either `configure` or `cmake`, respectively.
* Added `netcdf-cxx4` to the [Coverity Scan Dashboard](https://scan.coverity.com/projects/unidata-netcdf-cxx4?tab=overview).
* Added `open` and `close` methods for NcFile.  See [Github Pull Request #18](https://github.com/Unidata/netcdf-cxx4/pull/18) for more information.
* Added `netcdf-cxx4` to travis-ci.org.  See [https://travis-ci.org/Unidata/netcdf-cxx4](https://travis-ci.org/Unidata/netcdf-cxx4) for more details.
* Added `NcCompoundType` methods `getMemberName` and `getMemberIndex`.  See [Pull Request #19](https://github.com/Unidata/netcdf-cxx4/pull/19) for more details.
* Added `cmake` support to `netcdf-cxx4`, which will allow us to create a `CDash` continuous integration dashboard similar to those created for the `netcdf-c` and `netcdf-fortran` projects.
* Added a `travis-ci` configuration file, `.travis.yml`.
* Created `RELEASE_NOTES.md`.
