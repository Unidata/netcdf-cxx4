## Automake file, partof Unidata's netCDF-CXX4 package.
# Copyright 2005-2016.

# These files are included in the dist.

EXTRA_DIST = CMakeLists.txt Doxyfile.in Doxyfile.developer DoxygenLayout.xml \
Makefile.am footer.html mainpage.md netcdf-50x50.png

# Turn off parallel builds in this directory.
.NOTPARALLEL:

if BUILD_DOCS

all-local: doxyfile.stamp
clean-local: rm -rf $(top_builddir)/docs/html

endif

doxyfile.stamp:
	$(DOXYGEN) Doxyfile

CLEANFILES = doxyfile.stamp html
