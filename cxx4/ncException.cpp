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


// Thrown if the specified netCDF ID does not refer to an open netCDF dataset. 
NcBadId::NcBadId(const char* complaint,const char* file,int line) :
  NcException(NC_EBADID,complaint,file,line) { }


// Thrown if too many netcdf files are open.
NcNFile::NcNFile(const char* complaint,const char* file,int line) :
  NcException(NC_ENFILE,complaint,file,line) { }

// Thrown if, having set NC_NOCLOBBER, the specified dataset already exists. 
NcExist::NcExist(const char* complaint,const char* file,int line) :
  NcException(NC_EEXIST,complaint,file,line) { }

// Thrown if not a netCDF id.
NcInvalidArg::NcInvalidArg(const char* complaint,const char* file,int line) :
  NcException(NC_EINVAL,complaint,file,line) { }

// Thrown if invalid argument.
NcInvalidWrite::NcInvalidWrite(const char* complaint,const char* file,int line) :
  NcException(NC_EPERM,complaint,file,line) { }

// Thrown if operation not allowed in data mode.
NcNotInDefineMode::NcNotInDefineMode(const char* complaint,const char* file,int line) :
  NcException(NC_ENOTINDEFINE,complaint,file,line) { }

// Thrown if operation not allowed in defined mode.
NcInDefineMode::NcInDefineMode(const char* complaint,const char* file,int line) :
  NcException(NC_EINDEFINE,complaint,file,line) { }

// Index exceeds dimension bound
NcInvalidCoords::NcInvalidCoords(const char* complaint,const char* file,int line) :
  NcException(NC_EINVALCOORDS,complaint,file,line) { }

// Thrown if NC_MAX_DIMS is exceeded.
NcMaxDims::NcMaxDims(const char* complaint,const char* file,int line) :
  NcException(NC_EMAXDIMS,complaint,file,line) { }

// Thrown if string match to name is in use.
NcNameInUse::NcNameInUse(const char* complaint,const char* file,int line) :
  NcException(NC_ENAMEINUSE,complaint,file,line) { }

// Thrown if attribute is not found.
NcNotAtt::NcNotAtt(const char* complaint,const char* file,int line) :
  NcException(NC_ENOTATT,complaint,file,line) { }

// Thrown if Nc_MAX_ATTRS is exceeded.
NcMaxAtts::NcMaxAtts(const char* complaint,const char* file,int line) :
  NcException(NC_EMAXATTS,complaint,file,line) { }

// Thrown if not a valid netCDF data type.
NcBadType::NcBadType(const char* complaint,const char* file,int line) :
  NcException(NC_EBADTYPE,complaint,file,line) { }

// Thrown if an invalid dimension id or name.
NcBadDim::NcBadDim(const char* complaint,const char* file,int line) :
  NcException(NC_EBADDIM,complaint,file,line) { }

// Thrown if Nc_UNLIMITED is in the wrong index.
NcUnlimPos::NcUnlimPos(const char* complaint,const char* file,int line) :
  NcException(NC_EUNLIMPOS,complaint,file,line) { }

// Thrown if NC_MAX_VARS is exceeded.
NcMaxVars::NcMaxVars(const char* complaint,const char* file,int line) :
  NcException(NC_EMAXVARS,complaint,file,line) { }

// Thrown if variable is not found.
NcNotVar::NcNotVar(const char* complaint,const char* file,int line) :
  NcException(NC_ENOTVAR,complaint,file,line) { }

// Thrown if the action is prohibited on the NC_GLOBAL varid.
NcGlobal::NcGlobal(const char* complaint,const char* file,int line) :
  NcException(NC_EGLOBAL,complaint,file,line) { }

// Thrown if not a netCDF file.
NcNotNCF::NcNotNCF(const char* complaint,const char* file,int line) :
  NcException(NC_ENOTNC,complaint,file,line) { }

// Thrown if in FORTRAN, string is too short.
NcSts::NcSts(const char* complaint,const char* file,int line) :
  NcException(NC_ESTS,complaint,file,line) { }

// Thrown if NC_MAX_NAME is exceeded.
NcMaxName::NcMaxName(const char* complaint,const char* file,int line) :
  NcException(NC_EMAXNAME,complaint,file,line) { }

// Thrown if NC_UNLIMITED size is already in use.
NcUnlimit::NcUnlimit(const char* complaint,const char* file,int line) :
  NcException(NC_EUNLIMIT,complaint,file,line) { }

// Thrown if nc_rec op when there are no record vars.
NcNoRecVars::NcNoRecVars(const char* complaint,const char* file,int line) :
  NcException(NC_ENORECVARS,complaint,file,line) { }

// Thrown if attempt to convert between text and numbers.
NcChar::NcChar(const char* complaint,const char* file,int line) :
  NcException(NC_ECHAR,complaint,file,line) { }

// Thrown if edge+start exceeds dimension bound.
NcEdge::NcEdge(const char* complaint,const char* file,int line) :
  NcException(NC_EEDGE,complaint,file,line) { }

// Thrown if illegal stride.
NcStride::NcStride(const char* complaint,const char* file,int line) :
  NcException(NC_ESTRIDE,complaint,file,line) { }

// Thrown if attribute or variable name contains illegal characters.
NcBadName::NcBadName(const char* complaint,const char* file,int line) :
  NcException(NC_EBADNAME,complaint,file,line) { }

// Thrown if math result not representable.
NcRange::NcRange(const char* complaint,const char* file,int line) :
  NcException(NC_ERANGE,complaint,file,line) { }

// Thrown if memory allocation (malloc) failure.
NcNoMem::NcNoMem(const char* complaint,const char* file,int line) :
  NcException(NC_ENOMEM,complaint,file,line) { }

// Thrown if one or more variable sizes violate format constraints
NcVarSize::NcVarSize(const char* complaint,const char* file,int line) :
  NcException(NC_EVARSIZE,complaint,file,line) { }

// Thrown if invalid dimension size.
NcDimSize::NcDimSize(const char* complaint,const char* file,int line) :
  NcException(NC_EDIMSIZE,complaint,file,line) { }

// Thrown if file likely truncated or possibly corrupted.
NcTrunc::NcTrunc(const char* complaint,const char* file,int line) :
  NcException(NC_ETRUNC,complaint,file,line) { }

// Thrown if an error was reported by the HDF5 layer.
NcHdfErr::NcHdfErr(const char* complaint,const char* file,int line) :
  NcException(NC_EHDFERR,complaint,file,line) { }

// Thrown if cannot read.
NcCantRead::NcCantRead(const char* complaint,const char* file,int line) :
  NcException(NC_ECANTREAD,complaint,file,line) { }

// Thrown if cannot write.
NcCantWrite::NcCantWrite(const char* complaint,const char* file,int line) :
  NcException(NC_ECANTWRITE,complaint,file,line) { }

// Thrown if cannot create.
NcCantCreate::NcCantCreate(const char* complaint,const char* file,int line) :
  NcException(NC_ECANTCREATE,complaint,file,line) { }

// Thrown if file meta.
NcFileMeta::NcFileMeta(const char* complaint,const char* file,int line) :
  NcException(NC_EFILEMETA,complaint,file,line) { }

// Thrown if dim meta.
NcDimMeta::NcDimMeta(const char* complaint,const char* file,int line) :
  NcException(NC_EDIMMETA,complaint,file,line) { }

// Thrown if attribute meta.
NcAttMeta::NcAttMeta(const char* complaint,const char* file,int line) :
  NcException(NC_EATTMETA,complaint,file,line) { }

// Thrown if variable meta.
NcVarMeta::NcVarMeta(const char* complaint,const char* file,int line) :
  NcException(NC_EVARMETA,complaint,file,line) { }

// Thrown if no compound.
NcNoCompound::NcNoCompound(const char* complaint,const char* file,int line) :
  NcException(NC_ENOCOMPOUND,complaint,file,line) { }

// Thrown if attribute exists.
NcAttExists::NcAttExists(const char* complaint,const char* file,int line) :
  NcException(NC_EATTEXISTS,complaint,file,line) { }

// Thrown if attempting netcdf-4 operation on netcdf-3 file.
NcNotNc4::NcNotNc4(const char* complaint,const char* file,int line) :
  NcException(NC_ENOTNC4,complaint,file,line) { }

// Thrown if attempting netcdf-4 operation on strict nc3 netcdf-4 file.
NcStrictNc3::NcStrictNc3(const char* complaint,const char* file,int line) :
  NcException(NC_ESTRICTNC3,complaint,file,line) { }

// Thrown if bad group id.
NcBadGroupId::NcBadGroupId(const char* complaint,const char* file,int line) :
  NcException(NC_EBADGRPID,complaint,file,line) { }

// Thrown if bad type id.
NcBadTypeId::NcBadTypeId(const char* complaint,const char* file,int line) :
  NcException(NC_EBADTYPID,complaint,file,line) { }

// Thrown if bad field id.
NcBadFieldId::NcBadFieldId(const char* complaint,const char* file,int line) :
  NcException(NC_EBADFIELD,complaint,file,line) { }

// Thrown if cannot find the field id.
NcUnknownName::NcUnknownName(const char* complaint,const char* file,int line) :
  NcException(complaint,file,line) { }

// Thrown if cannot find the field id.
NcEnoGrp::NcEnoGrp(const char* complaint,const char* file,int line) :
  NcException(NC_ENOGRP,complaint,file,line) { }

// Thrown if cannot find the field id.
NcNullGrp::NcNullGrp(const char* complaint,const char* file,int line) :
  NcException(complaint,file,line) { }

// Thrown if cannot find the field id.
NcNullDim::NcNullDim(const char* complaint,const char* file,int line) :
  NcException(complaint,file,line) { }

// Thrown if cannot find the field id.
NcNullType::NcNullType(const char* complaint,const char* file,int line) :
  NcException(complaint,file,line) { }

// Thrown if an operation to set the deflation, chunking, endianness, fill, compression, or checksum of a NcVar object is issued after a call to NcVar::getVar or NcVar::putVar.
NcElateDef::NcElateDef(const char* complaint,const char* file,int line) :
  NcException(NC_ELATEDEF,complaint,file,line) { }

