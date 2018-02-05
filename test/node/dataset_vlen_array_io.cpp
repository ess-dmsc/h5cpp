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

class HKLPoint
{
  public:
    HKLPoint();
    HKLPoint(int h,int k,int l);
    HKLPoint(const std::initializer_list<int> &init_list);

    int h() const noexcept;
    int k() const noexcept;
    int l() const noexcept;
  private:
    int h_;
    int k_;
    int l_;
};

HKLPoint::HKLPoint():
    h_(0),
    k_(0),
    l_(0)
{}

HKLPoint::HKLPoint(int h,int k,int l):
    h_(h),
    k_(k),
    l_(l)
{}

HKLPoint::HKLPoint(const std::initializer_list<int> &init_list):
    h_(0),
    k_(0),
    l_(0)
{
  auto iter = init_list.begin();
  h_ = *iter++;
  k_ = *iter++;
  l_ = *iter;
}

int HKLPoint::h() const noexcept
{
  return h_;
}

int HKLPoint::k() const noexcept
{
  return k_;
}

int HKLPoint::l() const noexcept
{
  return l_;
}

bool operator==(const HKLPoint &lhs,const HKLPoint &rhs)
{
  if((lhs.h()==rhs.h())&&(lhs.k()==rhs.k())&&(lhs.l()==rhs.l()))
    return true;
  else
    return false;
}

namespace hdf5 {
namespace datatype {

template<>
class TypeTrait<HKLPoint>
{
  public:
    using TypeClass = Compound;

    static TypeClass create(const HKLPoint & = HKLPoint())
    {
      auto type = Compound::create(sizeof(HKLPoint));
      auto base_type = TypeTrait<int>::create();
      type.insert("h",0,base_type);
      type.insert("k",sizeof(int),base_type);
      type.insert("l",sizeof(int)*2,base_type);
      return type;
    }
};

}
}


class HKLPointList : public std::vector<HKLPoint>
{
  public:
    using std::vector<HKLPoint>::vector;
};

namespace hdf5{
namespace datatype{

template<>
class TypeTrait<HKLPointList>
{
  public:
    using TypeClass = VLengthArray;

    static TypeClass create(const HKLPointList & = HKLPointList())
    {
      return VLengthArray::create(TypeTrait<HKLPoint>::create());
    }
};

}
}

using namespace hdf5;

using HKLPoints = std::vector<HKLPointList>;


namespace hdf5 {

template<>
struct VarLengthBufferTrait<HKLPoints>
{
    static void to_buffer(const HKLPoints &points, VarLengthDataBuffer &buffer)
    {
      std::transform(points.begin(),points.end(),std::back_inserter(buffer),
                     [](const HKLPointList &list)
                     { return hvl_t{list.size(),(void*)list.data()}; });
    }

    static void from_buffer(const VarLengthDataBuffer &buffer,HKLPoints &points)
    {
      std::transform(buffer.begin(),buffer.end(),points.begin(),
      [](const hvl_t &value)
      {
        HKLPointList list;
        HKLPoint *start =  reinterpret_cast<HKLPoint*>(value.p);
        HKLPoint *end   = start+value.len;
        std::copy(start,end,std::back_inserter(list));
        return list;
      }
      );
    }
};

}

TEST(DatasetVLenghtArrayIO,read_write_hkl_list)
{
  std::vector<HKLPointList> write_points{
    {{1,2,3},{3,4,5},{6,7,8}},
    {{4,5,6}}
  };
  std::vector<HKLPointList> read_points(2);

  file::File f = file::create("read_write_hkl_list.h5",file::AccessFlags::TRUNCATE);
  node::Group root_group = f.root();

  node::Dataset dset(root_group,Path("data"),datatype::create<HKLPointList>(),
                                             dataspace::Simple({2}));

  dset.write(write_points);
  dset.read(read_points);
  EXPECT_EQ(write_points[0].size(),read_points[0].size());
  EXPECT_EQ(write_points[1].size(),read_points[1].size());

  //check content
  HKLPointList ref1{{1,2,3},{3,4,5},{6,7,8}};
  HKLPointList ref2{{4,5,6}};
  EXPECT_EQ(ref1,read_points[0]);
  EXPECT_EQ(ref2,read_points[1]);

}



