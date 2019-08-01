// Purpose: Converts ida3 format xma data to netcdf4
// Usage:   xma2netcdf <shot number>

#include <iostream>
#include <ncFile.h>
#include <ncVar.h>
#include <ncException.h>
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
#define BZIP2_ID 307
#define BZIP2_LEVEL 9
#define BZIP2_NPARAMS 1
string  UNITS = "units";
string  DEGREES_NORTH = "degrees_north";
unsigned int level = BZIP2_LEVEL;
unsigned int idp = BZIP2_ID;
size_t nparamsp = BZIP2_NPARAMS;

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

      cout<<"Setting Filter....";
      try{
        latVar.setFilter(BZIP2_ID,BZIP2_NPARAMS,&level);
        cout<<"Success."<<endl;
      } catch (NcException &e){
        cout<<"Caught unexpected exception." << endl;
        return e.errorCode();
      }

      cout<<"Getting filter...";
      try{
        latVar.getFilter(&idp,&nparamsp, &level);
        cout<<"Success."<<endl;
      } catch (NcException &e){
        cout<<"Caught unexpected exception." << endl;
        return e.errorCode();
      }
    }
  catch (NcException& e)
    {
      cout << "unknown error"<<endl;
      e.what();
      return e.errorCode();
    }
}
