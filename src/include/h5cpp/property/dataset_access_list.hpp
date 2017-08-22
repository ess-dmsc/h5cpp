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
// Created on: Aug 22, 2017
//
#pragma once

#include "link_access_list.hpp"

namespace hdf5 {
namespace property {

class ChunkCacheParameters
{
  public:
    ChunkCacheParameters(size_t nslots,size_t nbytes,double preempt_policy) noexcept;
    ChunkCacheParameters() noexcept;
    ChunkCacheParameters(const ChunkCacheParameters&) = default;

    void chunk_slots(size_t nslots) noexcept;
    size_t chunk_slots() const noexcept;

    void chunk_cache_size(size_t size) noexcept;
    size_t chunk_cache_size() const noexcept;

    void preemption_policy(double value) noexcept;
    double preemption_policy() const noexcept;
  private:
    size_t nslots_;
    size_t nbytes_;
    double w0_;
};
	
class DatasetAccessList : public LinkAccessList
{
  public:
    DatasetAccessList();
    ~DatasetAccessList();

    void chunk_cache_parameters(const ChunkCacheParameters &params) const;
    ChunkCacheParameters chunk_cache_parameters() const;


};
} // namespace property
} // namespace hdf5
