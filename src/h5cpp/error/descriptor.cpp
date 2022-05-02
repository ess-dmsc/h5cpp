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
#include <h5cpp/core/utilities.hpp>
#include <stdexcept>
#include <vector>

extern "C"{
#ifdef __clang__
#include <string.h>
#else
#include <cstring>
#endif
}



namespace hdf5 {
namespace error {

// can't throw here (HDF5 C implementation disallows it)
Descriptor::Descriptor(const H5E_error2_t& descr)
{
  line = descr.line;

  maj_num = descr.maj_num;
  min_num = descr.min_num;

  if (descr.file_name && (strlen(descr.file_name) > 0))
    file = std::string(descr.file_name, strlen(descr.file_name));
  if (descr.func_name && (strlen(descr.func_name) > 0))
    function = std::string(descr.func_name, strlen(descr.func_name));
  if (descr.desc && (strlen(descr.desc) > 0))
    description = std::string(descr.desc, strlen(descr.desc));
}

// could throw here, but probably shouldn't
void Descriptor::extract_strings()
{
  H5E_type_t message_type;
  ssize_t    message_size = 0;

  // retrieve the major error message
  message_size = H5Eget_msg(maj_num,&message_type,nullptr,0);
  if(message_size > 0 && message_type == H5E_MAJOR)
  {
    std::vector<char> message_buffer(signed2unsigned<size_t>(message_size+1));
    H5Eget_msg(maj_num,&message_type,message_buffer.data(),signed2unsigned<size_t>(message_size+1));
    major = std::string(message_buffer.begin(),--message_buffer.end());
  }

  // retrieve the minor error message
  message_size = H5Eget_msg(min_num,&message_type,nullptr,0);
  if(message_size > 0 && message_type == H5E_MINOR)
  {
    std::vector<char> message_buffer(signed2unsigned<size_t>(message_size+1));
    H5Eget_msg(min_num,&message_type,message_buffer.data(),signed2unsigned<size_t>(message_size+1));
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
