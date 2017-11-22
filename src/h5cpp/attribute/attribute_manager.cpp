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
// Created on: Oct 4, 2017
//
#include <sstream>
#include <h5cpp/node/node.hpp>
#include <h5cpp/attribute/attribute_manager.hpp>
#include <h5cpp/attribute/attribute_iterator.hpp>
#include <h5cpp/error/error.hpp>

namespace hdf5 {
namespace attribute {

AttributeManager::AttributeManager(node::Node &node):
    node_(node),
    iter_config_()
{}

Attribute AttributeManager::operator[](size_t index) const
{
  hid_t id = H5Aopen_by_idx(static_cast<hid_t>(node_),".",
                            static_cast<H5_index_t>(iter_config_.index()),
                            static_cast<H5_iter_order_t>(iter_config_.order()),
                            index,
                            H5P_DEFAULT,
                            static_cast<hid_t>(iter_config_.link_access_list())
                            );
  if(id<0)
  {
    std::stringstream ss;
    ss<<"Failure to access attribute ["<<index<<"] of node ["
      <<node_.link().path()<<"]!";
    error::Singleton::instance().throw_with_stack(ss.str());
  }

  return Attribute(ObjectHandle(id));

}

Attribute AttributeManager::operator[](const std::string &name) const
{
  hid_t id = H5Aopen_by_name(static_cast<hid_t>(node_),".",
                             name.c_str(),
                             H5P_DEFAULT,
                             static_cast<hid_t>(iter_config_.link_access_list())
                             );
  if(id<0)
  {
    std::stringstream ss;
    ss<<"Failure to access attribute ["<<name<<"] from node ["
      <<node_.link().path()<<"]!";
    error::Singleton::instance().throw_with_stack(ss.str());
  }

  return Attribute(ObjectHandle(id));
}

size_t AttributeManager::size() const
{
  H5O_info_t obj_info;
  if(H5Oget_info(static_cast<hid_t>(node_),&obj_info))
  {
    error::Singleton::instance().throw_with_stack("Failure to determine the number of attributes!");
  }

  return obj_info.num_attrs;
}

void AttributeManager::remove(const std::string &name) const
{
  if(H5Adelete_by_name(static_cast<hid_t>(node_),".",name.c_str(),
                       static_cast<hid_t>(iter_config_.link_access_list()))<0)
  {
    std::stringstream ss;
    ss<<"Failure to remove attribute ["<<name<<"] from node ["
      <<node_.link().path()<<"]!";
    error::Singleton::instance().throw_with_stack(ss.str());
  }
}

void AttributeManager::remove(size_t index) const
{
  if(H5Adelete_by_idx(static_cast<hid_t>(node_),".",
                      static_cast<H5_index_t>(iter_config_.index()),
                      static_cast<H5_iter_order_t>(iter_config_.order()),
                      index,
                      static_cast<hid_t>(iter_config_.link_access_list()))<0)
  {
    std::stringstream ss;
    ss<<"Failure to remove attribute ["<<index<<"] from node ["
      <<node_.link().path()<<"]!";
    error::Singleton::instance().throw_with_stack(ss.str());
  }
}

bool AttributeManager::exists(const std::string &name) const
{
  htri_t result = H5Aexists_by_name(static_cast<hid_t>(node_),".",
                                    name.c_str(),
                                    static_cast<hid_t>(iter_config_.link_access_list()));
  if(result > 0)
    return true;
  if(result == 0)
    return false;
  else
  {
    std::stringstream ss;
    ss<<"Failure to check the existence of attribute ["<<name<<"] on node ["
      <<node_.link().path()<<"]!";
    error::Singleton::instance().throw_with_stack(ss.str());
  }
}

Attribute AttributeManager::create(const std::string &name,
                                   const datatype::Datatype &datatype,
                                   const dataspace::Dataspace &dataspace,
                                   const property::AttributeCreationList &acpl) const
{
  hid_t id = H5Acreate(static_cast<hid_t>(node_),
                       name.c_str(),
                       static_cast<hid_t>(datatype),
                       static_cast<hid_t>(dataspace),
                       static_cast<hid_t>(acpl),
                       H5P_DEFAULT);
  if(id<0)
  {
    std::stringstream ss;
    ss<<"Failure to create attribute ["<<name<<"] on node ["
      <<node_.link().path()<<"]!";
    error::Singleton::instance().throw_with_stack(ss.str());
  }

  return Attribute(ObjectHandle(id));
}

void AttributeManager::rename(const std::string &old_name,const std::string &new_name) const
{
  if(H5Arename(static_cast<hid_t>(node_),old_name.c_str(),new_name.c_str())<0)
  {
    std::stringstream ss;
    ss<<"Failure to rename attribute ["<<old_name<<"] to ["<<new_name<<"] "
      <<"on node ["<<node_.link().path()<<"]!";
    error::Singleton::instance().throw_with_stack(ss.str());
  }
}

IteratorConfig &AttributeManager::iterator_config() noexcept
{
  return iter_config_;
}

const IteratorConfig &AttributeManager::iterator_config() const noexcept
{
  return iter_config_;
}

const node::Node &AttributeManager::node() const
{
  return node_;
}

AttributeIterator AttributeManager::begin() const
{
  return AttributeIterator(*this,0);
}

AttributeIterator AttributeManager::end() const
{
  return AttributeIterator(*this,size());
}

} // namespace attribute
} // namespace hdf5
