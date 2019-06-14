//This will be the first test for creation of a nc_def_var_filter
//call function in the C++ library

#include <string>
#include <iostream>
#include <sstream>

#include "ncFilter.h"
#include "ncCheck.h"

using namespace std;
using namespace netCDF;

NcFilter::~NcFilter();

// open a file from path and mode
void NcFilter::setFilter( unsigned int id, size_t nparams,
            const unsigned int* parms) const
{
  ncCheck(nc_def_var_filter(groupId,myId,id,nparams,parms),__FILE__,__LINE__);
}

void NcFilter::inquire_v()
{
  ncCheck(nc_inq_var_filter(ncid, varid, &filterid,  &nparams,NULL));
}
