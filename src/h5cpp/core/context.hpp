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
#pragma once

#include <h5cpp/core/object_id.hpp>
#include <map>
#include <mutex>

namespace hdf5
{

class Context
{
  public:
    void open(const hid_t&);
    bool is_open(const hid_t&) const;
    void close(const hid_t&);

  private:
    mutable std::mutex mutex_;
    std::map<id, hid_t> objects_;

    void close(const id&);

    //singleton assurance
  public:
    static Context& singleton()
    {
      static Context singleton_instance;
      return singleton_instance;
    }

    Context(Context const&)         = delete;
    void operator=(Context const&)  = delete;

  private:
    Context() {}
    ~Context();
};


}
