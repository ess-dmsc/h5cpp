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
// Authors:
//   Eugen Wintersberger <eugen.wintersberger@desy.de>
//   Martin Shetty <martin.shetty@esss.se>
//   Jan Kotanski <jan.kotanski@desy.de>
// Created on: Oct 09, 2017
//
#pragma once

#include <h5cpp/property/property_list.hpp>

namespace hdf5 {
namespace property {

class CopyFlags;

enum class CopyFlag : unsigned {
  ShallowHierarchy = H5O_COPY_SHALLOW_HIERARCHY_FLAG,
  ExpandSoftLinks = H5O_COPY_EXPAND_SOFT_LINK_FLAG,
  ExpandExternalLinks = H5O_COPY_EXPAND_EXT_LINK_FLAG,
  ExpandReferences = H5O_COPY_EXPAND_REFERENCE_FLAG,
  WithoutAttributes = H5O_COPY_WITHOUT_ATTR_FLAG,
  MergeCommittedTypes = H5O_COPY_MERGE_COMMITTED_DTYPE_FLAG
};

DLL_EXPORT std::ostream &operator<<(std::ostream &stream, const CopyFlag &flag);

DLL_EXPORT CopyFlags operator|(const CopyFlag &lhs, const CopyFlag &rhs);

DLL_EXPORT CopyFlags operator&(const CopyFlag &lhs, const CopyFlag &rhs);

//!
//! \brief encapsulate copy flags
//!
//! This class encapsulates copy flags and provides easy access to
//! the flags without using logical operators.
//!
class DLL_EXPORT CopyFlags {
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
  //! \brief unary logical or operator
  //!
  CopyFlags &operator|=(const CopyFlag &flag) noexcept;

  //!
  //! \brief unary logical or operator
  //!
  CopyFlags &operator|=(const CopyFlags &flags) noexcept;

  //!
  //! \brief unary logical and operator
  //!
  CopyFlags &operator&=(const CopyFlag &flag) noexcept;

  //!
  //! \brief unary logical and operator
  //!
  CopyFlags &operator&=(const CopyFlags &flags) noexcept;

  //!
  //! \brief allow for explicit conversion to unsigned
  //!
  explicit operator unsigned() const noexcept {
    return value_;
  }

  //!
  //! \brief get state of the shallow hierarchy flag
  //!
  bool shallow_hierarchy() const noexcept;

  //!
  //! \brief set the state of the shallo hierarchy flag
  //!
  void shallow_hierarchy(bool flag) noexcept;

  //!
  //! \brief get the state of the expand soft links flag
  //!
  bool expand_soft_links() const noexcept;

  //!
  //! \brief set the state of the expand soft links flag
  //!
  void expand_soft_links(bool flag) noexcept;

  //!
  //! \brief get the state of the expand external links flag
  //!
  bool expand_external_links() const noexcept;

  //!
  //! \brief set the state of the expand external links flag
  //!
  void expand_external_links(bool flag) noexcept;

  //!
  //! \brief get the state of the expand reference flag
  //!
  bool expand_references() const noexcept;

  //!
  //! \brief set the state of the expand reference flag
  //!
  void expand_references(bool flag) noexcept;

  //!
  //! \brief get the state of the without attribute flag
  //!
  bool without_attributes() const noexcept;

  //!
  //! \brief set the state of the without attribute flag
  //!
  void without_attributes(bool flag) noexcept;

  //!
  //! \brief get the state of the merge committed attribute flag
  //!
  bool merge_committed_types() const noexcept;

  //!
  //! \brief set the state of the merge comitted attribute flag
  //!
  void merge_committed_types(bool flag) noexcept;

};

//!
//! \brief binary or operator for copy flags
//!
DLL_EXPORT CopyFlags operator|(const CopyFlags &flags, const CopyFlags &rhs) noexcept;

//!
//! \brief binary or operator for copy flags
//!
DLL_EXPORT CopyFlags operator|(const CopyFlags &flags, const CopyFlag &flag) noexcept;

//!
//! \brief binary or operator for copy flags
//!
DLL_EXPORT CopyFlags operator|(const CopyFlag &flag, const CopyFlags &flags) noexcept;

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wweak-vtables"
#endif
//!
//! \brief binary and operator for copy flags
//!
DLL_EXPORT CopyFlags operator&(const CopyFlags &flags, const CopyFlags &rhs) noexcept;

//!
//! \brief binary and operator for copy flags
//!
DLL_EXPORT CopyFlags operator&(const CopyFlags &flags, const CopyFlag &flag) noexcept;

//!
//! \brief binary and operator for copy flags
//!
DLL_EXPORT CopyFlags operator&(const CopyFlag &flag, const CopyFlags &flags) noexcept;

class DLL_EXPORT ObjectCopyList : public List {
 public:
  ObjectCopyList();

  explicit ObjectCopyList(ObjectHandle &&handle);

  void flags(const CopyFlags &flags) const;
  void flags(const CopyFlag &flag) const;

  CopyFlags flags() const;

};
#ifdef __clang__
#pragma clang diagnostic pop
#endif

} // namespace property
} // namespace hdf5
