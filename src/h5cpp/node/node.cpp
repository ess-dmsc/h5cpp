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
//          Sebastian Koenig <skoenig@ncsu.edu>
// Created on: Sep 11, 2017
//
#include <stdexcept>
#include <h5cpp/node/node.hpp>
#include <h5cpp/error/error.hpp>

namespace hdf5 {
namespace node {

Node::Node():
    attributes(*this),
    handle_(),
    link_()
{}

Node::Node(ObjectHandle &&handle,const Link &link):
    attributes(*this),
    handle_(std::move(handle)),
    link_(link)
{}

Node::Node(const Node &node):
    attributes(*this),
    handle_(node.handle_),
    link_(node.link_)
{}

Node &Node::operator=(const Node &node)
{
  if(this == &node)
    return *this;

  handle_ = node.handle_;
  link_   = node.link_;

  return *this;
}

Node::~Node()
{}

void Node::close()
{
  handle_.close();
  link_ = Link();
}

NodeType Node::type() const
{
  H5O_info_t_ info;
#if H5_VERSION_LE(1,10,2)
  if(H5Oget_info(static_cast<hid_t>(*this),&info)<0)
#else
  if(H5Oget_info1(static_cast<hid_t>(*this),&info)<0)
#endif
  {
    error::Singleton::instance().throw_with_stack("Error retrieving type information for this node!");
  }

  return static_cast<NodeType>(info.type);
}

bool Node::is_valid() const
{
  return handle_.is_valid();
}

ObjectId Node::id() const
{
  return ObjectId(handle_);
}

bool operator==(const Node &lhs, const Node &rhs)
{
  return lhs.id() == rhs.id();
}

bool operator!=(const Node &lhs, const Node &rhs)
{
  return lhs.id() != rhs.id();
}

const Link &Node::link() const
{
  return link_;
}

} // namespace node
} // namespace hdf5
