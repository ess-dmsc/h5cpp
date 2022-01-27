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
// Created on: Sep 13, 2017
//
#pragma once

#include <functional>
#include <h5cpp/core/iterator.hpp>
#include <h5cpp/node/link_view.hpp>
#include <h5cpp/node/link.hpp>
#include <h5cpp/core/windows.hpp>
#include <h5cpp/node/group.hpp>

namespace hdf5 {
namespace node {

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wweak-vtables"
#endif
class DLL_EXPORT LinkIterator : public Iterator
{
  public:
    using value_type = Link;
    using pointer = value_type*;
    using reference = value_type&;
    using difference_type = ssize_t;
    using iterator_category = std::bidirectional_iterator_tag;

    LinkIterator() = delete;

    static LinkIterator begin(const Group &group);
    static LinkIterator end(const Group &group);

  value_type operator*() const;
    value_type *operator->();
    LinkIterator &operator++();
    LinkIterator operator++(int);
    LinkIterator &operator--();
    LinkIterator operator--(int);

    bool operator==(const LinkIterator &a) const;
    bool operator!=(const LinkIterator &a) const;

  private:
    LinkIterator(const Group &group,ssize_t index);
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4251)
#endif
    Group group_;
#ifdef _MSC_VER
#pragma warning(pop)
#endif
    mutable Link current_link_;

};
#ifdef __clang__
#pragma clang diagnostic pop
#endif

} // namespace node
} // namespace hdf5
