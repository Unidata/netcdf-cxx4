#include <exception>
#include <string>
#include <iostream>

#ifndef NcExceptionClasses
#define NcExceptionClasses

namespace netCDF
{

  //!  Exception classes.
  /*!
    These exceptions are thrown if the netCDF-4 API encounters an error.
  */
  namespace exceptions
  {

    /*!
      A NcException is thrown if an error is encountered. An exception object will be thrown 
      as a result of an unsatisfactory return from a call to one of the netcdf c-routines or
      other errors encountered. The return value of a call to the c-routines can be retrieved
      by the errorCode method. If the exception originates from other errors, errorCode will return 0.
    */
    class NcException : public std::exception {
    public:
      //NcException(const string& complaint,const char* fileName,int lineNumber);
      NcException(const char* complaint,const char* fileName,int lineNumber);
      NcException(int errorCode, const char* complaint,const char* fileName,int lineNumber);
      NcException(const NcException& e) throw();
      NcException& operator=(const NcException& e) throw();
      virtual ~NcException() throw();
      const char* what() const throw();
      int errorCode() const throw();
    private:
      std::string* what_msg;
      int ec;
    };

  }
}

#endif

