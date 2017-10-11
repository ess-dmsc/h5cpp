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
// Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
// Created on: Sep 11, 2017
//

#include <sstream>
#include <h5cpp/node/group.hpp>
#include "utilities.hpp"

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
{}


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
                          const property::GroupAccessList &gapl)
{
  //check if the name is a valid group name
  if(!is_valid_child_name(name))
  {
    std::stringstream ss;
    ss<<"["<<name<<"] is not a valid child name!";
    throw std::runtime_error(ss.str());
  }

  //check if there is already a link with this name
  if(this->links.exists(name))
  {
    std::stringstream ss;
    ss<<"A link with name ["<<name<<"] already exists below ["
      <<link().path()<<"]!";
    throw std::runtime_error(ss.str());
  }

  try
  {
    ObjectHandle handle(H5Gcreate(static_cast<hid_t>(*this),
                                  name.c_str(),
                                  static_cast<hid_t>(lcpl),
                                  static_cast<hid_t>(gcpl),
                                  static_cast<hid_t>(gapl)
                                  ));

    return Group(Node(std::move(handle),links[name]));

  }
  catch(const std::runtime_error &error)
  {
    std::stringstream ss;
    ss<<"Could not create group of name ["<<name<<"] below ";
    ss<<"group ["<<link().path()<<"]";
    throw std::runtime_error(ss.str());
  }
}

Dataset Group::create_dataset(const std::string &name,
                              const datatype::Datatype &type,
                              const dataspace::Dataspace &space,
                              const property::LinkCreationList &lcpl,
                              const property::DatasetCreationList &dcpl,
                              const property::DatasetAccessList &dapl)
{
  if(!is_valid_child_name(name))
  {
    std::stringstream ss;
    ss<<"["<<name<<"] is not a valid name for a dataset!";
    throw std::runtime_error(ss.str());
  }

  try
  {
    ObjectHandle handle(H5Dcreate(static_cast<hid_t>(*this),
                                  name.c_str(),
                                  static_cast<hid_t>(type),
                                  static_cast<hid_t>(space),
                                  static_cast<hid_t>(lcpl),
                                  static_cast<hid_t>(dcpl),
                                  static_cast<hid_t>(dapl)));
    Link new_link(link().file(),link().path(),name);
    return Dataset(Node(std::move(handle),new_link));

  }
  catch(const std::runtime_error &error)
  {
    std::stringstream ss;
    ss<<"Failure creating dataset ["<<name<<"] below ["<<link().path()<<"]!";
    throw std::runtime_error(ss.str());
  }
}

Node Group::operator[](const std::string &name) const
{
  return nodes[name];
}

} // namespace node
} // namespace hdf5
