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
      public:
        ~NcFilter();

        //constructor
        NcFilter ();

        //member function
        void setFilter(unsigned int, unsigned int, unsigned int, size_t, const unsigned int*);
        void getFilter(unsigned int, unsigned int, unsigned int*, size_t*, unsigned int*);
      };

}
#endif
