//
// (c) Copyright 2017 DESY,ESS
//
// This file is part of h5pp.
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
// Created on: Oct 09, 2017
//
#pragma once


#include "list.hpp"

namespace hdf5 {
namespace property {

enum class CopyFlag : unsigned {
  SHALLOW_HIERARCHY     = H5O_COPY_SHALLOW_HIERARCHY_FLAG,
  EXPAND_SOFT_LINKS     = H5O_COPY_EXPAND_SOFT_LINK_FLAG,
  EXPAND_EXTERNAL_LINKS = H5O_COPY_EXPAND_EXT_LINK_FLAG,
  EXPAND_REFERNCES      = H5O_COPY_EXPAND_REFERENCE_FLAG,
  WITHOUT_ATTRIBUTES    = H5O_COPY_WITHOUT_ATTR_FLAG,
  MERGE_COMMITTED_TYPES = H5O_COPY_MERGE_COMMITTED_DTYPE_FLAG
};

std::ostream &operator<<(std::ostream &stream,const CopyFlag &flag);

//!
//! \brief encapsulate copy flags
//!
//! This class encapsulates copy flags and provides easy access to
//! the flags without using logical operators.
//!
class CopyFlags
{
  private:
    unsigned value_;
  public:
    //!
    //! \brief default constructor
    //!
    //! Setup the flags with 0.
    //!
    CopyFlags() noexcept;

    //!
    //! \brief constructor
    //!
    //! Construct a CopyFlags instance from a raw unsigned value.
    //! \param flags raw flags value
    //!
    explicit CopyFlags(unsigned flags) noexcept;

    //!
    //! \brief copy constructor
    //!
    //! Use default implementation for this.
    //!
    CopyFlags(const CopyFlags &flags) = default;

    //!
    //! \brief logical or operator
    //!
    CopyFlags &operator|(const CopyFlag &flag);

    //!
    //! \brief logical or operator
    //!
    CopyFlags &operator|(const CopyFlags &flags);


    //!
    //! \brief if this flag is set
    bool shallow_hierarchy() const noexcept;
    void shallow_hierarchy(bool flag) noexcept;

    bool expand_soft_links() const noexcept;
    void expand_soft_links(bool flag) noexcept;

    bool expand_external_links() const noexcept;
    void expand_external_links(bool flag) noexcept;

    bool expand_references() const noexcept;
    void expand_references(bool flag) noexcept;

    bool without_attributes() const noexcept;
    void without_attributes(bool flag) noexcept;

    bool merge_committed_types() const noexcept;
    void merge_committed_types(bool flag) noexcept;

};





class DLL_EXPORT ObjectCopyList : public List
{
  public:
    ObjectCopyList();


};

} // namespace property
} // namespace hdf5
