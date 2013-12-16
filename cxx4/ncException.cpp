#include <ncException.h>
#include <sstream>
#include <netcdf.h>
using namespace std;
using namespace netCDF;
using namespace netCDF::exceptions;


// Default object thrown if a netCDF exception is encountered.
/*NcException::NcException(const string& complaint,const char* fileName,int lineNumber)
  : what_msg(NULL)
  , ec(0)
{
	try{
		std::ostringstream oss;
		oss << lineNumber;
		what_msg = new std::string(complaint+"\nfile: "+fileName+"  line:"+oss.str());
	}catch(...){
		what_msg = NULL;
	}
}*/

NcException::NcException(const char* complaint,const char* fileName,int lineNumber)
  : what_msg(NULL)
  , ec(0)
{
  try{
    std::ostringstream oss;
    oss << lineNumber;
    what_msg = new std::string(complaint?complaint:"");
    what_msg->append("\nfile: ");
    what_msg->append(fileName);
    what_msg->append("  line:");
    what_msg->append(oss.str());
  }catch(...){
    what_msg = NULL;
  }
}

NcException::NcException(int errorCode, const char* complaint,const char* fileName,int lineNumber)
  : what_msg(NULL)
  , ec(errorCode)
{
  try{
    std::ostringstream oss;
    oss << lineNumber;
    what_msg = new std::string(complaint?complaint:"");
    what_msg->append("\nfile: ");
    what_msg->append(fileName);
    what_msg->append("  line:");
    what_msg->append(oss.str());
  }catch(...){
    what_msg = NULL;
  }
}

NcException::NcException(const NcException& e) throw()
	: what_msg(NULL)
  , ec(e.ec)
{
	try{
		what_msg = new std::string(*(e.what_msg));
	}catch(...){
		what_msg = NULL;
	}
}

NcException& NcException::operator=(const NcException& e) throw(){
	if (this != &e){
    ec = e.ec;
		delete what_msg;
		try{
			what_msg = new std::string(*(e.what_msg));
		}catch(...){
			what_msg = NULL;
		}
	}
	return *this;
}

NcException::~NcException()throw() {
	delete what_msg;
}


const char* NcException::what() const throw()
{
  return what_msg==NULL ? "" : what_msg->c_str();
}

int NcException::errorCode() const throw() {
  return ec;
}
