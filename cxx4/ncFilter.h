#include <iostream>
#include <string>
#include "netcdf.h"
#include "ncGroup.h"

#ifndef NcFilterClass
#define NcFilterClass

namespace netCDF
{
  class NcFilter
    {
      //constructor
      NcFilter ();
      public:
        //member function
        void setFilter();
        void getFilter();
    };

}
#endif
