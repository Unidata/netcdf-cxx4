#include <string>
#include "ncType.h"
#include "ncGroup.h"
#include "ncCheck.h"
using namespace std;

extern int g_ncid;

namespace netCDF {
  //  Global comparator operator ==============
  // comparator operator
  bool operator<(const NcType& lhs,const NcType& rhs)
  {
    return false;
  }

  // comparator operator
  bool operator>(const NcType& lhs,const NcType& rhs)
  {
    return true;
  }

  const NcByte ncByte{};
  const NcUbyte ncUbyte{};
  const NcChar ncChar{};
  const NcShort ncShort{};
  const NcUshort ncUshort{};
  const NcInt ncInt{};
  const NcUint ncUint{};
  const NcInt64 ncInt64{};
  const NcUint64 ncUint64{};
  const NcFloat ncFloat{};
  const NcDouble ncDouble{};
  const NcString ncString{};
}

using namespace netCDF;

// constructor
NcType::NcType(const NcGroup& grp, const string& name) :
  nullObject (false)
{
  groupId= grp.getId();
  NcType typTmp(grp.getType(name,NcGroup::ParentsAndCurrent));
  myId = typTmp.getId();
}

// Constructor for a non-global type
NcType::NcType(const netCDF::NcGroup& grp, nc_type id):
  nullObject(false),
  myId(id),
  groupId(grp.getId())
{}


// equivalence operator
bool NcType::operator==(const NcType & rhs) const
{
  if(nullObject)
    return nullObject == rhs.nullObject;
  else
    return groupId == rhs.groupId && myId == rhs.myId;
}

//  !=  operator
bool NcType::operator!=(const NcType & rhs) const
{
  return !(*this == rhs);
}

// Gets parent group.
NcGroup  NcType::getParentGroup() const {
  if(groupId == 0) return NcGroup(); else  return NcGroup(groupId);
}

// Returns the type name.
string  NcType::getName() const{
  char charName[NC_MAX_NAME+1];
  size_t *sizep=NULL;

  /* We cannot call nc_inq_type without a valid
     netcdf file ID (ncid), which is not *groupid*.
     Working around this for now. */

  ncCheck(nc_inq_type(g_ncid,myId,charName,sizep),__FILE__,__LINE__);
  return string(charName);

};

// Returns the size in bytes
size_t NcType::getSize() const{
  char* charName=NULL;
  size_t sizep;
  ncCheck(nc_inq_type(g_ncid,myId,charName,&sizep),__FILE__,__LINE__);
  return sizep;
};

// The type class returned as an enumeration type.
NcType::ncType NcType::getTypeClass() const{
  switch (myId) {
  case NC_BYTE    : return nc_BYTE;
  case NC_UBYTE   : return nc_UBYTE;
  case NC_CHAR    : return nc_CHAR;
  case NC_SHORT   : return nc_SHORT;
  case NC_USHORT  : return nc_USHORT;
  case NC_INT     : return nc_INT;
  case NC_UINT    : return nc_UINT;
  case NC_INT64   : return nc_INT64;
  case NC_UINT64  : return nc_UINT64;
  case NC_FLOAT   : return nc_FLOAT;
  case NC_DOUBLE  : return nc_DOUBLE;
  case NC_STRING  : return nc_STRING;
  default:
    // this is a user defined type
    // establish its type class, ie whether it is: NC_VLEN, NC_OPAQUE, NC_ENUM, or NC_COMPOUND.
    char* name=NULL;
    size_t* sizep=NULL;
    nc_type* base_nc_typep=NULL;
    size_t* nfieldsp=NULL;
    int classp;
    ncCheck(nc_inq_user_type(groupId,myId,name,sizep,base_nc_typep,nfieldsp,&classp),__FILE__,__LINE__);
    return static_cast<ncType>(classp);
  }
}

// The type class returned as a string.
string NcType::getTypeClassName() const{
  ncType typeClass=getTypeClass();
  switch (typeClass) {
  case nc_BYTE    : return string("nc_BYTE");
  case nc_UBYTE   : return string("nc_UBYTE");
  case nc_CHAR    : return string("nc_CHAR");
  case nc_SHORT   : return string("nc_SHORT");
  case nc_USHORT  : return string("nc_USHORT");
  case nc_INT     : return string("nc_INT");
  case nc_UINT    : return string("nc_UINT");
  case nc_INT64   : return string("nc_INT64");
  case nc_UINT64  : return string("nc_UINT64");
  case nc_FLOAT   : return string("nc_FLOAT");
  case nc_DOUBLE  : return string("nc_DOUBLE");
  case nc_STRING  : return string("nc_STRING");
  case nc_VLEN    : return string("nc_VLEN");
  case nc_OPAQUE  : return string("nc_OPAQUE");
  case nc_ENUM    : return string("nc_ENUM");
  case nc_COMPOUND: return string("nc_COMPOUND");
  }
  // we never get here!
  return "Dummy";
}
