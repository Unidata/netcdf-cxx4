#include "ncFile.h"
#include "ncCheck.h"
#include "ncException.h"
#include "ncByte.h"
#include<iostream>
#include<string>
#include<sstream>
#include<vector>
using namespace std;
using namespace netCDF;
using namespace netCDF::exceptions;

// destructor
NcFile::~NcFile()
{
  // destructor may be called due to an exception being thrown
  // hence throwing an exception from within a destructor
  // causes undefined behaviour! so just printing a warning message
  try
  {
    close();
  }
  catch (NcException &e)
  {
    cerr << e.what() << endl;
  }
}

void NcFile::close()
{
  if (!nullObject) {
    ncCheck(nc_close(myId),__FILE__,__LINE__);
  }

  nullObject = true;
}

// Constructor generates a null object.
NcFile::NcFile() :
    NcGroup()  // invoke base class constructor
{}

// constructor
NcFile::NcFile(const string& filePath, const FileMode fMode)
{
  open(filePath, fMode);
}

// constructor
NcFile::NcFile(const string& filePath, const int ncFileFlags)
{
  open(filePath, ncFileFlags);
}

/*! Open a file from a path and an NC_FLAG
 *
 * This will allow for fine-grained control by the user.
 *
 *
 */
void NcFile::open(const string& filePath, int ncFileFlags) {
  if(!nullObject)
    close();

  ncCheck(nc_open(filePath.c_str(), ncFileFlags, &myId),__FILE__,__LINE__);

  nullObject=false;
}


// open a file from path and mode
void NcFile::open(const string& filePath, const FileMode fMode)
{
  if (!nullObject)
    close();



  switch (fMode)
    {
    case NcFile::write:
      ncCheck(nc_open(filePath.c_str(), NC_WRITE, &myId),__FILE__,__LINE__);
      break;
    case NcFile::read:
      ncCheck(nc_open(filePath.c_str(), NC_NOWRITE, &myId),__FILE__,__LINE__);
      break;
    case NcFile::newFile:
      ncCheck(nc_create(filePath.c_str(), NC_NETCDF4 | NC_NOCLOBBER, &myId),__FILE__,__LINE__);
      break;
    case NcFile::replace:
      ncCheck(nc_create(filePath.c_str(), NC_NETCDF4 | NC_CLOBBER, &myId),__FILE__,__LINE__);
      break;
    }


  nullObject=false;
}

// constructor with file type specified
NcFile::NcFile(const string& filePath, const FileMode fMode, const FileFormat fFormat )
{
  open(filePath, fMode, fFormat);
}


/*! Allow for the explicit creation of a file using a path and NC_ file flags from netcdf.h
 *
 * @author wfisher
 */
void NcFile::create(const string& filePath, const int ncFileFlags) {
  if(!nullObject)
    close();

  ncCheck(nc_create(filePath.c_str(),ncFileFlags,&myId),__FILE__,__LINE__);


  nullObject=false;
}

void NcFile::open(const string& filePath, const FileMode fMode, const FileFormat fFormat )
{
  if (!nullObject)
    close();

  int format;
  switch (fFormat)
    {
    case NcFile::classic:
	format = 0;
	break;
    case NcFile::classic64:
	format = NC_64BIT_OFFSET;
	break;
    case NcFile::nc4:
	format = NC_NETCDF4;
	break;
    case NcFile::nc4classic:
	format = NC_NETCDF4 | NC_CLASSIC_MODEL;
	break;
    }
  switch (fMode)
    {
    case NcFile::write:
      ncCheck(nc_open(filePath.c_str(), format | NC_WRITE, &myId),__FILE__,__LINE__);
      break;
    case NcFile::read:
      ncCheck(nc_open(filePath.c_str(), format | NC_NOWRITE, &myId),__FILE__,__LINE__);
      break;
    case NcFile::newFile:
      ncCheck(nc_create(filePath.c_str(), format | NC_NOCLOBBER, &myId),__FILE__,__LINE__);
      break;
    case NcFile::replace:
      ncCheck(nc_create(filePath.c_str(), format | NC_CLOBBER, &myId),__FILE__,__LINE__);
      break;
    }

  nullObject=false;
}

// Synchronize an open netcdf dataset to disk
void NcFile::sync(){
  ncCheck(nc_sync(myId),__FILE__,__LINE__);
}
// Set fill mode for netCDF dataset open for writing and return current fill mode
void NcFile::set_Fill(int fillmode, int *old_modep){
  ncCheck(nc_set_fill(myId, fillmode, old_modep),__FILE__,__LINE__);
}


// Put open netCDF dataset into define mode
void NcFile::redef(){
  ncCheck(nc_redef(myId),__FILE__,__LINE__);
}

// Leave define mode, used for classic model
void NcFile::enddef() {
    ncCheck(nc_enddef(myId),__FILE__,__LINE__);
}

string NcFile::getPath() const
{
    size_t pathLength;
    ncCheck(nc_inq_path(myId, &pathLength, NULL),__FILE__,__LINE__);

    vector<char> pathCString(pathLength + 1);
    ncCheck(nc_inq_path(myId, NULL, pathCString.data()),__FILE__,__LINE__);

    return string(pathCString.data());
}
