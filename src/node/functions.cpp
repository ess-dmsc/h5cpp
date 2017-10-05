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
// Author: Martin Shetty <martin.shetty@esss.se>
// Created on: Sep 9, 2017
//
#include <sstream>
#include <h5cpp/node/functions.hpp>

namespace hdf5 {
namespace node {

void copy(const Node &source, const Group& base, const Path &rel_path)
{
//  if (base.nodes.exists(static_cast<std::string>(rel_path)))
//  {
//    //todo: Make more informative
//    throw std::runtime_error("Node already exists!");
//  }

  H5Ocopy(static_cast<hid_t>(source.link().parent()), //parent
          source.link().path().back().c_str(),        //object name
          static_cast<hid_t>(base),                   //destination parent
          static_cast<std::string>(rel_path).c_str(), //destination name
          0, 0);
}

void copy(const Node &source, const Group& destination)
{
  auto name = source.link().path().back();
//  if (destination.nodes.exists(name))
//  {
//    //todo: Make more informative
//    throw std::runtime_error("Node already exists!");
//  }

  H5Ocopy(static_cast<hid_t>(source.link().parent()), //parent
          name.c_str(),                               //object name
          static_cast<hid_t>(destination),            //destination parent
          name.c_str(),                               //...same name
          0, 0);
}

} // namespace node


} // namespace hdf5




