//
// (c) Copyright 2017 DESY,ESS
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
// Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
// Created on: Sep 10, 2017
//

#include <h5cpp/node/types.hpp>

namespace hdf5 {
namespace node {


std::ostream &operator<<(std::ostream &stream,const Type &type)
{
  switch(type)
  {
    case Type::UNKNOWN: return stream<<"UNKOWN";
    case Type::GROUP: return stream<<"GROUP";
    case Type::DATASET: return stream<<"DATASET";
    case Type::DATATYPE: return stream<<"DATATYPE";
    default:
      return stream;
  }
}

std::ostream &operator<<(std::ostream &stream,const IterationOrder &order)
{
  switch(order)
  {
    case IterationOrder::DECREASING: return stream<<"DECREASING";
    case IterationOrder::INCREASING: return stream<<"INCREASING";
    case IterationOrder::NATIVE: return stream<<"NATIVE";
    default:
      return stream;
  }

}

std::ostream &operator<<(std::ostream &stream,const IterationIndex &index)
{

}

} // namespace node
} // namespace hdf5


