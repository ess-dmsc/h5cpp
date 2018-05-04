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
// WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
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
#include <stdexcept>
#include <vector>

extern "C"{
#include <cstring>
}

namespace hdf5 {
namespace error {

Descriptor::Descriptor(const H5E_error2_t& descr)
{
  line = descr.line;
  file = std::string(descr.file_name, strlen(descr.file_name));
  function = std::string(descr.func_name, strlen(descr.func_name));
  description = std::string(descr.desc, strlen(descr.desc));

  H5E_type_t message_type;
  ssize_t    message_size = 0;

  //
  // retrieve the major error message
  //
  message_size = H5Eget_msg(descr.maj_num,&message_type,NULL,0);
  if(message_size<0)
  {
    throw std::runtime_error("Failure to obtain major error message!");
  }
  if(message_size > 0 && message_type == H5E_MAJOR)
  {
    std::vector<char> message_buffer(message_size+1);
    H5Eget_msg(descr.maj_num,&message_type,message_buffer.data(),message_size+1);
    major = std::string(message_buffer.begin(),--message_buffer.end());
  }

  //
  // retrieve the minor error message
  //
  message_size = H5Eget_msg(descr.min_num,&message_type,NULL,0);
  if(message_size < 0)
  {
    throw std::runtime_error("Failure to obtain minor error message!");
  }
  if(message_size > 0 && message_type == H5E_MINOR)
  {
    std::vector<char> message_buffer(message_size+1);
    H5Eget_msg(descr.min_num,&message_type,message_buffer.data(),message_size+1);
    minor = std::string(message_buffer.begin(),--message_buffer.end());
  }
}

std::ostream &operator<<(std::ostream &stream, const Descriptor &desc)
{
  stream << desc.file << ":" << desc.line
         << " in function '" << desc.function << "': "
         << desc.description
         << " (maj=" << desc.major
         << ", min=" << desc.minor
         << ")";
  return stream;
}


} // namespace file
} // namespace hdf5
