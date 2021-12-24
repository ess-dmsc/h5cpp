#pragma once

#include <vector>
#include <h5cpp/datatype/type_trait.hpp>

namespace hdf5 { 
namespace datatype { 

template<typename T>
class TypeTrait<std::vector<T>> {
 public:
  using Type = std::vector<T>;
  using TypeClass = typename TypeTrait<T>::TypeClass;
  static TypeClass create(const Type & = Type()) {
    return TypeTrait<typename std::remove_const<T>::type>::create();
  }
  const static TypeClass & get(const Type & = Type()) {
    const static TypeClass & cref_ = create();
    return cref_;
  }
};

} // end of namespace datatype
} // end of namespace hdf5