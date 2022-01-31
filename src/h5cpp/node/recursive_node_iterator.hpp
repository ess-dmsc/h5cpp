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
//! Group top = ...;
//! auto iter = RecursiveNodeIterator::begin(top);
//! auto end  = RecursiveNodeIterator::end(top);
//!
//! while(iter != end)
//! {
//!   //do something here
//!   ++iter;
//! }
//! // or with STL
//!
//! std::for_each(RecursiveNodeIterator::begin(top),
//!               RecursiveNodeIterator::end(top),
//!               [](const Node &node) { ...do something ... ; });
//! \endcode
//!
//! Unlike NodeIterator, RecursiveNodeIterator is a simple forward iterator.
//!
//!
class DLL_EXPORT RecursiveNodeIterator
{
  public:
    using value_type = Node;
    using pointer = value_type*;
    using reference = value_type&;
    using difference_type = ssize_t;
    using iterator_category = std::forward_iterator_tag;

    //!
    //! \brief default constructor
    //!
    //! There is no default constructors -> would not make too much sense.
    //!
    RecursiveNodeIterator() = delete;

    //!
    //! \brief create iterator to the first element
    //!
    //! Static factory function returning an instance of
    //! RecursiveForwardIterator on the first element of the top group.
    //!
    //! \param current_group the top level group where to start with
    //!                      recursive iteration
    //! \return instance of RecursiveNodeIterator
    //!
    static RecursiveNodeIterator begin(const Group &current_group);

    //!
    //! \brief create iterator to the last+1 element
    //!
    //! Static factory function returning an instance of
    //! RecursiveForwardIterator on the last+1 element of top group.
    //!
    //! \param current_group the top level group at which to start the
    //!                      recursive iteration.
    //! \return instance of RecursiveNodeIterator
    //!
    static RecursiveNodeIterator end(const Group &current_group);

    //!
    //! \brief return current Node instance
    //!
    //! Returns an instance of the actual node the iterator refers to.
    //! \return instance of node::Node
    //!
    Node operator*() const;

    //!
    //! \brief return address of the actual Node instance
    //!
    //! Returns the adress of the actual node in memory.
    //! \return adress of current Node
    //!
    Node *operator->();

    //!
    //! \brief advance to next element
    //!
    //! Advances to the next element in line.
    //! \code
    //! RecursiveNodeIterator iter = ...;
    //! while(...)
    //! {
    //!   ++iter;
    //! }
    //! \endcode
    //!
    //! \return reference to the udpated iterator
    //!
    RecursiveNodeIterator &operator++();

    //!
    //! \brief advance to next element
    //!
    //! Advances to the next element in line but returns an iterator to the
    //! previous element.
    //!
    //! \code
    //! RecursiveNodeIterator iter = ...;
    //!
    //! while(...)
    //! {
    //!   Node n = *iter++; //give me the actual node and advance
    //!   std::cout<<n.link().path()<<std::endl;
    //! }
    //! \endcode
    //!
    //! \return instance of RecursiveNodeIterator
    //!
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
