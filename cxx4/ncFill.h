#include <iostream>
#include <string>
#include "netcdf.h"
#include "ncGroup.h"

#ifndef NcFillClass
#define NcFillClass

namespace netCDF
{
  class NcFill
    {
      public:
        ~NcFill();

        //constructor
        NcFill();

        //member functions
        void set_Fill(int, int, int*);
      };

}
#endif
