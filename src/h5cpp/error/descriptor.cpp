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
// Created on: Oct 25, 2017
//

#include <h5cpp/error/descriptor.hpp>

extern "C"{
#include <cstring>
}

namespace hdf5 {
namespace error {

Descriptor::Descriptor(const H5E_error2_t& d)
    : line(d.line)
{
  func_name = std::string(d.func_name, strlen(d.func_name));
  file_name = std::string(d.file_name, strlen(d.file_name));
  desc = std::string(d.desc, strlen(d.desc));

  auto mesg1 = H5Eget_major(d.maj_num);
  major_txt = std::string(mesg1, strlen(mesg1));

  auto mesg2 = H5Eget_minor(d.min_num);
  minor_txt = std::string(mesg2, strlen(mesg2));
}

std::ostream &operator<<(std::ostream &stream, const Descriptor &desc)
{
  stream << desc.file_name << ":" << desc.line
         << " in function '" << desc.func_name << "': "
         << desc.desc
         << " (maj=" << desc.major_txt
         << ", min=" << desc.minor_txt
         << ")";
  return stream;
}


} // namespace file
} // namespace hdf5
