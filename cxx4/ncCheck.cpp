#include <cstring>
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

    switch(retCode) {
    case NC_EBADID          : throw NcBadId(msg,file,line);
    case NC_ENFILE          : throw NcNFile(msg,file,line);
    case NC_EEXIST          : throw NcExist(msg,file,line);
    case NC_EINVAL          : throw NcInvalidArg(msg,file,line);
    case NC_EPERM           : throw NcInvalidWrite(msg,file,line);
    case NC_ENOTINDEFINE    : throw NcNotInDefineMode(msg,file,line);
    case NC_EINDEFINE       : throw NcInDefineMode(msg,file,line);
    case NC_EINVALCOORDS    : throw NcInvalidCoords(msg,file,line);
    case NC_EMAXDIMS        : throw NcMaxDims(msg,file,line);
    case NC_ENAMEINUSE      : throw NcNameInUse(msg,file,line);
    case NC_ENOTATT         : throw NcNotAtt(msg,file,line);
    case NC_EMAXATTS        : throw NcMaxAtts(msg,file,line);
    case NC_EBADTYPE        : throw NcBadType(msg,file,line);
    case NC_EBADDIM         : throw NcBadDim(msg,file,line);
    case NC_EUNLIMPOS       : throw NcUnlimPos(msg,file,line);
    case NC_EMAXVARS        : throw NcMaxVars(msg,file,line);
    case NC_ENOTVAR         : throw NcNotVar(msg,file,line);
    case NC_EGLOBAL         : throw NcGlobal(msg,file,line);
    case NC_ENOTNC          : throw NcNotNCF(msg,file,line);
    case NC_ESTS            : throw NcSts(msg,file,line);
    case NC_EMAXNAME        : throw NcMaxName(msg,file,line);
    case NC_EUNLIMIT        : throw NcUnlimit(msg,file,line);
    case NC_ENORECVARS      : throw NcNoRecVars(msg,file,line);
    case NC_ECHAR           : throw NcChar(msg,file,line);
    case NC_EEDGE           : throw NcEdge(msg,file,line);
    case NC_ESTRIDE         : throw NcStride(msg,file,line);
    case NC_EBADNAME        : throw NcBadName(msg,file,line);
    case NC_ERANGE          : throw NcRange(msg,file,line);
    case NC_ENOMEM          : throw NcNoMem(msg,file,line);
    case NC_EVARSIZE        : throw NcVarSize(msg,file,line);
    case NC_EDIMSIZE        : throw NcDimSize(msg,file,line);
    case NC_ETRUNC          : throw NcTrunc(msg,file,line);

      // The following are specific netCDF4 errors.
    case NC_EHDFERR         : throw NcHdfErr(msg,file,line);
    case NC_ECANTREAD       : throw NcCantRead(msg,file,line);
    case NC_ECANTWRITE      : throw NcCantWrite(msg,file,line);
    case NC_ECANTCREATE     : throw NcCantCreate(msg,file,line);
    case NC_EFILEMETA       : throw NcFileMeta(msg,file,line);
    case NC_EDIMMETA        : throw NcDimMeta(msg,file,line);
    case NC_EATTMETA        : throw NcAttMeta(msg,file,line);
    case NC_EVARMETA        : throw NcVarMeta(msg,file,line);
    case NC_ENOCOMPOUND     : throw NcNoCompound(msg,file,line);
    case NC_EATTEXISTS      : throw NcAttExists(msg,file,line);
    case NC_ENOTNC4         : throw NcNotNc4(msg,file,line);
    case NC_ESTRICTNC3      : throw NcStrictNc3(msg,file,line);
    case NC_EBADGRPID       : throw NcBadGroupId(msg,file,line);
    case NC_EBADTYPID       : throw NcBadTypeId(msg,file,line);                       // netcdf.h file inconsistent with documentation!!
    case NC_EBADFIELD       : throw NcBadFieldId(msg,file,line);                     // netcdf.h file inconsistent with documentation!!
      //  case NC_EUNKNAME        : throw NcUnkownName("Cannot find the field id.",file,line);   // netcdf.h file inconsistent with documentation!!

    case NC_ENOGRP          : throw NcEnoGrp(msg,file,line);
    case NC_ELATEDEF        : throw NcElateDef(msg,file,line);

    default:
      throw NcException(retCode, msg, file, line);
    }
  }

  void ncCheckDefineMode(int ncid)
  {
    int status = nc_redef(ncid);
    if (status != NC_EINDEFINE) ncCheck(status, __FILE__, __LINE__);
  }

  void ncCheckDataMode(int ncid)
  {
    int status = nc_enddef(ncid);
    if (status != NC_ENOTINDEFINE) ncCheck(status, __FILE__, __LINE__);
  }
}
