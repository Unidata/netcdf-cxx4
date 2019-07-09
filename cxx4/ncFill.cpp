#include <string>
#include <iostream>
#include <sstream>

#include "ncFill.h"
#include "ncCheck.h"
#include "netcdf.h"

using namespace std;
using namespace netCDF;

NcFill::~NcFill() {

};

void NcFill::set_Fill( int ncid, int fillmode, int *old_modep ) {

  ncCheck(nc_set_fill(ncid, fillmode, old_modep ),__FILE__,__LINE__);

  }
