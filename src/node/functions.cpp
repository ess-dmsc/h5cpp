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
  //what if rel_path is actually absolute?
  if (base.links.exists(static_cast<std::string>(rel_path)))
  {
    std::stringstream ss;
    ss << "node::copy failed. "
       << base.link() << " / " << rel_path << " already exists!";
    throw std::runtime_error(ss.str());
  }

  if (0 > H5Ocopy(static_cast<hid_t>(source.link().parent()), //parent
                  source.link().path().back().c_str(),        //object name
                  static_cast<hid_t>(base),                   //destination parent
                  static_cast<std::string>(rel_path).c_str(), //destination name
                  0, 0))
  {
    std::stringstream ss;
    ss << "node::copy failed. Could not copy "
       << source.link() << " to "
       << base.link() << " / " << rel_path;
    throw std::runtime_error(ss.str());
  }
}

void copy(const Node &source, const Group& destination)
{
  //what if rel_path is actually absolute?
  auto name = source.link().path().back(); //this feels awkward
  if (destination.links.exists(name))
  {
    std::stringstream ss;
    ss << "node::copy failed. "
       << destination.link() << " / " << name << " already exists!";
    throw std::runtime_error(ss.str());
  }

  if (0 > H5Ocopy(static_cast<hid_t>(source.link().parent()), //parent
                  name.c_str(),                               //object name
                  static_cast<hid_t>(destination),            //destination parent
                  name.c_str(),                               //...same name
                  0, 0))
  {
    std::stringstream ss;
    ss << "node::copy failed. Could not copy "
       << source.link() << " to "
       << destination.link() << " / " << name;
    throw std::runtime_error(ss.str());
  }
}

} // namespace node
} // namespace hdf5




