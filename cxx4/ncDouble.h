#ifndef NcDoubleClass
#define NcDoubleClass

#include "ncType.h"

namespace netCDF
{
  
  /*! Class represents a netCDF atomic Double type. */
  class NcDouble : public NcType
  {
  public: 
    
    /*! equivalence operator */
    bool operator==(const NcDouble & rhs);
    
    /*!  destructor */
    ~NcDouble();
    
    /*! Constructor */
    NcDouble();
  };

  /*! A global instance  of the NcDouble class within the netCDF namespace. */
  extern NcDouble ncDouble;

}
#endif
