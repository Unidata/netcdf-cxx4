#include "ncFile.h"
#include "ncCheck.h"
#include "ncException.h"
#include "ncByte.h"
#include<iostream>
#include<string>
#include<sstream>
using namespace std;
using namespace netCDF;
using namespace netCDF::exceptions;

int g_ncid = -1;

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
    g_ncid = -1;
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

  g_ncid = myId;

  nullObject=false;
}

// constructor with file type specified
NcFile::NcFile(const string& filePath, const FileMode fMode, const FileFormat fFormat )
{
  open(filePath, fMode, fFormat);
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

  g_ncid = myId;
  nullObject=false;
}

// Synchronize an open netcdf dataset to disk
void NcFile::sync(){
  ncCheck(nc_sync(myId),__FILE__,__LINE__);
}

// Leave define mode, used for classic model
void NcFile::enddef() {
    ncCheck(nc_enddef(myId),__FILE__,__LINE__);
}
