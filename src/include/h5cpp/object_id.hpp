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

extern "C" {
#include <hdf5.h>
}

#include <string>
#include <sstream>
#include <boost/filesystem.hpp>
#include "windows.hpp"

namespace hdf5
{

class DLL_EXPORT ObjectId
{
  public:
    ObjectId();
    ObjectId(hid_t object);

    bool operator== (const ObjectId& other) const;
    bool operator!= (const ObjectId& other) const;
    bool operator< (const ObjectId& other) const;

    DLL_EXPORT friend std::ostream & operator<<(std::ostream &os, const ObjectId& p);

    unsigned long file_number() const;
    haddr_t       object_address() const;

    boost::filesystem::path   file_name() const;

  private:
    unsigned long file_num_ {0};
    haddr_t       obj_addr_ {0};
    boost::filesystem::path   file_name_;

    static std::string get_file_name(hid_t object);
};


}
