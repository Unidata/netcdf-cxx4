#include "ncDim.h"
#include "ncGroup.h"
#include "ncCheck.h"
#include <algorithm>
using namespace std;


namespace netCDF {
  //  Global comparator operator ==============
  // comparator operator
  bool operator<(const NcDim& lhs,const NcDim& rhs)
  {
    return false;
  }

  // comparator operator
  bool operator>(const NcDim& lhs,const NcDim& rhs)
  {
    return true;
  }
}

using namespace netCDF;

// equivalence operator
bool NcDim::operator==(const NcDim& rhs) const
{
  if(nullObject)
    return nullObject == rhs.nullObject;
  else
    return myId == rhs.myId && groupId == rhs.groupId;
}

//  !=  operator
bool NcDim::operator!=(const NcDim & rhs) const
{
  return !(*this == rhs);
}


// Gets parent group.
NcGroup  NcDim::getParentGroup() const {
  return NcGroup(groupId);
}

// Constructor for a dimension (must already exist in the netCDF file.)
NcDim::NcDim(const NcGroup& grp, int dimId) :
  nullObject(false)
{
  groupId = grp.getId();
  myId = dimId;
}

// gets the size of the dimension, for unlimited, this is the current number of records.
size_t NcDim::getSize() const
{
  size_t dimSize;
  ncCheck(nc_inq_dimlen(groupId, myId, &dimSize),__FILE__,__LINE__);
  return dimSize;
}


// returns true if this dimension is unlimited.
bool NcDim::isUnlimited() const
{
  int numlimdims;
  int* unlimdimidsp=NULL;
  // get the number of unlimited dimensions
  ncCheck(nc_inq_unlimdims(groupId,&numlimdims,unlimdimidsp),__FILE__,__LINE__);
  if (numlimdims){
	  // get all the unlimited dimension ids in this group
	  vector<int> unlimdimid(static_cast<std::size_t>(numlimdims));
	  ncCheck(nc_inq_unlimdims(groupId,&numlimdims,&unlimdimid[0]),__FILE__,__LINE__);
	  vector<int>::iterator it;
	  // now look to see if this dimension is unlimited
	  it = find(unlimdimid.begin(),unlimdimid.end(),myId);
	  return it != unlimdimid.end();
  }
  return false;
}


// gets the name of the dimension.
string NcDim::getName() const
{
  char dimName[NC_MAX_NAME+1];
  ncCheck(nc_inq_dimname(groupId, myId, dimName),__FILE__,__LINE__);
  return string(dimName);
}

// renames this dimension.
void NcDim::rename(const string& name)
{
  ncCheck(nc_rename_dim(groupId, myId, name.c_str()),__FILE__,__LINE__);
}
