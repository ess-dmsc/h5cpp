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
// Author: Eugen Wintersberger <eugen.wintersberger@gmail.com>
// Created on: Sep 11, 2017
//

#include <catch2/catch.hpp>
#include <h5cpp/hdf5.hpp>

using namespace hdf5;

SCENARIO("testing LinkType stream io an integer conversion") { 
  using node::LinkType;
  using r = std::tuple<LinkType,std::string,H5L_type_t>;
  auto d = GENERATE(table<LinkType,std::string,H5L_type_t>({
    r{LinkType::Error, "ERROR", H5L_TYPE_ERROR},
    r{LinkType::External, "EXTERNAL", H5L_TYPE_EXTERNAL},
    r{LinkType::Hard, "HARD", H5L_TYPE_HARD},
    r{LinkType::Soft, "SOFT", H5L_TYPE_SOFT}
  }));
  std::stringstream ss;
  WHEN("writing to stream") { 
    ss<<std::get<0>(d);
    THEN("we get") { REQUIRE(ss.str() == std::get<1>(d));}
  }
  WHEN("converting to integer we get") { 
    REQUIRE(static_cast<H5L_type_t>(std::get<0>(d)) == std::get<2>(d));
  }
}
