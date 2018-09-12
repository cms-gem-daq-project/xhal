#include <string>
#include <vector>
#include <map>

typedef std::vector<uint32_t> PyListUint32;

//this is a typedef for std::map<T, uint32_t>
template <class T>
using PyDictUint32 = std::map<T,uint32_t>; //Now PyDictUint32 is a typedef for std::map<T, uint32_t>

//this is a typedef for std::map<T, PyListUint32>
template <class T>
using PyDictVecUint32 = std::map<T, PyListUint32>;

//this is a typedef for std::map<T, M>
template <class T, class M>
using NestedPyDict = std::map<T,M>;
