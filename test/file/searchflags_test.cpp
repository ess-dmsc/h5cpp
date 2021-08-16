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
// Authors:
//   Eugen Wintersberger <eugen.wintersberger@desy.de>
//   Jan Kotanski <jan.kotanski@desy.de>
// Created on: Sep 8, 2017
//
#include <h5cpp/file/types.hpp>
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <sstream>

using namespace hdf5;

file::SearchFlagsBase cast(file::SearchFlags flags) {
  return static_cast<file::SearchFlagsBase>(flags);
}

SCENARIO("Basic search flags operations", "[h5cpp,file]") {
  std::stringstream stream;

  GIVEN("SearchFlags::ALL") {
    WHEN("written to output stream") {
      stream << file::SearchFlags::ALL;
      REQUIRE(stream.str() == "ALL");
    }
    WHEN("converted to integer") {
      REQUIRE(cast(file::SearchFlags::ALL) == H5F_OBJ_ALL);
    }
  }

  GIVEN("SearchFlags::ATTRIBUTE") {
    WHEN("written to output stream") {
      stream << file::SearchFlags::ATTRIBUTE;
      REQUIRE(stream.str() == "ATTRIBUTE");
    }
    WHEN("SearchFlags::ATTRIBUTE") {
      REQUIRE(cast(file::SearchFlags::ATTRIBUTE) == H5F_OBJ_ATTR);
    }
  }

  GIVEN("SearchFlags::DATASET") {
    WHEN("written to output stream") {
      stream << file::SearchFlags::DATASET;
      REQUIRE(stream.str() == "DATASET");
    }
    WHEN("SearchFlags::DATASET") {
      REQUIRE(cast(file::SearchFlags::DATASET) == H5F_OBJ_DATASET);
    }
  }

  GIVEN("SearchFalgs::DATATYPE") {
    WHEN("written to toutput stream") {
      stream << file::SearchFlags::DATATYPE;
      REQUIRE(stream.str() == "DATATYPE");
    }
    WHEN("SearchFlags::DATATYPE") {
      REQUIRE(cast(file::SearchFlags::DATATYPE) == H5F_OBJ_DATATYPE);
    }
  }

  GIVEN("SearchFlags::FILE") {
    WHEN("written to output stream") {
      stream << file::SearchFlags::FILE;
      REQUIRE(stream.str() == "FILE");
    }
    WHEN("SearchFlags::FILE") {
      REQUIRE(cast(file::SearchFlags::FILE) == H5F_OBJ_FILE);
    }
  }

  GIVEN("SearchFlags::GROUP") {
    WHEN("written to output stream") {
      stream << file::SearchFlags::GROUP;
      REQUIRE(stream.str() == "GROUP");
    }
    WHEN("SearchFlags::GROUP") {
      REQUIRE(cast(file::SearchFlags::GROUP) == H5F_OBJ_GROUP);
    }
  }

  GIVEN("SearchFlags::LOCAL") {
    WHEN("written to output stream") {
      stream << file::SearchFlags::LOCAL;
      REQUIRE(stream.str() == "LOCAL");
    }
    WHEN("SearchFlags::LOCAL") {
      REQUIRE(cast(file::SearchFlags::LOCAL) == H5F_OBJ_LOCAL);
    }
  }
}

TEST_CASE("search flags ||", "[h5cpp,file]") {
  SECTION("ATTRIBUTE and DATASET") {
    REQUIRE((file::SearchFlags::ATTRIBUTE |
            file::SearchFlags::DATASET) == (H5F_OBJ_ATTR | H5F_OBJ_DATASET));
  }

  SECTION("ATTRIBUTE, DATASET and DATATYPE") {
    REQUIRE((file::SearchFlags::ATTRIBUTE | file::SearchFlags::DATASET |
            file::SearchFlags::DATATYPE) == (H5F_OBJ_ATTR | H5F_OBJ_DATASET |
            H5F_OBJ_DATATYPE));
  }
SECTION("test AND and OR operators")
{
  using file::SearchFlags;
  using file::SearchFlagsBase;
  REQUIRE(static_cast<SearchFlagsBase>((file::SearchFlags::DATATYPE | file::SearchFlags::DATASET) &
            file::SearchFlags::DATATYPE) == H5F_OBJ_DATATYPE);
  REQUIRE(static_cast<SearchFlagsBase>(file::SearchFlags::ATTRIBUTE &
	    (file::SearchFlags::ATTRIBUTE | file::SearchFlags::DATASET)) ==
            H5F_OBJ_ATTR);
  REQUIRE(static_cast<SearchFlagsBase>((file::SearchFlags::DATATYPE | file::SearchFlags::DATASET) &
	    (file::SearchFlags::ATTRIBUTE | file::SearchFlags::DATASET)) ==
            H5F_OBJ_DATASET);
}

SECTION("test values")
{
  REQUIRE(static_cast<file::SearchFlagsBase>(file::SearchFlags::ALL) ==
            H5F_OBJ_ALL);
  REQUIRE(static_cast<file::SearchFlagsBase>(file::SearchFlags::ATTRIBUTE) ==
            H5F_OBJ_ATTR);
  REQUIRE(static_cast<file::SearchFlagsBase>(file::SearchFlags::DATASET) ==
            H5F_OBJ_DATASET);
  REQUIRE(static_cast<file::SearchFlagsBase>(file::SearchFlags::DATATYPE) ==
            H5F_OBJ_DATATYPE);
  REQUIRE(static_cast<file::SearchFlagsBase>(file::SearchFlags::FILE) ==
            H5F_OBJ_FILE);
  REQUIRE(static_cast<file::SearchFlagsBase>(file::SearchFlags::GROUP) ==
            H5F_OBJ_GROUP);
  REQUIRE(static_cast<file::SearchFlagsBase>(file::SearchFlags::LOCAL) ==
            H5F_OBJ_LOCAL);
}
}

