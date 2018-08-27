#include <string>
#include <vector>
#include <map>

typedef std::vector<uint32_t> PyListUint32;
template <class T>
using PyDictUint32 = std::map<T,uint32_t>; //Now PyDictUint32 is a typedef for std::map<T, uint32_t>
template <class T>
using PyDictVecUint32 = std::map<T, PyListUint32>; //now PyDictVecUint32 is a typedef for std::map<T, PyListUint32>
