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
#include <h5cpp/node/group.hpp>
#include <h5cpp/node/node.hpp>
#include <h5cpp/core/windows.hpp>

namespace hdf5 {
namespace node {

//!
//! \brief bidirectional NodeIterator
//!
//! This iterator iterates over the direct children (nodes) of a group.
//! It is a full random access iterator using the index access methods
//! provided by the NodeView interface.
//!
//! The interface follows the C++ specification for bidirectional
//! constant iterators. See
//! <a href="http://en.cppreference.com/w/cpp/concept/BidirectionalIterator">
//! C++ reference on iterators</a> for details.
//!
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wweak-vtables"
#endif
class DLL_EXPORT NodeIterator : public Iterator
{
  public:
    using value_type = Node;
    using pointer = value_type*;
    using reference = value_type&;
    using difference_type = ssize_t;
    using iterator_category = std::bidirectional_iterator_tag;

    //!
    //! \brief default constructor
    //!
    //! Not requried, thus deleted.
    //!
    NodeIterator() = delete;

    //!
    //! \brief get iterator to first element
    //!
    //! Static factory function returning an iterator to the first child
    //! of a group.
    //!
    //! \param group reference to the group over which to iterate
    //! \return instance of NodeIterator
    //!
    static NodeIterator begin(const Group &group);

    //!
    //! \brief get iterator to last+1 element
    //!
    //! Static factory function returning an iterator to the last+1 child
    //! of the given group.
    //!
    //! \param group reference to the group over which to iterate
    //! \return instance of NodeIterator
    //!
    static NodeIterator end(const Group &group);


    Node operator*() const;
    Node *operator->();
    NodeIterator &operator++();
    NodeIterator operator++(int);
    NodeIterator &operator--();
    NodeIterator operator--(int);

    bool operator==(const NodeIterator &a) const;
    bool operator!=(const NodeIterator &a) const;

  private:
    //!
    //! \brief constructor
    //!
    NodeIterator(const Group &group,ssize_t index);
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4251)
#endif
    Group group_;
#ifdef _MSC_VER
#pragma warning(pop)
#endif
    //!
    //! stores the current node instance. The only reason we have this
    //! member is to be able to return an adress to the current object.
    //! This would not be possible as there is no such thing as an
    //! adress to an HDF5 object in memory.
    //!
    mutable Node current_node_;

};
#ifdef __clang__
#pragma clang diagnostic pop
#endif

} // namespace node
} // namespace hdf5
