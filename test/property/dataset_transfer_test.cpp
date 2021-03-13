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
// Created on: Aug 28, 2017
//

#include <catch2/catch.hpp>
#include <h5cpp/property/dataset_transfer.hpp>
#include <h5cpp/property/property_class.hpp>
#include <sstream>
#include "../utilities.hpp"
#include "utilities.hpp"

namespace pl = hdf5::property;


SCENARIO("DatasetTransferList creation") {
  GIVEN("a default constructed list") {
    pl::DatasetTransferList dtpl;
    THEN("we get") { REQUIRE(dtpl.get_class() == pl::kDatasetXfer); }
  }
  GIVEN("a handle to a dataset transfer property list") {
    auto handle = handle_from_class(pl::kDatasetXfer);
    THEN("we can construct a new instance from this") { 
      REQUIRE_NOTHROW(pl::DatasetTransferList{std::move(handle)});
    }
  }
  GIVEN("a handle to a group creation property list") { 
    auto handle = handle_from_class(pl::kGroupCreate);
    THEN("instantiation must fail") { 
      REQUIRE_THROWS_AS(pl::DatasetTransferList{std::move(handle)}, std::runtime_error);
    }
  }
}

#ifdef WITH_MPI

SCENARIO("writing MPITransferMode to a stream") { 
  using r = std::tuple<pl::MPITransferMode,std::string>;
  auto p = GENERATE(table<pl::MPITransferMode,std::string>({
    r{pl::MPITransferMode::INDEPENDENT, "INDEPENDENT"},
    r{pl::MPITransferMode::COLLECTIVE, "COLLECTIVE"}
  }));
  GIVEN("a stream") { 
    std::stringstream stream;
    WHEN("writing to the stream") { 
      stream<<std::get<0>(p);
      THEN("we get") { REQUIRE(stream.str() == std::get<1>(p));}
    }
  }
}

/*
TEST(DatasetTransferList, transfer_mode) {
  pl::DatasetTransferList dtpl;
  dtpl.mpi_transfer_mode(pl::MPITransferMode::INDEPENDENT);
  EXPECT_EQ(dtpl.mpi_transfer_mode(), pl::MPITransferMode::INDEPENDENT);

  dtpl.mpi_transfer_mode(pl::MPITransferMode::COLLECTIVE);
  EXPECT_EQ(dtpl.mpi_transfer_mode(), pl::MPITransferMode::COLLECTIVE);

  hdf5::ObjectHandle(static_cast<hid_t>(dtpl)).close();
  EXPECT_THROW(dtpl.mpi_transfer_mode(pl::MPITransferMode::COLLECTIVE),
               std::runtime_error);
  EXPECT_THROW(dtpl.mpi_transfer_mode(), std::runtime_error);
}

TEST(DatasetTransferList, chunk_option) {
  pl::DatasetTransferList dtpl;
  dtpl.mpi_chunk_option(pl::MPIChunkOption::ONE_LINK_CHUNKED);
  dtpl.mpi_chunk_option(pl::MPIChunkOption::MULTI_CHUNK);

  EXPECT_THROW(dtpl.mpi_chunk_option(), std::runtime_error);
  hdf5::ObjectHandle(static_cast<hid_t>(dtpl)).close();
  EXPECT_THROW(dtpl.mpi_chunk_option(pl::MPIChunkOption::MULTI_CHUNK),
               std::runtime_error);
}*/

#endif
