#include "netcdf.h"
#include <ncException.h>
using namespace std;
using namespace netCDF::exceptions;

//  C++ API for netCDF4.
namespace netCDF
{
  // function checks error code and if necessary throws appropriate exception.
  void ncCheck(int retCode, const char* file, int line){
    if (retCode==NC_NOERR)
      return;

    const char* msg = 0;
    if (NC_ISSYSERR(retCode)){
      msg = std::strerror(retCode);
      msg = msg ? msg : "Unknown system error";
    }else{
      msg = nc_strerror(retCode);
    }

    throw NcException(retCode, msg, file, line);
  }
}
