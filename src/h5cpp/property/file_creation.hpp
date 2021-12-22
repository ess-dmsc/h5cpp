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
// Authors:
//   Eugen Wintersberger <eugen.wintersberger@desy.de>
//   Martin Shetty <martin.shetty@esss.se>
// Created on: Aug 18, 2017
//
#pragma once

#include <h5cpp/property/group_creation.hpp>
#include <h5cpp/core/windows.hpp>

namespace hdf5 {
namespace property {

//!
//! \brief dataset creation property list
//!
class DLL_EXPORT FileCreationList : public GroupCreationList {
 public:
  //!
  //! \brief default constructor
  //!
  FileCreationList();
  ~FileCreationList() override;

  //!
  //! \brief constructor
  //!
  //! Construct a file creation property list from a handler instance.
  //! This constructor will throw an exception if the handle does not
  //! reference a file creation property list.
  //!
  //! \throws std::runtime_error in case of a failure
  //! \param handle r-value reference to a handle instance
  //!
  explicit FileCreationList(ObjectHandle &&handle);

  //!
  //! \brief set user block
  //!
  void user_block(hsize_t size) const;
  //!
  //! \brief get user block
  //!
  hsize_t user_block() const;

  //!
  //! \brief set object offset size
  //!
  void object_offset_size(size_t size) const;
  //!
  //! \brief get object offset size
  //!
  size_t object_offset_size() const;

  //!
  //! \brief set object length size
  //!
  void object_length_size(size_t size) const;
  //!
  //! \brief get object length size
  //!
  size_t object_length_size() const;

  //!
  //! \brief set btree rank
  //!
  void btree_rank(unsigned int ik);
  //!
  //! \brief get btree rank
  //!
  unsigned int btree_rank() const;

  //!
  //! \brief set btree symbols
  //!
  void btree_symbols(unsigned int lk);
  //!
  //! \brief get btree symbols
  //!
  unsigned int btree_symbols() const;
  //!
  //! \brief set chunk tree rank
  //!
  void chunk_tree_rank(unsigned int ik);
  //!
  //! \brief get chunk tree rank
  //!
  unsigned int chunk_tree_rank() const;

#if (defined(_DOXYGEN_) || H5_VERSION_GE(1,10,1))
  //!
  //! \brief set page size (*since hdf5 1.10.1*)
  //!
  void page_size(hsize_t size);
  //!
  //!  \brief get page size (*since hdf5 1.10.1*)
  //!
  hsize_t page_size() const;
#endif

// The following still need wrapping
//    H5Pset_file_space_strategy
//    H5Pget_file_space_strategy
//
//    H5Pset_shared_mesg_nindexes
//    H5Pget_shared_mesg_nindexes
//
//    H5Pset_shared_mesg_index
//    H5Pget_shared_mesg_index
//
//    H5Pset_shared_mesg_phase_change
//    H5Pget_shared_mesg_phase_change

// DO NOT WRAP the following:
//    H5Pget_version -- deprecated in favor of H5Fget_info

};

} // namespace property
} // namespace hdf5
