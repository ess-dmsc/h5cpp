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
// Created on: Nov 17, 2017
//
#pragma once

#include <functional>
#include <h5cpp/node/group.hpp>
#include <h5cpp/node/node_iterator.hpp>
#include <h5cpp/core/windows.hpp>

namespace hdf5 {
namespace node {

//!
//! \brief recursive node iterator
//!
//! Iterator which recursively iterates over all subelements of a particular
//! group.
//! All relevant constructors are private. To construct an instance of
//! this iterator use the two static factory functions begin() and end().
//!
//! \code
//! auto iter = RecursiveNodeIterator::begin();
//! auto end  = RecursiveNodeIterator::end();
//!
//! while(iter != end)
//! {
//!   std::cout<<
//! }
//!
//!
class DLL_EXPORT RecursiveNodeIterator
{
  public:
    using value_type = Node;
    using pointer = value_type*;
    using reference = value_type&;
    using difference_type = ssize_t;
    using iterator_category = std::random_access_iterator_tag;

    //!
    //! \brief default constructor
    //!
    //! There is no default constructors -> would not make too much sense.
    //!
    RecursiveNodeIterator() = delete;

    //!
    //! \brief copy constructor
    //!
    //! Required, but we can use the compiler provided default version here.
    //!
    RecursiveNodeIterator(const RecursiveNodeIterator&) = default;



    static RecursiveNodeIterator begin(const Group &current_group);
    static RecursiveNodeIterator end(const Group &current_group);


    Node operator*() const;

    Node *operator->();

    RecursiveNodeIterator &operator++();
    RecursiveNodeIterator operator++(int);

    bool operator==(const RecursiveNodeIterator &rhs) const;

    bool operator!=(const RecursiveNodeIterator &rhs) const;

  private:
    RecursiveNodeIterator(const Group &current_group,
                          RecursiveNodeIterator parent_iterator);
    RecursiveNodeIterator(const Group &current_group);

    using IteratorPointer = std::shared_ptr<RecursiveNodeIterator>;

    //!
    //! references the current group we are in. We have to keep this
    //! as an object we are iterating upon must not be destroyed.
    //!
    Group           current_group_;

    //!
    //! iterator over the current group.
    //!
    NodeIterator    current_iterator_;

    //!
    //! Pointer to the parent interator if there is one
    //!
    IteratorPointer parent_iterator_;



};

} // namespace node
} // namespace hdf5
