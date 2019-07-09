// Check move constructors for NcGroup/NcFile work correctly

#include <netcdf>

int main() {
  using namespace netCDF;
  using namespace netCDF::exceptions;

  std::cout << "Testing move constructor for NcFile\n";

  try {
    NcFile first_file("testfile.nc", NcFile::replace);
    auto first_file_id = first_file.getId();

    NcFile second_file = std::move(first_file);

    if (second_file.isNull()) throw NcException("Error in move test", __FILE__, __LINE__);

    auto second_file_id = second_file.getId();

    if (second_file_id != first_file_id) throw NcException("Error in move test", __FILE__, __LINE__);
  } catch (NcException &e) {
    std::cout << e.what() << std::endl;
    return e.errorCode();
  }

  std::cout << "Testing move constructor for NcGroup\n";

  try {
    NcFile file("testfile.nc", NcFile::replace);
    NcGroup first_group(file.addGroup("first_group")); 

    auto first_group_id = first_group.getId();

    NcGroup second_group = std::move(first_group);

    if (second_group.isNull()) throw NcException("Error in move test", __FILE__, __LINE__);

    auto second_group_id = second_group.getId();

    if (second_group_id != first_group_id) throw NcException("Error in move test", __FILE__, __LINE__);
    if (second_group.getName(true) != first_group.getName(true)) throw NcException("Error in move test", __FILE__, __LINE__);
  } catch (NcException &e) {
    std::cout << e.what() << std::endl;
    return e.errorCode();
  }

}
