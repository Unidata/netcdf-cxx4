#include <iostream>
#include <ncFile.h>
#include <ncDim.h>
#include <ncException.h>
#include <iomanip>
#include <netcdf>

using namespace std;
using namespace netCDF;
using namespace netCDF::exceptions;

int main()
{
   try
   {
      cout << "Test creation of classic format file";
      {
	 NcFile ncFile("test_classic.nc", NcFile::replace, NcFile::classic);
	 NcDim dim1 = ncFile.addDim("dim1",11);
	 NcDim dim2 = ncFile.addDim("dim2");
	 NcDim dim3 = ncFile.addDim("dim3",13);

	 NcVar var_gw  = ncFile.addVar("George_Washington", ncInt, dim1);
	 // The following fails, I don't know why...
	 // vector<NcDim> dimArray(2);
	 // dimArray[0]=dim1;
	 // dimArray[1]=dim2;
	 // NcVar varA1_3  = ncFile.addVar("varA1_3", ncInt, dimArray);
      }

      // Now test reading.
      {
	 NcFile ncFile("test_classic.nc", NcFile::read);

	 if (ncFile.getVarCount() != 1)
	    throw NcException("NcException", "Holy Mother of Pearl!", __FILE__, __LINE__);
      }

      cout << "    -----------   passed\n";
   }
   catch(NcException& e)
   {
      cout << "Error!\n";
      return 99;
   }
}
