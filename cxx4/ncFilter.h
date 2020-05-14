#include <iostream>
#include <string>
#include "netcdf.h"
#include "ncGroup.h"

#ifndef NcFilterClass
#define NcFilterClass

namespace netCDF
{
  /* Definition of filter class. */
  class NcFilter
    {
      public:
        ~NcFilter();

        //constructor
        NcFilter ();

        /* Member functions:
        setFilter: allows for filter definition of a variable when writing
        getFilter: querys about a filter (if any) associated with the variable
        */
        void setFilter(unsigned int, unsigned int, unsigned int, size_t, const unsigned int*);
        void getFilter(unsigned int, unsigned int, unsigned int*, size_t*, unsigned int*);
      };

}
#endif
