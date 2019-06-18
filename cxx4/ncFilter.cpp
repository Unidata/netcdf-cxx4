//This will be the first test for creation of a nc_def_var_filter
//call function in the C++ library

#include <string>
#include <iostream>
#include <sstream>

#include "ncFilter.h"
#include "ncCheck.h"
#include "netcdf.h"

using namespace std;
using namespace netCDF;

NcFilter::~NcFilter() {

};

// open a file from path and mode
void NcFilter::setFilter(unsigned int ncid, unsigned int varid, unsigned int filterId, size_t nparams, const unsigned int* parms)
{
  ncCheck(nc_def_var_filter(ncid,varid,filterId,nparams,parms),__FILE__,__LINE__);
}

void NcFilter::getFilter(unsigned int ncid, unsigned int varid, unsigned int* idp, size_t* nparamsp, unsigned int* params)
{
  ncCheck(nc_inq_var_filter(ncid, varid, idp, nparamsp, params),__FILE__,__LINE__);
}
