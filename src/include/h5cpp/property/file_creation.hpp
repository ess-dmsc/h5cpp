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
// Created on: Aug 18, 2017
//
#pragma once


#include <h5cpp/property/group_creation.hpp>
#include <h5cpp/windows.hpp>

namespace hdf5 {
namespace property {

class DLL_EXPORT FileCreationList : public GroupCreationList
{
  public:
    FileCreationList();
    ~FileCreationList();

    void userblock(hsize_t size) const;
    hsize_t userblock() const;

    void object_offset_size(size_t size) const;
    size_t object_offset_size() const;

    void object_length_size(size_t size) const;
    size_t object_length_size() const;

    void btree_rank(unsigned ik);
    unsigned btree_rank() const;

    void btree_symbols(unsigned lk);
    unsigned btree_symbols() const;

    // istore_k
    void chunk_rank(unsigned ik);
    unsigned chunk_rank() const;

    // file_space_page_size
    void page_size(hsize_t size);
    hsize_t page_size() const;

//        H5Pset_file_space_strategy
//    H5Pget_file_space_strategy
//
//        H5Pset_shared_mesg_nindexes
//    H5Pget_shared_mesg_nindexes
//
//        H5Pset_shared_mesg_index
//    H5Pget_shared_mesg_index
//
//        H5Pset_shared_mesg_phase_change
//    H5Pget_shared_mesg_phase_change
};

} // namespace property
} // namespace hdf5
