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
// Authors:
//   Eugen Wintersberger <eugen.wintersberger@desy.de>
//   Martin Shetty <martin.shetty@esss.se>
//   Jan Kotanski <jan.kotanski@desy.de>
// Created on: Sep 8, 2017
//

#include <h5cpp/file/file.hpp>
#include <h5cpp/node/node.hpp>
#include <h5cpp/node/group.hpp>
#include <h5cpp/error/error.hpp>
#include <h5cpp/core/utilities.hpp>
#include <h5cpp/property/file_access.hpp>

namespace hdf5 {
namespace file {

File::File(ObjectHandle &&handle) :
    handle_(std::move(handle))
{

}

AccessFlags File::intent() const
{
  AccessFlagsBase value;
  if (H5Fget_intent(static_cast<hid_t>(*this), &value) < 0)
  {
    error::Singleton::instance().throw_with_stack("Failure retrieving the file intent!");
  }

  return static_cast<AccessFlags>(value);
}

size_t File::size() const
{
  hsize_t s;
  if (H5Fget_filesize(static_cast<hid_t>(*this), &s) < 0)
  {
    error::Singleton::instance().throw_with_stack("Failure retrieving the file size!");
  }
  return s;
}

ssize_t File::buffer_size() const
{
  ssize_t s = H5Fget_file_image(static_cast<hid_t>(*this), nullptr, 0);
  if (s < 0)
    {
      error::Singleton::instance().throw_with_stack("Failure retrieving the buffer size");
    }
  return s;
}

void File::flush(Scope scope) const
{
  if (H5Fflush(static_cast<hid_t>(*this), static_cast<H5F_scope_t>(scope)) < 0)
  {
    error::Singleton::instance().throw_with_stack("Failure to flush the file!");
  }
}


void File::close()
{
  property::FileAccessList fapl = property::FileAccessList(ObjectHandle(H5Fget_access_plist(static_cast<hid_t>(*this))));

  if(fapl.close_degree() == property::CloseDegree::Strong)
  {
    hid_t mid= static_cast<hid_t>(*this);
    handle_.close();
    // closes all copies of file hid_t's created with Node::link_.parent_file_
    while(H5Iget_type(mid) > 0)
    {
      H5Fclose(mid);
    }
  }
  else
  {
    handle_.close();
  }
}

fs::path File::path() const
{
  ssize_t size = H5Fget_name(static_cast<hid_t>(*this), nullptr, 0);

  if (size < 0)
  {
    error::Singleton::instance().throw_with_stack("Failure to determine file name length!");
  }

  std::vector<char> buffer(signed2unsigned<size_t>(size + 1));
  if (H5Fget_name(static_cast<hid_t>(*this), buffer.data(), signed2unsigned<size_t>(size + 1)) < 0)
  {
    std::stringstream ss;
    ss << "Error retrieving file name of size " << size << " for HDF5 file!";
    error::Singleton::instance().throw_with_stack(ss.str());
  }

  return fs::path(std::string(buffer.begin(), --buffer.end()));
}

size_t File::count_open_objects(SearchFlagsBase flags) const
{
  ssize_t nobjects = 0;
  nobjects = H5Fget_obj_count(static_cast<hid_t>(*this), flags);
  if (nobjects < 0)
  {
    error::Singleton::instance().throw_with_stack("Failure retrieving the open object count for this file!");
  }

  return signed2unsigned<size_t>(nobjects);
}

size_t File::count_open_objects(SearchFlags flag) const
{
  return count_open_objects(static_cast<SearchFlagsBase>(flag));
}

class node::Group File::root(const property::GroupAccessList &gapl) const
{
  try
  {
    ObjectHandle handle(H5Gopen(static_cast<hid_t>(*this), "/", static_cast<hid_t>(gapl)));
    node::Link root_link(*this, Path("/"), "/");

    return node::Group(node::Node(std::move(handle), root_link));
  }
  catch (...)
  {
    std::throw_with_nested(std::runtime_error("Error obtaining root group from file!"));
  }
}

bool File::is_valid() const
{
  return handle_.is_valid();
}

ObjectId File::id() const
{
  bool valid = false;
  try
  {
    valid = is_valid();
  }
  catch (...)
  {
    std::throw_with_nested(std::runtime_error("Cannot obtain ObjectId from an invalid file instance!"));
  }

  if (!valid)
  {
    error::Singleton::instance().throw_with_stack("Cannot obtain ObjectId from an invalid file instance!");
  }

  return ObjectId(handle_);
}

} // namespace file
} // namespace hdf5
