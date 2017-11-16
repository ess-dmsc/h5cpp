//
// (c) Copyright 2017 DESY,ESS
//
// This file is part of h5pp.
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
// Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
// Created on: Oct 23, 2017
//
#include <gtest/gtest.h>
#include <h5cpp/hdf5.hpp>
#include <algorithm>

template<typename T> struct Vector
{
  public:
    Vector(){}
    Vector(const std::initializer_list<T> &init_list):
      data_()
    {
      std::copy(init_list.begin(),init_list.end(),data_);
    }

    const T* begin() const
    {
      return data_;
    }

    const T* end() const
    {
      return &data_[3];
    }

  private:
    T data_[3];
};

template<typename T>
bool operator==(const Vector<T> &lhs,const Vector<T> &rhs)
{
  return std::equal(lhs.begin(),lhs.end(),rhs.begin());
}

namespace hdf5 {
namespace datatype {

template<typename T>
class TypeTrait<Vector<T>>
{
  public:
    using TypeClass = Array;

    static TypeClass create()
    {
      auto base_type = TypeTrait<T>::create();
      return Array(base_type,{3});
    }

    static TypeClass create(const Vector<T> &)
    {
      return create();
    }
};

}
}

using namespace hdf5;

TEST(DatasetArrayIO,read_write_vector)
{
  using ElementType = Vector<int>;
  file::File f;
  EXPECT_NO_THROW(f = file::create("read_write_vector.h5",file::AccessFlags::TRUNCATE));
  node::Group root_group = f.root();

  datatype::Array type;
  dataspace::Simple space;

  EXPECT_NO_THROW(type = datatype::create<ElementType>());
  EXPECT_NO_THROW(space = dataspace::Simple({2}));

  node::Dataset dset(root_group,Path("data"),type,space);


  std::vector<ElementType> write_data{{1,2,3},{4,5,6}};
  std::vector<ElementType> read_data(2);
  EXPECT_NE(write_data,read_data);
  EXPECT_NO_THROW(dset.write(write_data));
  EXPECT_NO_THROW(dset.read(read_data));
  EXPECT_EQ(write_data,read_data);


}
