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
// Authors: Eugen Wintersberger <eugen.wintersberger@desy.de>
//          Martin Shetty <martin.shetty@esss.se>
//          Jan Kotanski <jan.kotanski@desy.de>
// Created on: Sep 11, 2017
//

#include <sstream>
#include <h5cpp/node/group.hpp>
#include <h5cpp/node/functions.hpp>

namespace hdf5 {
namespace node {

Group::Group():
    Node(),
    links(*this),
    nodes(*this),
    iter_config_(IteratorConfig())
{}

Group::Group(const Group &group):
    Node(group),
    links(*this),
    nodes(*this),
    iter_config_(group.iterator_config())
{
}

Group::Group(const Node &node):
    Node(node),
    links(*this),
    nodes(*this),
    iter_config_(IteratorConfig())
{
  if(node.type()!=Type::Group)
  {
    std::stringstream ss;
    ss<<"Construction of a Group from a Node failed since ";
    ss<<"Node ["<<node.link().path()<<"] is not a group!";
    throw std::runtime_error(ss.str());
  }
}

Group::Group(const Group &parent, const Path &path,
             const property::LinkCreationList &lcpl,
             const property::GroupCreationList &gcpl,
             const property::GroupAccessList &gapl):
     Node(),
     links(*this),
     nodes(*this),
     iter_config_(IteratorConfig())
{
  hid_t gid = 0;

  if((gid=H5Gcreate(static_cast<hid_t>(parent),
                    static_cast<std::string>(path).c_str(),
                    static_cast<hid_t>(lcpl),
                    static_cast<hid_t>(gcpl),
                    static_cast<hid_t>(gapl)))<0)
  {
    std::stringstream ss;
    ss<<"Failure to create new group ["<<path<<"] below ["
      <<parent.link().path()<<"]!";
    hdf5::error::Singleton::instance().throw_with_stack(ss.str());
  }
  H5Gclose(gid);

  *this = node::get_node(parent,path);
}


Group &Group::operator=(const Group &group)
{
  if(this == &group)
    return *this;

  Node::operator=(group);
  return *this;
}

bool Group::exists(const std::string &name,
                   const property::LinkAccessList &lapl) const
{
  return (links.exists(name, lapl) && nodes.exists(name, lapl));
}

Group Group::create_group(const std::string &name,
                          const property::LinkCreationList &lcpl,
                          const property::GroupCreationList &gcpl,
                          const property::GroupAccessList &gapl) const
{
  //check if the name is a valid group name
  if(!Path(name).is_name())
  {
    std::stringstream ss;
    ss<<"["<<name<<"] is not a valid child name!";
    throw std::runtime_error(ss.str());
  }

  return Group(*this,Path(name),lcpl,gcpl,gapl);
}

Dataset Group::create_dataset(const std::string &name,
                              const datatype::Datatype &type,
                              const dataspace::Dataspace &space,
                              const property::DatasetCreationList &dcpl,
                              const property::LinkCreationList &lcpl,
                              const property::DatasetAccessList &dapl) const
{
  if(!Path(name).is_name())
  {
    std::stringstream ss;
    ss<<"["<<name<<"] is not a valid child name!";
    throw std::runtime_error(ss.str());
  }

  return Dataset(*this,Path(name),type,space,lcpl,dcpl,dapl);
}

Node Group::operator[](const Path &path) const
{
  return hdf5::node::get_node(*this, path);
}

void Group::create_link(const Path &link_path,
                        const fs::path &target_file,
                        const Path &target_path,
                        const property::LinkCreationList &lcpl,
                        const property::LinkAccessList &lapl)
{
  hdf5::node::link(target_file, target_path, *this, link_path, lcpl, lapl);
}

void Group::create_link(const Path &link_path,
                        const Path &target_path,
                        const property::LinkCreationList &lcpl,
                        const property::LinkAccessList &lapl)
{
  hdf5::node::link(target_path, *this, link_path, lcpl, lapl);
}

void Group::create_link(const Path &link_path,
                        const Node &target,
                        const property::LinkCreationList &lcpl,
                        const property::LinkAccessList &lapl)
{
  hdf5::node::link(target, *this, link_path, lcpl, lapl);
}

void Group::copy_here(const Path &link_path,
                      const Node &target,
                      const property::ObjectCopyList &ocpl,
                      const property::LinkCreationList &lcpl)
{
  hdf5::node::copy(target, *this, link_path, ocpl, lcpl);
}

void Group::copy_here(const Node &target,
                      const property::ObjectCopyList &ocpl,
                      const property::LinkCreationList &lcpl)
{
  hdf5::node::copy(target, *this, ocpl, lcpl);
}

void Group::move_here(const Path &link_path,
                      const Node &target,
                      const property::LinkCreationList &lcpl,
                      const property::LinkAccessList &lapl)
{
  hdf5::node::move(target, *this, link_path, lcpl, lapl);
}

void Group::move_here(const Node &target,
                      const property::LinkCreationList &lcpl,
                      const property::LinkAccessList &lapl)
{
  hdf5::node::move(target, *this, lcpl, lapl);
}

void Group::remove(const Path &path,
                   const property::LinkAccessList &lapl)
{
  hdf5::node::remove(*this, path, lapl);
}

bool Group::has_group(const Path &path, const property::LinkAccessList &lapl) const noexcept
{
  bool ret = false;
  try
  {
    ret = hdf5::node::is_group(hdf5::node::get_node(*this, path, lapl));
  }
  catch (...)
  {
    return false;
  }
  return ret;
}

bool Group::has_dataset(const Path &path, const property::LinkAccessList &lapl) const noexcept
{
  bool ret = false;
  try
  {
    ret = hdf5::node::is_dataset(hdf5::node::get_node(*this, path, lapl));
  }
  catch (...)
  {
    return false;
  }
  return ret;
}

Group Group::get_group(const Path &path, const property::LinkAccessList &lapl) const
{
  return hdf5::node::get_group(*this, path, lapl);
}

Dataset Group::get_dataset(const Path &path, const property::LinkAccessList &lapl) const
{
  return hdf5::node::get_dataset(*this, path, lapl);
}

#if H5_VERSION_GE(1,10,0)
void Group::flush() const
{
  if (H5Gflush(static_cast<hid_t>(*this)) < 0)
  {
    error::Singleton::instance().throw_with_stack("Failure to flush the group!");
  }
}
#endif

} // namespace node
} // namespace hdf5
