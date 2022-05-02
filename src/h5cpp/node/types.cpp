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


std::ostream &operator<<(std::ostream &stream,const NodeType &type)
{
  switch(type)
  {
    case NodeType::Unknown: return stream<<"UNKNOWN";
    case NodeType::Group: return stream<<"GROUP";
    case NodeType::Dataset: return stream<<"DATASET";
    case NodeType::Datatype: return stream<<"DATATYPE";
  }
  return stream;
}

std::ostream &operator<<(std::ostream &stream,const LinkType &type)
{
  switch(type)
  {
    case LinkType::Error: return stream<<"ERROR";
    case LinkType::External: return stream<<"EXTERNAL";
    case LinkType::Hard: return stream<<"HARD";
    case LinkType::Soft: return stream<<"SOFT";
  }
  return stream;
}

} // namespace node
} // namespace hdf5


