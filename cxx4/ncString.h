#ifndef NcStringClass
#define NcStringClass

#include "ncType.h"

namespace netCDF
{
  
  /*! Class represents a netCDF atomic String type. */
  class NcString : public NcType
  {
  public: 
    
    /*! equivalence operator */
    bool operator==(const NcString & rhs);
    
    /*! destructor */
    ~NcString();
    
    /*! Constructor */
    NcString();
  };

  /*! A global instance  of the NcString class within the netCDF namespace. */
  extern NcString ncString;

}
#endif
