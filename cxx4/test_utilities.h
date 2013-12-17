#include <vector>
using namespace std;

template <class T> void initializeVector(std::vector<T>& dataVector) {
  for(size_t  i=0; i<dataVector.size(); i++) {
    dataVector[i] = static_cast<T>(i);
  }
}
