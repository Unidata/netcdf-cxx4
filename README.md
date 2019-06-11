[![Build Status](https://travis-ci.org/Unidata/netcdf-cxx4.svg)](https://travis-ci.org/Unidata/netcdf-cxx4)

netcdf-cxx4
===========

Official GitHub repository for netCDF-4 C++ library.

Note: The latest release of the historic C++ libraries, netCDF-4.2, may be downloaded from the following page:

* https://www.unidata.ucar.edu/downloads/netcdf/index.jsp

### Introduction

Lynton Appel, of the Culham Centre for Fusion Energy (CCFE) in
Oxfordshire, has developed and contributed a
[netCDF-4 C++ library][netcdf-cxx4] that depends on an installed
netCDF-4 C library.  The netCDF-4 C++ API was developed for use in
managing fusion research data from CCFE's innovative MAST (Mega Amp
Spherical Tokamak) experiment.

  [netcdf-cxx4]: https://www.unidata.ucar.edu/downloads/netcdf/netcdf-cxx/

Appel's C++ implementation is a complete read/write interface for
netCDF-4, but can also be used as an alternative to the older netCDF-3
C++ interface, to write classic-format netCDF-3 files as well as
netCDF-4 classic model files. The new API is implemented as a layer
over the netCDF-4 C interface, which means bug fixes and performance
enhancements in the C interface will be immediately available to C++
developers as well. It replaces a previous partial netCDF-4 C++
interface developed by Shanna Forbes.

The new API makes use of standard C++ features such as namespaces,
exceptions, and templates, none of which were included in the first
netCDF-3 C++ API developed in the mid-90's. The earlier netCDF-3 C++
API is still supported and available in the source distribution, but
developers who are thinking of eventually upgrading to use of the
enhanced data model should consider using Lynton's new API.

We're grateful for Appel's development and CCFE's contribution of the
new open-source code for the netCDF-4 C++ API, and hope C++ developers
in the netCDF community will find it useful! Feedback is appreciated,
and should be directed to [Lynton Appel][la_email].

  [la_email]: mailto:Lynton.Appel@ccfe.ac.uk

### Installation

The C++ interface requires the C library to have been build with the
netCDF-4 API (this is the default in recent versions). You can check
by running:

    $ nc-config --has-nc4
    yes

The simplest way to build the C++ interface is with CMake:

    mkdir build
    cd build
    cmake ..
    make
    ctest
    make install

Make sure that either `nc-config` is in your `PATH`, or that the
location of `netCDFConfig.cmake` is in `CMAKE_PREFIX_PATH`.

There is also an autotools-based build system:

    mkdir build
    cd build
    ../configure
    make
    make check
    make install

Note that the "configure" script must be generated using

    autoreconf -if

To build the C++ interface guide, change to the cxx4 directory of the
distribution and enter

    doxygen

By default, HTML documentation will be installed in cxx4/doc/html;
other options may be specified according to the settings contained in
the file "Doxyfile" (details of alternative settings are documented at
[doxygen][dox_l]). Note that as a prerequisite for generating the
documentation, the system will need to have doxygen and
[Graphviz][g_l] installed.


  [dox_l]: https://www.stack.nl/~dimitri/doxygen
  [g_l]: https://www.graphviz.org/


### Examples of usage

Here is an example of writing a 2D array to a file, and then reading
it back in:

```cpp
#include <iostream>
#include <netcdf>

// We are writing 2D data, a 6 x 12 grid
constexpr int nx = 6;
constexpr int ny = 12;

// Return this in event of a problem
constexpr int nc_err = 2;

int main() {
  // The default behavior of the C++ API is to throw an exception if
  // an error occurs
  try {
    // This is the data array we will write. It will just be filled
    // with a progression of numbers for this example.
    int dataOut[nx][ny];

    // Create some pretend data. If this wasn't an example program, we
    // would have some real data to write, for example, model output.
    for (int i = 0; i < nx; i++) {
      for (int j = 0; j < ny; j++) {
        dataOut[i][j] = i * ny + j;
      }
    }

    // Create the file. The Replace parameter tells netCDF to overwrite
    // this file, if it already exists.
    netCDF::NcFile dataFile("simple_xy.nc", netCDF::NcFile::replace);

    // Create netCDF dimensions
    auto xDim = dataFile.addDim("x", nx);
    auto yDim = dataFile.addDim("y", ny);

    // Define the variable. The type of the variable in this case is
    // ncInt (32-bit integer)
    auto data = dataFile.addVar("data", netCDF::ncInt, {xDim, yDim});

    // Write the data to the file. Although netCDF supports reading
    // and writing subsets of data, in this case we write all the data
    // in one operation.
    data.putVar(dataOut);

    // The file will be automatically close when the NcFile object goes
    // out of scope. This frees up any internal netCDF resources
    // associated with the file, and flushes any buffers.
  } catch (netCDF::exceptions::NcException &e) {
    std::cout << e.what() << std::endl;
    return nc_err;
  }

  // Now read the data back in
  try {
    // This is the array we will read into
    int dataIn[nx][ny];

    // Open the file for read access
    netCDF::NcFile dataFile("simple_xy.nc", netCDF::NcFile::read);

    // Retrieve the variable named "data"
    auto data = dataFile.getVar("data");
    if (data.isNull())
      return nc_err;
    data.getVar(dataIn);

    // Check the values.
    for (int i = 0; i < nx; i++) {
      for (int j = 0; j < ny; j++) {
        if (dataIn[i][j] != i * ny + j) {
          return nc_err;
        }
      }
    }
  } catch (netCDF::exceptions::NcException &e) {
    std::cout << e.what() << std::endl;
    return nc_err;
  }
}
```
