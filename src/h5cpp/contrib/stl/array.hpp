#pragma once

#include <h5cpp/datatype/type_trait.hpp>
#include <h5cpp/dataspace/type_trait.hpp>
#include <h5cpp/dataspace/simple.hpp>
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

template<typename T, size_t N>
class TypeTrait<std::array<T, N>> {
 public:
  using DataspaceType = Simple;

  static DataspaceType create(const std::array<T, N> &) {
    return Simple(hdf5::Dimensions{N}, hdf5::Dimensions{N});
  }

  const static DataspaceType & get(const std::array<T, N> &, DataspacePool &) {
    const static DataspaceType & cref_ = Simple(hdf5::Dimensions{N}, hdf5::Dimensions{N});
    return cref_;
  }

  static void *ptr(std::array<T, N> &value) {
    return reinterpret_cast<void *>(value.data());
  }

  static const void *cptr(const std::array<T, N> &value) {
    return reinterpret_cast<const void *>(value.data());
  }
};

} // end of namespace dataspace
} // end of namespace hdf5
