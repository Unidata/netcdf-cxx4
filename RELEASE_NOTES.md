# Release Notes {#RELEASE_NOTES}

\brief Release notes file for the netcdf-cxx4 package.

This file contains a high-level description of this package's evolution. Releases are in reverse chronological order (most recent first).

Note that this file was created and maintained starting with the `netcdf-cxx4 4.3.0 release`.

## netCDF-CXX4 4.3.2 TBD

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
