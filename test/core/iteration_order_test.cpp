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
// Created on: Sep 11, 2017
//
#include <h5cpp/core/iterator_config.hpp>
#include <sstream>
#include <catch2/catch_all.hpp>

using namespace hdf5;

SCENARIO("Testing basic behavior of the IterationOrder enumeration ") {
  GIVEN("DECREASING") { 
    THEN("stream output is DECREASING") {
      std::stringstream stream;
      stream<<IterationOrder::Decreasing;
      REQUIRE(stream.str() == "DECREASING");
    }

    AND_THEN("the integer would be") { 
      REQUIRE(static_cast<H5_iter_order_t>(IterationOrder::Decreasing) ==
                    H5_ITER_DEC);
    }

  }

  GIVEN("INCREASING") { 
    THEN("stream outputis INCREASING") { 
      std::stringstream stream;
      stream<<IterationOrder::Increasing;
      REQUIRE(stream.str() == "INCREASING");
    }

    AND_THEN("the integer is H5_ITER_DEC") { 
      REQUIRE(static_cast<H5_iter_order_t>(IterationOrder::Increasing) ==
                    H5_ITER_INC);
    }
  }

  GIVEN("NATIVE") { 
    THEN("stream output is NATIVE") { 
      std::stringstream stream;    
      stream<<IterationOrder::Native;
      REQUIRE(stream.str() ==  "NATIVE");
    }

    AND_THEN("the integer is H5_ITER_NATIVE") { 

      REQUIRE(static_cast<H5_iter_order_t>(IterationOrder::Native) == 
                    H5_ITER_NATIVE);
    }
  }
}
