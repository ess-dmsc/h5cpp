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
// Created on: Aug 22, 2017
//

#include <gtest/gtest.h>
#include <h5cpp/property/dataset_access.hpp>
#include <h5cpp/property/property_class.hpp>

namespace pl = hdf5::property;

TEST(ChunkCacheParameters, default_construction) {
  pl::ChunkCacheParameters params;

  EXPECT_EQ(params.chunk_slots(), 0ul);
  EXPECT_EQ(params.chunk_cache_size(), 0ul);
  EXPECT_NEAR(params.preemption_policy(), 0.0, 0.0001);
}

TEST(ChunkCacheParameters, test_construction) {
  pl::ChunkCacheParameters params(100, 200, 0.2);
  EXPECT_EQ(params.chunk_slots(), 100ul);
  EXPECT_EQ(params.chunk_cache_size(), 200ul);
  EXPECT_NEAR(params.preemption_policy(), 0.2, 0.0001);
}

TEST(ChunkCacheParameters, test_copy_construction) {
  pl::ChunkCacheParameters params1(100, 200, 0.2);
  pl::ChunkCacheParameters params2(params1);
  EXPECT_EQ(params2.chunk_slots(), 100ul);
  EXPECT_EQ(params2.chunk_cache_size(), 200ul);
  EXPECT_NEAR(params2.preemption_policy(), 0.2, 0.0001);
}

TEST(ChunkCacheParameters, test_chunk_slots) {
  pl::ChunkCacheParameters p;
  p.chunk_slots(20);
  EXPECT_EQ(p.chunk_slots(), 20ul);
}

TEST(ChunkCacheParameters, test_chunk_cache_size) {
  pl::ChunkCacheParameters p;
  p.chunk_cache_size(200);
  EXPECT_EQ(p.chunk_cache_size(), 200ul);
}

TEST(ChunkCacheParameters, test_preemption_policy) {
  pl::ChunkCacheParameters p;
  p.preemption_policy(0.2);
  EXPECT_NEAR(p.preemption_policy(), 0.2, 0.0001);
}


