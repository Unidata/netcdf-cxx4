#include "ncAtt.h"
#include "netcdf.h"

#ifndef NcGroupAttClass
#define NcGroupAttClass

namespace netCDF
{
  class NcGroup;  // forward declaration.

  /*! Class represents a netCDF group attribute */
  class NcGroupAtt : public NcAtt
  {
  public:
    NcGroupAtt () = default;
    NcGroupAtt(const NcGroupAtt& rhs)  = default;
    NcGroupAtt& operator= (const NcGroupAtt& rhs) = default;
    NcGroupAtt(NcGroupAtt&& rhs)  = default;
    NcGroupAtt& operator= (NcGroupAtt&& rhs) = default;
      
    /*! 
      Constructor for an existing global attribute.
      \param  grp        Parent Group object.
      \param  index      The index (id) of the attribute.
    */
    NcGroupAtt(const NcGroup& grp, const int index);
    
    /*! equivalence operator */
    bool operator== (const NcGroupAtt& rhs);
      
    /*! comparator operator */
    friend bool operator<(const NcGroupAtt& lhs,const NcGroupAtt& rhs);
    
    /*! comparator operator */
    friend bool operator>(const NcGroupAtt& lhs,const NcGroupAtt& rhs);
    
  };
  
}

#endif
