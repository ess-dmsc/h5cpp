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
#include "../iterator.hpp"
#include "link_view.hpp"
#include "link.hpp"
#include "../windows.hpp"

namespace hdf5 {
namespace node {

class DLL_EXPORT LinkIterator : public Iterator
{
  public:
    using value_type = Link;
    using pointer = value_type*;
    using reference = value_type&;
    using difference_type = ssize_t;
    using iterator_category = std::random_access_iterator_tag;

    LinkIterator() = delete;
    LinkIterator(const LinkIterator&) = default;
    LinkIterator(const LinkView &view,ssize_t index);

#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-compare"
#endif
    explicit operator bool() const
    {
      return !(index()<0 || index()>=view_.get().size());
    }
#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif

    value_type operator*() const;

    value_type *operator->();

    LinkIterator &operator++();
    LinkIterator operator++(int);
    LinkIterator &operator--();
    LinkIterator operator--(int);

    LinkIterator &operator+=(ssize_t i);
    LinkIterator &operator-=(ssize_t i);

    bool operator==(const LinkIterator &a) const;

    bool operator!=(const LinkIterator &a) const;

  private:
    std::reference_wrapper<const LinkView> view_;
    Link current_link_;

};

} // namespace node
} // namespace hdf5
