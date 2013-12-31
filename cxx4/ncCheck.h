#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifndef NcCheckFunction
#define NcCheckFunction

namespace netCDF
{
  /*! 
    Function checks error code and if necessary throws an exception.
    \param retCode Integer value returned by %netCDF C-routines.
    \param file    The name of the file from which this call originates.
    \param line    The line number in the file from which this call originates.
  */
  void ncCheck(int retCode, const char* file, int line);

  /*! 
    Function checks if the file (group) is in define mode.
    If not, it places it in the define mode.
    While this is automatically done by the underlying C API
    for netCDF-4 files, the netCDF-3 files still need this call.
  */
  void ncCheckDefineMode(int ncid);

  /*! 
    Function checks if the file (group) is in data mode.
    If not, it places it in the data mode.
    While this is automatically done by the underlying C API
    for netCDF-4 files, the netCDF-3 files still need this call.
  */
  void ncCheckDataMode(int ncid);

};

#endif
