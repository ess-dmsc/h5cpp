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

struct Flip {
 public:
  Flip() {
    data_[0] = 0;
  }
  Flip(std::int32_t a) {
    data_[0] = a;
  }

  const std::int32_t* begin() const { return data_; }

  const std::int32_t* end() const { return &data_[1]; }

  bool positive() const{
    return data_[0] > 0;
  }

 private:
  std::int32_t data_[1];
};

bool operator==(const Flip& lhs, const Flip& rhs) {
  return std::equal(lhs.begin(), lhs.end(), rhs.begin());
}

bool operator!=(const Flip& lhs, const Flip& rhs) {
  return !(lhs == rhs);
}

namespace hdf5 {
namespace datatype {

template<>
class TypeTrait<Flip> {
 public:
  using TypeClass = datatype::Datatype;
  using Type = Flip;

  static TypeClass create(const Type & v= Type()) {
    if(v.positive())
      return hdf5::datatype::create<std::uint32_t>();
    else
      return hdf5::datatype::create<std::int32_t>();
  }
  const static TypeClass & get(const Type & = Type()) {
    const static TypeClass & cref_ = datatype::Datatype();
    return cref_;
  }
};

}  // namespace datatype
}  // namespace hdf5

using namespace hdf5;

SCENARIO("writing a vector with an dynamic element type") {
  using ElementType = Flip;
  using Elements = std::vector<ElementType>;
  auto f =
      file::create("dataset_dynamic_type_io.h5", file::AccessFlags::Truncate);
  auto type = datatype::create<ElementType>();
  auto mtype = datatype::create(Flip(-1));
  auto space = dataspace::Simple({2});

  GIVEN("a dataset of the appropriate datatype") {
    node::Dataset dset(f.root(), Path("data"), type, space);
    AND_GIVEN("a vector of data") {
      Elements write{1, 2};
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

  GIVEN("a dataset of the appropriate datatype with negative values") {
    node::Dataset mdset(f.root(), Path("mdata"), mtype, space);
    AND_GIVEN("a vector of data") {
      Elements mwrite{-2, -3};
      THEN("we can write this data to the dataset") {
        mdset.write(mwrite);
        AND_THEN("we can read it back") {
          Elements mread(2);
          mdset.read(mread);
          REQUIRE_THAT(mread, Catch::Matchers::Equals(mwrite));
        }
      }
    }
  }
}
