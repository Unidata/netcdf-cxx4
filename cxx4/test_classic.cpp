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
      cout << "Test creation of classic format file" << endl;
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

         // and inserting some data that needs leaving the define mode
         cout << "testing the swith to DATA mode..." << endl;
         int arr[] = {1,2,3,4,5,6,7,8,9,10,11};
         var_gw.putVar(arr);
      }

      // Now test reading.
      {
	 NcFile ncFile("test_classic.nc", NcFile::read);

	 if (ncFile.getVarCount() != 1)
	    throw NcException( "Holy Mother of Pearl!", __FILE__, __LINE__);
      }

      // and redefinition
      {
        NcFile ncFile("test_classic.nc", NcFile::write);
        cout << "testing the swith to DEFINE mode..." << endl;
        ncFile.putAtt(string("name"),string("value"));
      }

      cout << "    -----------   passed\n";
   }
   catch(NcException& e)
   {
      cout << "Error!\n";
      return e.errorCode();
   }
}
