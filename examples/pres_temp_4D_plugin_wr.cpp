/* This is part of the netCDF package.
   Copyright 2006 University Corporation for Atmospheric Research/Unidata.
   See COPYRIGHT file for conditions of use.

   This is an example program which writes some 4D pressure and
   temperatures. This example demonstrates the netCDF C++ API.

   This is part of the netCDF tutorial:
   https://docs.unidata.ucar.edu/netcdf-c/current/tutorial_8dox.html

   Full documentation of the netCDF C++ API can be found at:
   https://docs.unidata.ucar.edu/netcdf-cxx

   $Id: pres_temp_4D_wr.cpp,v 1.6 2010/02/11 22:36:42 russ Exp $
*/

#include <netcdf>
#include <iostream>
#include <string>
using namespace std;
using namespace netCDF;
using namespace netCDF::exceptions;

// This is the name of the data file we will create.
#define FILE_NAME "pres_temp_plugin_4D.nc"

// We are writing 4D data, a 2 x 6 x 12 lvl-lat-lon grid, with 2
// timesteps of data.
#define NDIMS    4
#define NLVL     2
#define NLAT     6
#define NLON     12
#define NREC     2

// Filter specs.
#define BZIP2_ID 307
#define BZIP2_LEVEL 9
#define BZIP2_NPARAMS 1
unsigned int level = BZIP2_LEVEL;
unsigned int idp = BZIP2_ID;
size_t nparamsp = BZIP2_NPARAMS;

// Names of things.
constexpr auto LVL_NAME = "level";
constexpr auto LAT_NAME = "latitude";
constexpr auto LON_NAME = "longitude";
constexpr auto REC_NAME = "time";
constexpr auto PRES_NAME = "pressure";
constexpr auto TEMP_NAME = "temperature";
constexpr auto MAX_ATT_LEN = 80;
// These are used to construct some example data.
constexpr float SAMPLE_PRESSURE = 900;
constexpr float SAMPLE_TEMP = 9.0;
constexpr float START_LAT = 25.0;
constexpr float START_LON = -125.0;


string  UNITS = "units";
string  DEGREES_EAST =  "degrees_east";
string  DEGREES_NORTH = "degrees_north";


// For the units attributes.
string PRES_UNITS = "hPa";
string TEMP_UNITS = "celsius";
string LAT_UNITS = "degrees_north";
string LON_UNITS = "degrees_east";

// Return this code to the OS in case of failure.
#define NC_ERR 2

int main()
{
  nc_set_log_level(5);
  // We will write latitude and longitude fields.
   float lats[NLAT],lons[NLON];

   // Program variables to hold the data we will write out. We will
   // only need enough space to hold one timestep of data; one record.
   float pres_out[NLVL][NLAT][NLON];
   float temp_out[NLVL][NLAT][NLON];

   int i=0;  //used in the data generation loop

   // create some pretend data. If this wasn't an example program, we
   // would have some real data to write for example, model output.
   for (int lat = 0; lat < NLAT; lat++) {
     lats[lat] = START_LAT + 5.f * static_cast<float>(lat);
   }
   for (int lon = 0; lon < NLON; lon++) {
     lons[lon] = START_LON + 5.f * static_cast<float>(lon);
   }

   for (int lvl = 0; lvl < NLVL; lvl++)
     for (int lat = 0; lat < NLAT; lat++)
       for (int lon = 0; lon < NLON; lon++)
	 {
	   pres_out[lvl][lat][lon] = SAMPLE_PRESSURE + static_cast<float>(i);
           temp_out[lvl][lat][lon] = SAMPLE_TEMP + static_cast<float>(i++);
	 }

   try
   {


      // Create the file.
      NcFile test(FILE_NAME, NcFile::replace);
      nc_set_log_level(5);
      // Define the dimensions. NetCDF will hand back an ncDim object for
      // each.
      NcDim lvlDim = test.addDim(LVL_NAME, NLVL);
      NcDim latDim = test.addDim(LAT_NAME, NLAT);
      NcDim lonDim = test.addDim(LON_NAME, NLON);
      NcDim recDim = test.addDim(REC_NAME);  //adds an unlimited dimension

      // Define the coordinate variables.
      NcVar latVar = test.addVar(LAT_NAME, ncFloat, latDim);
      NcVar lonVar = test.addVar(LON_NAME, ncFloat, lonDim);

      // Define units attributes for coordinate vars. This attaches a
      // text attribute to each of the coordinate variables, containing
      // the units.
      latVar.putAtt(UNITS, DEGREES_NORTH);
      lonVar.putAtt(UNITS, DEGREES_EAST);

      // Define the netCDF variables for the pressure and temperature
      // data.
      vector<NcDim> dimVector;
      dimVector.push_back(recDim);
      dimVector.push_back(lvlDim);
      dimVector.push_back(latDim);
      dimVector.push_back(lonDim);
      NcVar pressVar = test.addVar(PRES_NAME, ncFloat, dimVector);
      NcVar tempVar = test.addVar(TEMP_NAME, ncFloat, dimVector);

      // Define units attributes for coordinate vars. This attaches a
      // text attribute to each of the coordinate variables, containing
      // the units.
      pressVar.putAtt(UNITS, PRES_UNITS);
      tempVar.putAtt(UNITS, TEMP_UNITS);

      // Write the coordinate variable data to the file.

      //latVar.putVar(lats);
      //lonVar.putVar(lons);
      vector<size_t> chunks;
      for(int i = 0; i < NDIMS; i++) {
        chunks.push_back(4);
      }

      latVar.setChunking(NcVar::nc_CHUNKED,chunks);
      //Testing the filter ability in a write function
      cout<<"BZIP2_ID: " << BZIP2_ID <<"BZIP2_NPARAMS: "<< BZIP2_NPARAMS << " level: "<< level;
      latVar.setFilter(BZIP2_ID,BZIP2_NPARAMS,&level);

      latVar.getFilter(&idp,&nparamsp, &level);



      latVar.putVar(lats);
      lonVar.putVar(lons);

      // Write the pretend data. This will write our surface pressure and
      // surface temperature data. The arrays only hold one timestep
      // worth of data. We will just rewrite the same data for each
      // timestep. In a real application, the data would change between
      // timesteps.
      vector<size_t> startp,countp;
      startp.push_back(0);
      startp.push_back(0);
      startp.push_back(0);
      startp.push_back(0);
      countp.push_back(1);
      countp.push_back(NLVL);
      countp.push_back(NLAT);
      countp.push_back(NLON);
      for (size_t rec = 0; rec < NREC; rec++)
        {
          startp[0]=rec;
          pressVar.putVar(startp,countp,pres_out);
          tempVar.putVar(startp,countp,temp_out);
        }

      // The file is automatically closed by the destructor. This frees
      // up any internal netCDF resources associated with the file, and
      // flushes any buffers.

      //cout << "*** SUCCESS writing example file " << FILE_NAME << "!" << endl;
      test.close();
      return 0;
   }
   catch(NcException& e)
   {
      cout<<"FAILURE**************************\n";
      cout << e.what() << endl;
      return NC_ERR;
   }
}
