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
//
#include "context.hpp"
#include <list>

namespace hdf5
{

void Context::open(const hid_t& hid)
{
  std::lock_guard<std::mutex> guard(mutex_);
  objects_[id(hid)] = hid;
}

bool Context::is_open(const hid_t& hid) const
{
  std::lock_guard<std::mutex> guard(mutex_);
  return objects_.count(id(hid));
}

void Context::close(const hid_t& hid)
{
  std::lock_guard<std::mutex> guard(mutex_);
  close(id(hid));
}

void Context::close(const id& i)
{
  //could do actual object destruction?

  objects_.erase(i);
}

Context::~Context()
{
  std::list<id> ids;
  for (auto o : objects_)
    ids.push_back(o.first);
  for (auto i : ids)
    close(i);
}


}
