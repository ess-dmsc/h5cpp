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
#include <stdexcept>
#include <sstream>
#include <h5cpp/node/node.hpp>
#include <h5cpp/node/node_view.hpp>
#include <h5cpp/node/group.hpp>
#include <h5cpp/node/node_iterator.hpp>

namespace hdf5 {
namespace node {

NodeView::NodeView(Group &node):
    GroupView(node)
{}

NodeView::~NodeView()
{}



Node NodeView::operator[](size_t index) const
{
  const IteratorConfig &config = group().iterator_config();
  hid_t id = H5Oopen_by_idx(static_cast<hid_t>(group()),
                            ".",
                            static_cast<H5_index_t>(config.index()),
                            static_cast<H5_iter_order_t>(config.order()),
                            index,
                            static_cast<hid_t>(config.link_access_list()));

  if(id<0)
  {
    std::stringstream ss;
    ss<<"Failure opening child with index "<<index<<" from group ";
    ss<<group().link().path();
    error::Singleton::instance().throw_with_stack(ss.str());
  }


  Link new_link(group().link().file(),group().link().path(),
                group().links[index].path().name());

  return Node(ObjectHandle(id),new_link);
}

Node NodeView::operator[](const std::string &name) const
{
  if(!Path(name).is_name())
  {
    throw std::runtime_error("["+name+"] is not a valid name for a child object!");
  }

  const IteratorConfig &config = group().iterator_config();
  hid_t id  = H5Oopen(static_cast<hid_t>(group()),
                      name.c_str(),
                      static_cast<hid_t>(config.link_access_list()));
  if(id<0)
  {
    error::Singleton::instance().throw_with_stack("Failure open child node ["+name+"]!");
  }

  //returning an object with the new path
  return Node(ObjectHandle(id),Link(group().link().file(),group().link().path(),name));

}

bool NodeView::exists(const std::string &name, const property::LinkAccessList &lapl) const
{
  //we first have to check whether the link exists
  if(!group().links.exists(name, lapl))
    return false;

  htri_t result = H5Oexists_by_name(static_cast<hid_t>(group()),
                                    name.c_str(),
                                    static_cast<hid_t>(lapl));
  if(result>0)
  {
    return true;
  }
  else if(result == 0)
  {
    return false;
  }
  else
  {
    std::stringstream ss;
    ss<<"Failure to check if object ["<<name<<"] exists below ["
      <<group().link().path()<<"]!";
    error::Singleton::instance().throw_with_stack(ss.str());
  }
#ifndef  __clang__
  return false;
#endif
}

NodeView::const_iterator NodeView::begin() const
{
  return NodeIterator::begin(group());
}

NodeView::const_iterator NodeView::end() const
{
  return NodeIterator::end(group());
}


} // namespace node
} // namespace hdf5
