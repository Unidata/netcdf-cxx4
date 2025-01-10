#include <string>
#include "netcdf.h"

#ifndef NcTypeClass
#define NcTypeClass


namespace netCDF
{

  class NcGroup; // forward declaration to avoid cyclic reference.

  /*! Base class inherited by NcOpaque, NcVlen, NcCompound and NcEnum classes. */
  class NcType
  {

  public:

    /*!
      List of netCDF types that can be represented.
      The enumeration list contains the complete set of netCDF variable types. In addition, the type NC_TYPE
      is included. This enables the user to instantiate a netCDF type object without explcitly needing to know
      it precise type.
    */
    enum ncType
    {
      nc_BYTE     = NC_BYTE, 	//!< signed 1 byte integer
      nc_CHAR     = NC_CHAR,	//!< ISO/ASCII character
      nc_SHORT    = NC_SHORT, 	//!< signed 2 byte integer
      nc_INT      = NC_INT,	//!< signed 4 byte integer
      nc_FLOAT    = NC_FLOAT, 	//!< single precision floating point number
      nc_DOUBLE   = NC_DOUBLE, 	//!< double precision floating point number
      nc_UBYTE    = NC_UBYTE,	//!< unsigned 1 byte int
      nc_USHORT   = NC_USHORT,	//!< unsigned 2-byte int
      nc_UINT     = NC_UINT,	//!< unsigned 4-byte int
      nc_INT64    = NC_INT64,	//!< signed 8-byte int
      nc_UINT64   = NC_UINT64,	//!< unsigned 8-byte int
      nc_STRING   = NC_STRING, 	//!< string
      nc_VLEN     = NC_VLEN,   	//!< "NcVlen type"
      nc_OPAQUE   = NC_OPAQUE, 	//!< "NcOpaque type"
      nc_ENUM     = NC_ENUM, 	//!< "NcEnum type"
      nc_COMPOUND = NC_COMPOUND //!< "NcCompound type"
    };

    /*! Constructor generates a \ref isNull "null object". */
    NcType() = default;
    NcType(const NcType& rhs) = default;
    NcType(NcType&& rhs) = default;
    NcType& operator=(const NcType& rhs) = default;
    NcType& operator=(NcType&& rhs) = default;

    virtual ~NcType() = default;

    /*!
      Constructor for a non-global type.
      This object describes the "essential" information for all netCDF types required by NcVar, NcAtt objects.
      New netCDF types can be added using the appropriate "add" method in the NcGroup object.
      \param grp    Parent NcGroup object.
      \param name   Name of this type.
    */
    NcType(const netCDF::NcGroup& grp, const std::string& name);


    /*!
      Constructor for a non-global type.
      This object describes the "essential" information for all netCDF types required by NcVar, NcAtt objects.
      New netCDF types can be added using the appropriate "add" method in the NcGroup object.
      \param grp    Parent NcGroup object.
      \param id     type id
    */
    NcType(const netCDF::NcGroup& grp, nc_type id);

    /*!
      Constructor for a global type
      This object describes the "essential" information for a netCDF global type.
      \param id     type id
    */
    NcType(nc_type id) : nullObject(false), myId(id), groupId(0) {}

    /*! equivalence operator */
    bool operator==(const NcType&) const;

    /*!  != operator */
    bool operator!=(const NcType &) const;

    // accessors to private data.
    /*! The netCDF Id of this type. */
    nc_type getId() const {return myId;}

    /*! Gets parent group. For an atomic type, returns a Null object.*/
    netCDF::NcGroup getParentGroup() const;

    /*!
      The name of this type. For atomic types, the CDL type names are returned. These are as follows:
        - NcByte   String returned is "byte".
        - NcUbyte  String returned is "ubyte".
        - NcChar   String returned is "char".
        - NcShort  String returned is "short".
        - NcUshort String returned is "ushort".
        - NcInt    String returned is "int".
        - NcUint   String returned is "uint".
        - NcInt64  String returned is "int64".
        - NcUint64 String returned is "uint64".
        - NcFloat  String returned is "float".
        - NcDouble String returned is "double".
        - NcString String returned is "string".
     */
    std::string getName() const;

    /*!
      The size in bytes.
      This function will work on any type, including atomic and any user defined type, whether
      compound, opaque, enumeration, or variable length array.

     */
    size_t getSize() const;

    /*!
      The type class returned as enumeration type.
      Valid for all types, whether atomic or user-defined. User-defined types are returned as one of the following
      enumeration types: nc_VLEN, nc_OPAQUE, nc_ENUM, or nc_COMPOUND.
     */
    ncType getTypeClass() const;

    /*!
      Return a string containing the name of the enumerated type.  (ie one of the following strings:
      "nc_BYTE", "nc_CHAR", "nc_SHORT", "nc_INT", "nc_FLOAT", "nc_DOUBLE", "nc_UBYTE", "nc_USHORT",
      "nc_UINT", "nc_INT64", "nc_UINT64", "nc_STRING", "nc_VLEN", "nc_OPAQUE", "nc_ENUM", "nc_COMPOUND"
     */
    std::string getTypeClassName() const;

    /*! Returns true if this object is null (i.e. it has no contents); otherwise returns false. */
    bool isNull() const  {return nullObject;}

    /*! comparator operator  */
    friend bool operator<(const NcType& lhs,const NcType& rhs);

    /*! comparator operator  */
    friend bool operator>(const NcType& lhs,const NcType& rhs);

  protected:
    bool nullObject{true};

    /*! the type Id */
    nc_type myId{-1};

    /*! the group Id */
    int groupId{-1};
  };

  /// Intermediate base class for atomic types
  class NcAtomicType : public NcType {
  public:
    using NcType::NcType;

    bool operator==(const NcAtomicType& rhs) {
      return myId == rhs.myId;
    }
  };

  /// netCDF atomic byte type
  class NcByte : public NcAtomicType {
  public:
    NcByte() : NcAtomicType(NC_BYTE) {}
  };

  extern const NcByte ncByte;

  /// netCDF atomic unsigned byte type
  class NcUbyte : public NcAtomicType {
  public:
    NcUbyte() : NcAtomicType(NC_UBYTE) {}
  };

  extern const NcUbyte ncUbyte;

  /// netCDF atomic char type
  class NcChar : public NcAtomicType {
  public:
    NcChar() : NcAtomicType(NC_CHAR) {}
  };

  extern const NcChar ncChar;

  /// netCDF atomic short type
  class NcShort : public NcAtomicType {
  public:
    NcShort() : NcAtomicType(NC_SHORT) {}
  };

  extern const NcShort ncShort;

  /// netCDF atomic unsigned short type
  class NcUshort : public NcAtomicType {
  public:
    NcUshort() : NcAtomicType(NC_USHORT) {}
  };

  extern const NcUshort ncUshort;

  /// netCDF atomic int type
  class NcInt : public NcAtomicType {
  public:
    NcInt() : NcAtomicType(NC_INT) {}
  };

  extern const NcInt ncInt;

  /// netCDF atomic unsigned int type
  class NcUint : public NcAtomicType {
  public:
    NcUint() : NcAtomicType(NC_UINT) {}
  };

  extern const NcUint ncUint;

  /// netCDF atomic 64-bit int type
  class NcInt64 : public NcAtomicType {
  public:
    NcInt64() : NcAtomicType(NC_INT64) {}
  };

  extern const NcInt64 ncInt64;

  /// netCDF atomic unsigned 64-bit int type
  class NcUint64 : public NcAtomicType {
  public:
    NcUint64() : NcAtomicType(NC_UINT64) {}
  };

  extern const NcUint64 ncUint64;

  /// netCDF atomic float type
  class NcFloat : public NcAtomicType {
  public:
    NcFloat() : NcAtomicType(NC_FLOAT) {}
  };

  extern const NcFloat ncFloat;

  /// netCDF atomic double type
  class NcDouble : public NcAtomicType {
  public:
    NcDouble() : NcAtomicType(NC_DOUBLE) {}
  };

  extern const NcDouble ncDouble;

  /// netCDF atomic string type
  class NcString : public NcAtomicType {
  public:
    NcString() : NcAtomicType(NC_STRING) {}
  };

  extern const NcString ncString;
}
#endif
