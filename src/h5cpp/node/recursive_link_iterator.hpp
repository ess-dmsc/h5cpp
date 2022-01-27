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
// Created on: Nov 20, 2017
//
#pragma once

#include <functional>
#include <h5cpp/node/group.hpp>
#include <h5cpp/node/link_iterator.hpp>
#include <h5cpp/core/windows.hpp>

namespace hdf5 {
namespace node {

//!
//! \brief recursive Link iterator
//!
//! Iterator which recursively iterates over all Links of a particular
//! group.
//! All relevant constructors are private. To construct an instance of
//! this iterator use the two static factory functions begin() and end().
//!
//! \code
//! Group top = ...;
//! auto iter = RecursiveLinkIterator::begin(top);
//! auto end  = RecursiveLinkIterator::end(top);
//!
//! while(iter != end)
//! {
//!   //do something here
//!   ++iter;
//! }
//! // or with STL
//!
//! std::for_each(RecursiveLinkIterator::begin(top),
//!               RecursiveLinkIterator::end(top),
//!               [](const Link &link) { ...do something ... ; });
//! \endcode
//!
//! Unlike LinkIterator, RecursiveLinkIterator is a simple forward iterator.
//!
//!
class DLL_EXPORT RecursiveLinkIterator
{
  public:
    using value_type = Link;
    using pointer = value_type*;
    using reference = value_type&;
    using difference_type = ssize_t;
    using iterator_category = std::forward_iterator_tag;

    //!
    //! \brief default constructor
    //!
    //! There is no default constructors -> would not make too much sense.
    //!
    RecursiveLinkIterator() = delete;

    //!
    //! \brief create iterator to the first element
    //!
    //! Static factory function returning an instance of
    //! RecursiveLinkIterator on the first element of the top group.
    //!
    //! \param current_group the top level group where to start with
    //!                      recursive iteration
    //! \return instance of RecursiveLinkIterator
    //!
    static RecursiveLinkIterator begin(const Group &current_group);

    //!
    //! \brief create iterator to the last+1 element
    //!
    //! Static factory function returning an instance of
    //! RecursiveLinkIterator on the last+1 element of top group.
    //!
    //! \param current_group the top level group at which to start the
    //!                      recursive iteration.
    //! \return instance of RecursiveLinkIterator
    //!
    static RecursiveLinkIterator end(const Group &current_group);


    Link operator*() const;
    Link *operator->();
    RecursiveLinkIterator &operator++();
    RecursiveLinkIterator operator++(int);
    bool operator==(const RecursiveLinkIterator &rhs) const;
    bool operator!=(const RecursiveLinkIterator &rhs) const;

  private:
    RecursiveLinkIterator(const Group &current_group,
                          RecursiveLinkIterator parent_iterator);
    RecursiveLinkIterator(const Group &current_group);

    using IteratorPointer = std::shared_ptr<RecursiveLinkIterator>;

    //!
    //! references the current group we are in. We have to keep this
    //! as an object we are iterating upon must not be destroyed.
    //!
    Group           current_group_;

    //!
    //! iterator over the current group.
    //!
    LinkIterator    current_iterator_;

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4251)
#endif
    //!
    //! Pointer to the parent interator if there is one
    //!
    IteratorPointer parent_iterator_;
#ifdef _MSC_VER
#pragma warning(pop)
#endif



};

} // namespace node
} // namespace hdf5
