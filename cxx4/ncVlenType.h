#include <string>
#include "ncType.h"
#include "netcdf.h"

#ifndef NcVlenTypeClass
#define NcVlenTypeClass


namespace netCDF
{
  class NcGroup;  // forward declaration.

  /*! Class represents a netCDF VLEN type */
  class NcVlenType : public NcType
  {
  public:
    NcVlenType() = default;
    NcVlenType(const NcVlenType& rhs) = default;
    NcVlenType(NcVlenType&& rhs) = default;
    NcVlenType& operator=(const NcVlenType& rhs) = default;
    NcVlenType& operator=(NcVlenType&& rhs) = default;
    ~NcVlenType() = default;

    /*! 
      Constructor.
      The vlen Type must already exist in the netCDF file. New netCDF vlen types can be added 
      using NcGroup::addNcVlenType();
      \param grp        The parent group where this type is defined.
      \param name       Name of new type.
    */
    NcVlenType(const NcGroup& grp, const std::string& name);

    /*! 
      Constructor.
      Constructs from the base type NcType object. Will throw an exception if the NcType is not the base of a Vlen type.
      \param ncType     A Nctype object.
    */
    NcVlenType(const NcType& ncType);
      
    /*! 
      Assignment operator.
      This assigns from the base type NcType object. Will throw an exception if the NcType is not the base of a Vlen type.
    */
    NcVlenType& operator=(const NcType& rhs);
    /*! Returns the base type. */
    NcType  getBaseType() const;
  };
  
}

#endif
