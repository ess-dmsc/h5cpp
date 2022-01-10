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

namespace dataspace {

template<typename T>
class TypeTrait<std::vector<T>> {
 public:
  using DataspaceType = Simple;

  static Simple create(const std::vector<T> &value) {
    return Simple(hdf5::Dimensions{value.size()}, hdf5::Dimensions{value.size()});
  }

  static const Dataspace & get(const std::vector<T> & value, DataspacePool & pool) {
    return pool.getSimple(value.size());
  }

  static void *ptr(std::vector<T> &data) {
    return reinterpret_cast<void *>(data.data());
  }

  static const void *cptr(const std::vector<T> &data) {
    return reinterpret_cast<const void *>(data.data());
  }
};

} // end of namespace dataspace
} // end of namespace hdf5
