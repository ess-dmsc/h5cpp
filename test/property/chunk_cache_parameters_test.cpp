//
// (c) Copyright 2017 DESY,ESS
//               2020 Eugen Wintersberger <eugen.wintersberger@gmail.com>
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
//   Eugen Wintersberger <eugen.wintersberger@gmail.com>
//   Martin Shetty <martin.shetty@esss.se>
// Created on: Aug 22, 2017
//

#include <catch2/catch_all.hpp>
#include <h5cpp/property/dataset_access.hpp>
#include <h5cpp/property/property_class.hpp>
#include "../utilities.hpp"

namespace pl = hdf5::property;

SCENARIO("ChunkCacheParameters construction") {
  GIVEN("default constructed parameter") {
    pl::ChunkCacheParameters params;
    THEN("we get the following default configuration") {
      REQUIRE(params.chunk_slots() == 0ul);
      REQUIRE(params.chunk_cache_size() == 0ul);
      REQUIRE(params.preemption_policy() == 0.0);
    }
    AND_WHEN("we set the chunks slots to 20")  { 
      REQUIRE_NOTHROW(params.chunk_slots(20));
      THEN("we get for the chunk slots") { 
        REQUIRE(params.chunk_slots() == 20);
      }
    }
    AND_WHEN("we set the chunk cache size to 200") { 
      REQUIRE_NOTHROW(params.chunk_cache_size(200));
      THEN("we get for the chunk cache size") { 
        REQUIRE(params.chunk_cache_size() == 200);
      }
    }
    AND_WHEN("we set the preemption policy") { 
      REQUIRE_NOTHROW(params.preemption_policy(0.1));
      THEN("we get for the preemption policy") { 
        REQUIRE(params.preemption_policy() == Approx(0.1));
      }
    }
  }
  GIVEN("parameters") {
    size_t slots = 100;
    size_t cache_size = 200;
    double policy = 0.2;
    THEN("we can construct parameters") {
      pl::ChunkCacheParameters params(slots, cache_size, policy);
      AND_THEN("check their values") {
        REQUIRE(params.chunk_slots() == slots);
        REQUIRE(params.chunk_cache_size() == cache_size);
        REQUIRE(params.preemption_policy() == Approx(policy));
      }
      AND_WHEN("copy construct from this instance") { 
        pl::ChunkCacheParameters p2 = params;
        THEN("the new instance has the same configuration") { 
          REQUIRE(p2.chunk_slots() == params.chunk_slots());
          REQUIRE(p2.chunk_cache_size() == params.chunk_cache_size());
          REQUIRE(p2.preemption_policy() == Approx(params.preemption_policy()));
        }

      }
    }
  }
}
