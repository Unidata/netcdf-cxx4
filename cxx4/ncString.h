#include "ncType.h"

#ifndef NcStringClass
#define NcStringClass

namespace netCDF
{
  
  /*! Class represents a netCDF atomic String type. */
  class NcString : public NcType
  {
  public: 
    
    /*! equivalence operator */
    bool operator==(const NcString & rhs);
    
    /*! Constructor */
    NcString();
  };

  /*! A global instance  of the NcString class within the netCDF namespace. */
  extern NcString ncString;

}
#endif
