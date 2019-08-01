#include <string>
#include <iostream>
#include <sstream>

#include "ncFilter.h"
#include "ncCheck.h"
#include "netcdf.h"

using namespace std;
using namespace netCDF;

// Constructor for filtering object
NcFilter::~NcFilter() {

};

/* Define a new variable filter for either compression or decompression. The below
method allows for setting of the filter which is to be used wen writing a variable. */
void NcFilter::setFilter(unsigned int ncid, unsigned int varid, unsigned int filterId, size_t nparams, const unsigned int* parms)
{
  ncCheck(nc_def_var_filter(ncid,varid,filterId,nparams,parms),__FILE__,__LINE__);
}

/* This second API method makes it possible to query a varible to obtain information about
any associated filter using this signature */
void NcFilter::getFilter(unsigned int ncid, unsigned int varid, unsigned int* idp, size_t* nparamsp, unsigned int* params)
{
  ncCheck(nc_inq_var_filter(ncid, varid, idp, nparamsp, params),__FILE__,__LINE__);
}
