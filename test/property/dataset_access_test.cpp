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

#include <catch2/catch.hpp>
#include <h5cpp/hdf5.hpp>
#include <h5cpp/property/dataset_access.hpp>
#include <h5cpp/property/property_class.hpp>
#include "../utilities.hpp"
#include "utilities.hpp"

namespace pl = hdf5::property;

SCENARIO("instantiating a DatasetAccessList") {
  GIVEN("a default constructed instance") {
    pl::DatasetAccessList dapl;
    THEN("we ge the following configuration") {
      REQUIRE(dapl.get_class() == pl::kDatasetAccess);
    }
    WHEN("we close the instance") {
      close(dapl);
      THEN("calling any method on the class will fail") {
        REQUIRE_THROWS_AS(
            dapl.chunk_cache_parameters(pl::ChunkCacheParameters()),
            std::runtime_error);
        REQUIRE_THROWS_AS(dapl.chunk_cache_parameters(), std::runtime_error);
#if H5_VERSION_GE(1, 10, 0)
        REQUIRE_THROWS_AS(dapl.virtual_view(), std::runtime_error);
        REQUIRE_THROWS_AS(dapl.virtual_view(pl::VirtualDataView::FIRST_MISSING),
                          std::runtime_error);
#endif
      }
    }
  }
  GIVEN("a handle to a dataset access property list") {
    auto handle = handle_from_class(pl::kDatasetAccess);
    THEN("we can construct an instance from it") {
      REQUIRE_NOTHROW(pl::DatasetAccessList{std::move(handle)});
    }
  }
  GIVEN("a handle to a group access property list") {
    auto handle = handle_from_class(pl::kGroupAccess);
    THEN("then any attempt to construct an instance will fail") {
      REQUIRE_THROWS_AS(pl::DatasetAccessList{std::move(handle)},
                        std::runtime_error);
    }
  }
}

#if H5_VERSION_GE(1, 10, 0)
SCENARIO("writing VirtualDataView to a stream") {
  using r = std::tuple<pl::VirtualDataView, std::string>;
  auto p = GENERATE(table<pl::VirtualDataView, std::string>(
      {r{pl::VirtualDataView::FIRST_MISSING, "FIRST_MISSING"},
       r{pl::VirtualDataView::LAST_AVAILABLE, "LAST_AVAILABLE"}}));
  GIVEN("an output stream") {
    std::stringstream stream;
    WHEN("writing the value to the stream") {
      stream << std::get<0>(p);
      THEN("we get as output") { REQUIRE(stream.str() == std::get<1>(p)); }
    }
  }
}
#endif

SCENARIO("setting the chunk cache paranmeters on a DatasetAccessList") {
  pl::DatasetAccessList dapl;
  GIVEN("given a set of chunks cache parameters") {
    pl::ChunkCacheParameters params(200, 300 * 1024 * 1024, 0.5);
    WHEN("we set these parameters") {
      REQUIRE_NOTHROW(dapl.chunk_cache_parameters(params));
      AND_WHEN("we read these parameters back") {
        auto p2 = dapl.chunk_cache_parameters();
        AND_THEN("they should match the original parameters") {
          REQUIRE(p2.chunk_slots() == params.chunk_slots());
          REQUIRE(p2.chunk_cache_size() == params.chunk_cache_size());
          REQUIRE(p2.preemption_policy() == Approx(params.preemption_policy()));
        }
      }
    }
  }
}

#if H5_VERSION_GE(1, 10, 0)
SCENARIO("setting the virtual data view on a DatasetAccessList") {
  pl::DatasetAccessList dapl;
  GIVEN("the different view values") {
    auto view = GENERATE(pl::VirtualDataView::FIRST_MISSING,
                         pl::VirtualDataView::LAST_AVAILABLE);
    WHEN("we set the view") {
      dapl.virtual_view(view);
      THEN("reading it back must yield the same result") {
        REQUIRE(dapl.virtual_view() == view);
      }
    }
  }
}
#endif
