#include <string>
#include "netcdf.h"

#ifndef NcDimClass
#define NcDimClass


namespace netCDF
{
  class NcGroup;  // forward declaration.

  /*! Class represents a netCDF dimension */
  class NcDim   {

  public:
    NcDim () = default;

    /*!
      Constructor for a dimension .
      The dimension must already exist in the netCDF file. New netCDF variables can be added using NcGroup::addNcDim();
      \param grp    Parent NcGroup object.
      \param dimId  Id of the NcDim object.
    */
    NcDim(const NcGroup& grp, int dimId);

    /*! equivalence operator */
    bool operator==(const NcDim& rhs) const;

    /*!  != operator */
    bool operator!=(const NcDim& rhs) const;

    /*! The name of this dimension.*/
    std::string getName() const;

    /*! The netCDF Id of this dimension. */
    int getId() const {return myId;};

    /*! Gets a  NcGroup object of the parent group. */
    NcGroup getParentGroup() const;

    /*! Returns true if this is an unlimited dimension */
    bool isUnlimited() const;

    /*! The size of the dimension; for unlimited, this is the number of records written so far. */
    size_t  getSize() const;

    /*!renames the dimension */
    void rename( const std::string& newName);

    /*! Returns true if this object is null (i.e. it has no contents); otherwise returns false. */
    bool isNull() const  {return nullObject;}

    /*! comparator operator  */
    friend bool operator<(const NcDim& lhs,const NcDim& rhs);

    /*! comparator operator  */
    friend bool operator>(const NcDim& lhs,const NcDim& rhs);

  private:
    bool nullObject{true};
    int myId{-1};
    int groupId{-1};
  };
}


#endif
