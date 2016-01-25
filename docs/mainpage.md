# netCDF C++ Interface Guide {#cxx_interface_guide}

# netCDF C++ Interface Guide

## Introduction

Lynton Appel, of the Culham Centre for Fusion Energy (CCFE) in Oxfordshire, has developed and contributed a netCDF-4 C++ library that depends on an installed netCDF-4 C library. The netCDF-4 C++ API was developed for use in managing fusion research data from CCFE's innovative MAST (Mega Amp Spherical Tokamak) experiment.

Appel's C++ implementation is a complete read/write interface for netCDF-4, but can also be used as an alternative to the older netCDF-3 C++ interface, to write classic-format netCDF-3 files as well as netCDF-4 classic model files. The new API is implemented as a layer over the netCDF-4 C interface, which means bug fixes and performance enhancements in the C interface will be immediately available to C++ developers as well. It replaces a previous partial netCDF-4 C++ interface developed by Shanna Forbes.

The new API makes use of standard C++ features such as namespaces, exceptions, and templates, none of which were included in the first netCDF-3 C++ API developed in the mid-90's. The earlier netCDF-3 C++ API is still supported and available in the source distribution, but devvelopers who are thinking of eventually upgrading to use of the enhanced data model should consider using Lynton's new API.

We're grateful for Appel's development and CCFE's contribution of the new open-source code for the netCDF-4 C++ API, and hope C++ developers in the netCDF community will find it useful! Feedback is appreciated, and should be directed to <Lynton.Appel@ccfe.ac.uk>.

## Installation

Installing the C++ interface requires the additional flag --enable-netcdf-4 to be used during the configure stage of the installation, for example enter

 ./configure --enable-cxx-4 [plus other options]

To build the C++ interface guide, change to the `docs` directory of the distribution and enter

  doxygen Doxyfile.developer

Alternatively, you can build the documentation using the `--enable-doxygen` flag when using `configure`, or `-DNCXX_ENABLE_DOXYGEN=ON` when using `cmake`.

By default, HTML documentation will be installed in cxx4/doc/html; other options may be specified according to the settings contained in the file "Doxyfile" (details of alternative settings are documented at http://www.stack.nl/~dimitri/doxygen). Note that as a prerequisite for generating the documentation, the system will need to have doxygen (http://www.stack.nl/~dimitri/doxygen) and Graphviz (http://www.graphviz.org)installed.

Examples of usage.

Examples codes can be found by selecting the "Examples" tab.
