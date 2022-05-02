//
// (c) Copyright 2017 DESY,ESS
//               2020 Eugen Wintersberger <eugen.wintersberger@gmail.com>
//
// This file is part of h5cpp.
//
// This library is free software; you can redistribute it and/or modify it
// under the terms of the GNU Lesser General Public License as published
// by the Free Software Foundation; either version 2.1 of the License, or
// (at your option) any later version.
//
// This library is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty ofMERCHANTABILITY
// or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
// License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this library; if not, write to the
// Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor
// Boston, MA  02110-1301 USA
// ===========================================================================
//
// Authors:
//         Eugen Wintersberger <eugen.wintersberger@gmail.com>
//         Jan Kotanski <jan.kotanski@desy.de>
// Created on: Oct 23, 2017
//
#include <algorithm>
#include <catch2/catch.hpp>
#include <h5cpp/hdf5.hpp>
#include <h5cpp/contrib/stl/vector.hpp>

template <typename T>
struct Vector {
 public:
  Vector() {}
  Vector(const std::initializer_list<T>& init_list) : data_() {
    std::copy(init_list.begin(), init_list.end(), data_);
  }

  const T* begin() const { return data_; }

  const T* end() const { return &data_[3]; }

 private:
  T data_[3];
};

template <typename T>
bool operator==(const Vector<T>& lhs, const Vector<T>& rhs) {
  return std::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template <typename T>
bool operator!=(const Vector<T>& lhs, const Vector<T>& rhs) {
  return !(lhs == rhs);
}
namespace hdf5 {
namespace datatype {

template <typename T>
class TypeTrait<Vector<T>> {
 public:
  using TypeClass = Array;

  static TypeClass create() {
    auto base_type = TypeTrait<T>::create();
    return Array::create(base_type, {3});
  }

  static TypeClass create(const Vector<T>&) { return create(); }
  const static TypeClass & get(const Vector<T>&)
  {
    const static TypeClass & cref_ = create();
    return cref_;
  }
  const static TypeClass & get()
  {
    const static TypeClass & cref_ = create();
    return cref_;
  }
};

}  // namespace datatype
}  // namespace hdf5

using namespace hdf5;

SCENARIO("writing a vector with an array element type") {
  using ElementType = Vector<int>;
  using Elements = std::vector<ElementType>;
  auto f =
      file::create("dataset_array_type_io.h5", file::AccessFlags::Truncate);
  auto type = datatype::create<ElementType>();
  auto space = dataspace::Simple({2});

  GIVEN("a dataset of the appropriate datatype") {
    node::Dataset dset(f.root(), Path("data"), type, space);
    AND_GIVEN("a vector of data") {
      Elements write{{1, 2, 3}, {4, 5, 6}};
      THEN("we can write this data to the dataset") {
        dset.write(write);
        AND_THEN("we can read it back") {
          Elements read(2);
          dset.read(read);
          REQUIRE_THAT(read, Catch::Matchers::Equals(write));
        }
      }
    }
  }
}
