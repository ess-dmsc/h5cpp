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
// Created on: Sep 14, 2017
//
#pragma once

#include <h5cpp/core/iterator.hpp>
#include <h5cpp/core/windows.hpp>
#include <h5cpp/attribute/attribute.hpp>
#include <h5cpp/attribute/attribute_manager.hpp>

namespace hdf5 {
namespace attribute {

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wweak-vtables"
#endif
class DLL_EXPORT AttributeIterator : public Iterator
{
  public:
    using value_type = Attribute;
    using pointer = value_type*;
    using reference = value_type&;
    using difference_type = ssize_t;
    using iterator_category = std::random_access_iterator_tag;

    AttributeIterator() = delete;
    AttributeIterator(const AttributeIterator&) = default;
    AttributeIterator(const AttributeManager &manager,ssize_t index);

    explicit operator bool() const
    {
      return !(index()<0 || index()>=static_cast<ssize_t>(manager_.get().size()));
    }

    value_type operator*() const;

    value_type *operator->();

    AttributeIterator &operator++();
    AttributeIterator operator++(int);
    AttributeIterator &operator--();
    AttributeIterator operator--(int);

    AttributeIterator &operator+=(ssize_t i);
    AttributeIterator &operator-=(ssize_t i);

    bool operator==(const AttributeIterator &a) const;

    bool operator!=(const AttributeIterator &a) const;

  private:
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4251)
#endif
    std::reference_wrapper<const AttributeManager> manager_;
#ifdef _MSC_VER
#pragma warning(pop)
#endif
    Attribute current_attribute_;

};
#ifdef __clang__
#pragma clang diagnostic pop
#endif

} // namespace attribute
} // namespace hdf5
