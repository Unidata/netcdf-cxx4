#include <iostream>
#include <string>
#include "netcdf.h"
#include "ncGroup.h"

#ifndef NcFillClass
#define NcFillClass

/* Change fill-value to improve write preformace. This member function is a wrapper
to the C library's nc_set_fill() function. *NOT TO BE CONFUSED WITH setFill() IN
THE ncVar FILE*. The function nc_set_fill() sets the fill
mode for a netCDF dataset open for writing and returns the current fill mode in a return
parameter. The fill mode can be specified as either NC_FILL or NC_NOFILL. The default
behavior corresponding to NC_FILL is that data is pre-filled with fill values, that is
fill values are written when you create non-record variables or when you write a value
beyond data that has not yet been written. */

namespace netCDF
{
  class NcFill
    {
      public:
        ~NcFill();

        //constructor
        NcFill();

        //member function
        void set_Fill(int, int, int*);
      };

}
#endif
