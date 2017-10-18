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
// Created on: Aug 22, 2017
//

#include <gtest/gtest.h>
#include <boost/test/floating_point_comparison.hpp>
#include <h5cpp/property/dataset_access_list.hpp>
#include <h5cpp/property/class.hpp>

namespace pl = hdf5::property;

TEST(DatasetAccessList, test_default_construction)
{
  pl::DatasetAccessList dapl;
  EXPECT_TRUE(dapl.get_class()==pl::kDatasetAccess);
}

TEST(DatasetAccessList, test_chunk_cache_parameters)
{
  pl::DatasetAccessList dapl;
  pl::ChunkCacheParameters params(200,300*1024*1024,0.5);
  EXPECT_NO_THROW(dapl.chunk_cache_parameters(params));
  pl::ChunkCacheParameters p2 = dapl.chunk_cache_parameters();
  EXPECT_EQ(p2.chunk_slots(),200);
  EXPECT_EQ(p2.chunk_cache_size(),300*1024*1024);
  EXPECT_NEAR(p2.preemption_policy(),0.5,0.0001);
}



