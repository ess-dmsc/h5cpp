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
// Created on: Sep 11, 2017
//
#include <h5cpp/core/iterator_config.hpp>
#include <sstream>
#include <catch2/catch.hpp>

using namespace hdf5;

SCENARIO("testing the iteration index") { 
  GIVEN("CREATION_ORDER") { 
    THEN("stream output is CREATION_ORDER") { 
      std::stringstream stream;
      stream<<IterationIndex::CreationOrder;
      REQUIRE(stream.str() == "CREATION_ORDER");
    }

    AND_THEN("integer would be") { 
      REQUIRE(static_cast<H5_index_t>(IterationIndex::CreationOrder) == H5_INDEX_CRT_ORDER);
    }
  }

  GIVEN("NAME") { 
    THEN("stream output would be NAME"){
      std::stringstream stream;
      stream<<IterationIndex::Name;
      REQUIRE(stream.str() == "NAME");
    } 

    AND_THEN("integer would be") { 
      REQUIRE(static_cast<H5_index_t>(IterationIndex::Name) == H5_INDEX_NAME);
    }

  }
}
