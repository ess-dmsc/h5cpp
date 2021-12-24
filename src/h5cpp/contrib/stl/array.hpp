#pragma once

#include <h5cpp/datatype/type_trait.hpp>
#include <array>

namespace hdf5 { 
namespace datatype { 

template<typename T, size_t N>
class TypeTrait<std::array<T, N>> {
 public:
  using Type = std::array<T, N>;
  using TypeClass = typename TypeTrait<T>::TypeClass;
  static TypeClass create(const Type & = Type()) {
    return TypeTrait<typename std::remove_const<T>::type>::create();
  }
  const static TypeClass & get(const Type & = Type()) {
    const static TypeClass & cref_ = TypeTrait<typename std::remove_const<T>::type>::create();
    return cref_;
  }
};
} // end of namespace datatype

namespace dataspace { 

} // end of namespace dataspace
} // end of namespace hdf5