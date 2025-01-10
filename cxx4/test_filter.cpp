// Purpose: Converts ida3 format xma data to netcdf4
// Usage:   xma2netcdf <shot number>

#include <cstdlib>
#include <iostream>
#include <ncFile.h>
#include <ncVar.h>
#include <ncException.h>
#include <netcdf_filter.h>
#include <string>
#include <netcdf>
#include "test_utilities.h"
using namespace std;
using namespace netCDF;
using namespace netCDF::exceptions;

// Filter specs.
#define NDIMS    4
#define NLAT     6
#define LAT_NAME "latitude"
string  UNITS = "units";
string  DEGREES_NORTH = "degrees_north";

int main()
{
  try
    {
      NcFile test("pres_temp_plugin_4D.nc", NcFile::replace);
      nc_set_log_level(5);
      // Define the dimensions. NetCDF will hand back an ncDim object for
      // each.
      NcDim latDim = test.addDim(LAT_NAME, NLAT);
      // Define the coordinate variables.
      NcVar latVar = test.addVar(LAT_NAME, ncFloat, latDim);

      // Define units attributes for coordinate vars. This attaches a
      // text attribute to each of the coordinate variables, containing
      // the units.
      latVar.putAtt(UNITS, DEGREES_NORTH);


      vector<size_t> chunks;
      for(int i = 0; i < NDIMS; i++) {
        chunks.push_back(4);
      }

      latVar.setChunking(NcVar::nc_CHUNKED,chunks);

      constexpr unsigned int set_filter_id = H5Z_FILTER_DEFLATE;
      constexpr unsigned int set_filter_nparams = 1;
      constexpr unsigned int set_filter_level = 9;

      cout<<"Setting Filter... ";
      latVar.setFilter(set_filter_id, set_filter_nparams, &set_filter_level);
      cout<<"Success\n";

      cout<<"Getting filter... ";
      unsigned int level {};
      unsigned int idp {};
      size_t nparamsp {};
      latVar.getFilter(&idp, &nparamsp, &level);

      bool success = true;
      if (idp != set_filter_id) {
        cout << "got wrong filter ID (got " << set_filter_id
             << ", expected " << set_filter_id << ")\n";
        success &= false;
      }
      if (nparamsp != set_filter_nparams) {
        cout << "got wrong number of filter parameters (got " << nparamsp
             << ", expected " << set_filter_nparams << ")\n";
        success &= false;
      }
      if (level != set_filter_level) {
        cout << "got wrong filter level (got " << level
             << ", expected " << set_filter_level << ")\n";
        success &= false;
      }

      if (success) {
        cout<<"Success\n";
      } else {
        cout << "Failure\n";
        return EXIT_FAILURE;
      }
    }
  catch (NcException& e)
    {
      cout << e.what() << endl;
      return e.errorCode();
    }
}
