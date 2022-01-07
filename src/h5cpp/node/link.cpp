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
// Created on: Sep 11, 2017
//
#include <sstream>
#include <h5cpp/node/link.hpp>
#include <h5cpp/node/node.hpp>
#include <h5cpp/file/file.hpp>
#include <h5cpp/node/group.hpp>
#include <h5cpp/node/functions.hpp>
#include <h5cpp/error/error.hpp>

namespace hdf5 {
namespace node {

LinkTarget::LinkTarget():
    file_(),
    object_path_()
{}

LinkTarget::LinkTarget(const hdf5::Path &object_path):
    file_(),
    object_path_(object_path)
{}

LinkTarget::LinkTarget(const hdf5::Path &object_path,
                       const fs::path &file_path):
    file_(file_path),
    object_path_(object_path)
{}

fs::path LinkTarget::file_path() const
{
  return file_;
}

hdf5::Path LinkTarget::object_path() const
{
  return object_path_;
}

Link::Link(const file::File &file,const Path &parent_path,
           const std::string &link_name):
    parent_file_(file),
    parent_path_(parent_path),
    name_(link_name)
{}

Path Link::path() const
{
  if(name_ == "/")
    return parent_path_;
  else
    return parent_path_+ name_;
}

H5L_info_t Link::get_link_info(const property::LinkAccessList &lapl) const
{
  H5L_info_t info;
   if(H5Lget_info(static_cast<hid_t>(parent()),
                  name_.c_str(),
                  &info,
                  static_cast<hid_t>(lapl))<0)
   {
     std::stringstream ss;
     ss<<"Failure retrieving information for link ["<<name_<<"] on group"
       <<" ["<<parent_path_<<"]!";
     error::Singleton::instance().throw_with_stack(ss.str());
   }

   return info;
}

std::string Link::get_link_value(const property::LinkAccessList &lapl) const
{
  H5L_info_t info = get_link_info(lapl);
  std::string value(info.u.val_size-1,' ');

  if(H5Lget_val(static_cast<hid_t>(parent()),
                name_.c_str(),
                reinterpret_cast<void*>(const_cast<char*>(value.data())),
                info.u.val_size,
                static_cast<hid_t>(lapl))<0)
  {
    std::stringstream ss;
    ss<<"Failure to retrieve link value for link ["<<name_<<"] below "
      <<"group ["<<parent_path_<<"]!";
    error::Singleton::instance().throw_with_stack(ss.str());
  }

  return value;
}

LinkTarget Link::get_soft_link_target(const property::LinkAccessList &lapl ) const
{
  std::string value = get_link_value(lapl);

  return LinkTarget(Path(value));
}

LinkTarget Link::get_external_link_target(const property::LinkAccessList &lapl) const
{
  std::string value = get_link_value(lapl);

  const char *filename_buffer,
             *objectpath_buffer;

  if(H5Lunpack_elink_val(value.c_str(),value.size()+1,nullptr,
                         &filename_buffer,&objectpath_buffer)<0)
  {
    std::stringstream ss;
    ss<<"Failure decoding external link target for link ["<<name_<<"] below"
      <<" group ["<<static_cast<std::string>(parent_path_)<<"]!";
    error::Singleton::instance().throw_with_stack(ss.str());
  }

  return LinkTarget(Path(std::string(objectpath_buffer)),
                    fs::path(filename_buffer));

}

LinkTarget Link::target(const property::LinkAccessList &lapl) const
{
  switch(type(lapl))
  {
    case LinkType::Hard:
      return LinkTarget(parent_path_+name_);
    case LinkType::Soft:
      return get_soft_link_target(lapl);
    case LinkType::External:
      return get_external_link_target(lapl);
    default:
      throw std::runtime_error("Unkown link type - cannot determine target!");
  }

}

LinkType Link::type(const property::LinkAccessList &lapl) const
{
  //in the case of a default constructed instance the link type is ERROR
  if(!parent_file_.is_valid())
    return LinkType::Error;

  H5L_info_t info = get_link_info(lapl);
  switch(info.type)
  {
    case H5L_TYPE_HARD: return LinkType::Hard;
    case H5L_TYPE_SOFT: return LinkType::Soft;
    case H5L_TYPE_EXTERNAL: return LinkType::External;
    default:
      return LinkType::Error;
  }
}

Group Link::parent() const
{
  Group result = parent_file_.root();

  if(name_=="/") return result;

  for(auto link_name: parent_path_)
    result = result.nodes[link_name];

  return result;
}

const file::File &Link::file() const
{
  return parent_file_;
}

Node Link::operator*() const
{
  return get_node(parent_file_.root(),parent_path_+name_);
}

bool Link::exists() const
{
  Group parent = parent_file_.root();

  for(auto link_name: parent_path_)
  {
    if(parent.nodes.exists(link_name))
      parent = parent.nodes[link_name];
    else
      return false;
  }

  return parent.links.exists(name_);
}

bool Link::is_resolvable() const
{
  if(exists())
  {
    try
    {
      *(*this);
      return true;
    }
    catch(...)
    {
      return false;
    }
  }
  else
    return false;
}


bool operator==(const Link &lhs, const Link &rhs)
{
  return (lhs.parent_file_.path() == rhs.parent_file_.path()) &&
      (lhs.parent_path_ == rhs.parent_path_) &&
      (lhs.name_ == rhs.name_);
}

bool operator!=(const Link &lhs, const Link &rhs)
{
  return !(lhs == rhs);
}

std::ostream &operator<<(std::ostream &stream,const Link &link)
{
  return stream << link.file().path() << ":" << link.path();
}

} // namespace node
} // namespace hdf5
