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
// Created on: Jan 10, 2021
//
#pragma once
#pragma once
#include <h5cpp/hdf5.hpp>
#include <examples/hklpoint.hpp>

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
    const static TypeClass & get(const HKLPoint & = HKLPoint())
    {
      const static TypeClass & cref_ = create();
      return cref_;
    }
};

}
}


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
    const static TypeClass & get(const HKLPointList & = HKLPointList())
    {
      const static TypeClass & cref_ = VLengthArray::create(TypeTrait<HKLPoint>::create());
      return cref_;
    }
};

}
}

namespace hdf5 {

template<>
struct VarLengthBufferTrait<HKLPoints>
{
    static void to_buffer(const HKLPoints &points, VarLengthDataBuffer &buffer)
    {
      std::transform(points.begin(),points.end(),std::back_inserter(buffer),
                     [](const HKLPointList &list)
                     { return hvl_t{list.size(),
                                    const_cast<void *>(static_cast<const void *>(list.data()))}; });
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
