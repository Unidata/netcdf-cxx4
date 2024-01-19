#include <string>
#include "ncType.h"
#include "netcdf.h"

#ifndef NcOpaqueTypeClass
#define NcOpaqueTypeClass


namespace netCDF
{
  class NcGroup;  // forward declaration.

  /*! Class represents a netCDF opaque type */
  class NcOpaqueType : public NcType
  {
  public:
    NcOpaqueType() = default;
    ~NcOpaqueType() = default;
    NcOpaqueType(const NcOpaqueType& rhs) = default;
    NcOpaqueType(NcOpaqueType&& rhs) = default;
    NcOpaqueType& operator=(const NcOpaqueType& rhs) = default;
    NcOpaqueType& operator=(NcOpaqueType&& rhs) = default;

    /*! 
      Constructor.
      The opaque Type must already exist in the netCDF file. New netCDF opaque types #
      can be added using NcGroup::addNcOpaqueType();
      \param grp        The parent group where this type is defined.
      \param name       Name of new type.
    */
    NcOpaqueType(const NcGroup& grp, const std::string& name);

    /*! 
      Constructor.
      Constructs from the base type NcType object. Will throw an exception if the NcType is not the base of a Opaque type.
      \param ncType     A Nctype object.
    */
    NcOpaqueType(const NcType& ncType);
      
    /*! 
      Assignment operator.
      This assigns from the base type NcType object. Will throw an exception if the NcType is not the base of an Opaque type.
    */
    NcOpaqueType& operator=(const NcType& rhs);

    /*! Returns the size of the opaque type in bytes. */
    size_t  getTypeSize() const;

  };
  
}

#endif
