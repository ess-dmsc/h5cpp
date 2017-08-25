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
// Created on: Aug 24, 2017
//
#pragma once

#include "object_handle.hpp"
#include "attribute.hpp"
#include "container_iterator.hpp"

namespace hdf5 {

class AttributeView
{
  public:
    using value_type = Attribute;
    using const_iterator= ContainerIterator<const AttributeView>;


    AttributeView(ObjectHandle &handle);

    value_type create(const std::string &name);

    value_type operator[](size_t index) const;
    value_type operator[](const std::string &name) const;

    size_t size() const;
    bool exists(const std::string &name) const;
    void remove(const std::string &name) const;
    void remove(size_t index) const;


    const_iterator begin() const;
    const_iterator end() const;

  private:
    ObjectHandle &handle_;


};

} // namespace hdf5
