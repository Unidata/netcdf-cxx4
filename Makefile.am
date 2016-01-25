# This is the main automake file for the netCDF CXX4 C++ library.

# These files get added to the distribution.
EXTRA_DIST = COPYRIGHT ncxx4-config.in

# Directory for autotools to put scripts during build.
ACLOCAL_AMFLAGS = -I m4

# Pkgconfig is some data about how the package was built.
pkgconfigdir=$(libdir)/pkgconfig
pkgconfig_DATA = netcdf-cxx4.pc

# The nc-config script helps the user build programs with netCDF.
bin_SCRIPTS = ncxx4-config

# Build and test in these directories.
SUBDIRS = cxx4 examples docs

# Remove these generated files, for a distclean.
DISTCLEANFILES = VERSION

install-data-hook:
	@echo ''
	@echo '+-------------------------------------------------------------+'
	@echo '| Congratulations! You have successfully installed the        |'
	@echo '| new netCDF-4 C++ Library                                    |'
	@echo '|                                                             |'
	@echo '| CAUTION:                                                    |'
	@echo '|                                                             |'
	@echo '| If you have not already run "make check", then we strongly  |'
	@echo '| recommend you do so. It does not take very long.            |'
	@echo '|                                                             |'
	@echo '| Before using netCDF to store important data, test your      |'
	@echo '| build with "make check".                                    |'
	@echo '|                                                             |'
	@echo '| If any tests fail, please see the netCDF web site:          |'
	@echo '| http://www.unidata.ucar.edu/software/netcdf/                |'
	@echo '|                                                             |'
	@echo '| NetCDF is developed and maintained at the Unidata Program   |'
	@echo '| Center. Unidata provides a broad array of data and software |'
	@echo '| tools for use in geoscience education and research.         |'
	@echo '| http://www.unidata.ucar.edu                                 |'
	@echo '+-------------------------------------------------------------+'
	@echo ''
