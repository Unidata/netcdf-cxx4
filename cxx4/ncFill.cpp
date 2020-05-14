#include <string>
#include <iostream>
#include <sstream>

#include "ncFill.h"
#include "ncCheck.h"
#include "netcdf.h"

using namespace std;
using namespace netCDF;

/* Change fill-value to improve write preformace. This member function is a wrapper
to the C library's nc_set_fill() function. *NOT TO BE CONFUSED WITH setFill() IN
THE ncVar FILE*. The function nc_set_fill() sets the fill
mode for a netCDF dataset open for writing and returns the current fill mode in a return
parameter. The fill mode can be specified as either NC_FILL or NC_NOFILL. The default
behavior corresponding to NC_FILL is that data is pre-filled with fill values, that is
fill values are written when you create non-record variables or when you write a value
beyond data that has not yet been written. */


//NcFill constructor
NcFill::~NcFill() {

};
void NcFill::set_Fill( int ncid, int fillmode, int *old_modep ) {

  ncCheck(nc_set_fill(ncid, fillmode, old_modep ),__FILE__,__LINE__);

  }
