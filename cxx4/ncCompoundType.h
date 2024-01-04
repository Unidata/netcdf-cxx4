#include <string>
#include <vector>
#include "ncType.h"
#include "netcdf.h"

#ifndef NcCompoundTypeClass
#define NcCompoundTypeClass


namespace netCDF
{
  class NcGroup;  // forward declaration.

  /*! 
    Class represents a netCDF compound type
  */
  class NcCompoundType : public NcType
  {
  public:
    using NcType::NcType;

    /*! 
      Constructor.
      Constructs from the base type NcType object. Will throw an exception if the NcType is not the base of a Compound type.
      \param ncType     A Nctype object.
    */
    NcCompoundType(const NcType& ncType);

    /*! 
      Assignment operator.
      This assigns from the base type NcType object. Will throw an exception if the NcType is not the base of a Compound type.
    */
    NcCompoundType& operator=(const NcType& rhs);
      
    /*! equivalence operator */
    bool operator==(const NcCompoundType & rhs);

    /*!  
      Adds a named field.
      \param memName       Name of new field.
      \param newMemberType The type of the new member.
      \param offset        Offset of this member in bytes, obtained by a call to offsetof. For example 
the offset of a member "mem4" in structure struct1 is: offsetof(struct1,mem4).
    */
    void addMember(const std::string& memName, const NcType& newMemberType,size_t offset);

    /*!  
      Adds a named array field.
      \param memName       Name of new field.
      \param newMemberType The type of the new member.
      \param offset        Offset of this member in bytes, obtained by a call to offsetof. For example 
                           the offset of a member "mem4" in structure struct1 is: offsetof(struct1,mem4).
      \param shape         The shape of the array field.
    */
    void addMember(const std::string& memName, const NcType& newMemberType, size_t offset, const std::vector<int>& shape);


    /*! Returns number of members in this NcCompoundType object. */
    size_t  getMemberCount() const;
      
    /*! Returns a NcType object for a single member. */
    NcType getMember(int memberIndex) const;

    /*! Returns name of member field. */
    std::string getMemberName(int memberIndex) const;

    /*! Returns index of named member field. */
    int getMemberIndex(const std::string& memberName) const;

    /*! Returns the offset of the member with given index. */
    size_t getMemberOffset(const int index) const;

    /*! 
      Returns the number of dimensions of a member with the given index. 
      \param Index of member (numbering starts at zero).
      \return The number of dimensions of the field. Non-array fields have 0 dimensions.
    */
    int getMemberDimCount(int memberIndex) const;
      
      
    /*! 
      Returns the shape of a given member. 
      \param Index of member (numbering starts at zero).
      \return The size of the dimensions of the field. Non-array fields have 0 dimensions.
    */
    std::vector<int> getMemberShape(int memberIndex) const;
      
      
  private:
      
    int myOffset;
      
  };
  
}


#endif
