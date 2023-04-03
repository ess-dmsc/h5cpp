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
#include <catch2/catch_all.hpp>
#include <sstream>

using namespace hdf5;

static file::SearchFlagsBase cast(file::SearchFlags flags) {
  return static_cast<file::SearchFlagsBase>(flags);
}

SCENARIO("Basic search flags operations", "[h5cpp,file]") {
  std::stringstream stream;

  GIVEN("SearchFlags::All") {
    WHEN("written to output stream") {
      stream << file::SearchFlags::All;
      REQUIRE(stream.str() == "ALL");
    }
    WHEN("converted to integer") {
      REQUIRE(cast(file::SearchFlags::All) == H5F_OBJ_ALL);
    }
  }

  GIVEN("SearchFlags::Attribute") {
    WHEN("written to output stream") {
      stream << file::SearchFlags::Attribute;
      REQUIRE(stream.str() == "ATTRIBUTE");
    }
    WHEN("SearchFlags::Attribute") {
      REQUIRE(cast(file::SearchFlags::Attribute) == H5F_OBJ_ATTR);
    }
  }

  GIVEN("SearchFlags::Dataset") {
    WHEN("written to output stream") {
      stream << file::SearchFlags::Dataset;
      REQUIRE(stream.str() == "DATASET");
    }
    WHEN("SearchFlags::Dataset") {
      REQUIRE(cast(file::SearchFlags::Dataset) == H5F_OBJ_DATASET);
    }
  }

  GIVEN("SearchFalgs::Datatype") {
    WHEN("written to toutput stream") {
      stream << file::SearchFlags::Datatype;
      REQUIRE(stream.str() == "DATATYPE");
    }
    WHEN("SearchFlags::Datatype") {
      REQUIRE(cast(file::SearchFlags::Datatype) == H5F_OBJ_DATATYPE);
    }
  }

  GIVEN("SearchFlags::File") {
    WHEN("written to output stream") {
      stream << file::SearchFlags::File;
      REQUIRE(stream.str() == "FILE");
    }
    WHEN("SearchFlags::File") {
      REQUIRE(cast(file::SearchFlags::File) == H5F_OBJ_FILE);
    }
  }

  GIVEN("SearchFlags::Group") {
    WHEN("written to output stream") {
      stream << file::SearchFlags::Group;
      REQUIRE(stream.str() == "GROUP");
    }
    WHEN("SearchFlags::Group") {
      REQUIRE(cast(file::SearchFlags::Group) == H5F_OBJ_GROUP);
    }
  }

  GIVEN("SearchFlags::Local") {
    WHEN("written to output stream") {
      stream << file::SearchFlags::Local;
      REQUIRE(stream.str() == "LOCAL");
    }
    WHEN("SearchFlags::Local") {
      REQUIRE(cast(file::SearchFlags::Local) == H5F_OBJ_LOCAL);
    }
  }
}

TEST_CASE("search flags ||", "[h5cpp,file]") {
  SECTION("ATTRIBUTE and DATASET") {
    REQUIRE((file::SearchFlags::Attribute |
            file::SearchFlags::Dataset) == (H5F_OBJ_ATTR | H5F_OBJ_DATASET));
  }

  SECTION("ATTRIBUTE, DATASET and DATATYPE") {
    REQUIRE((file::SearchFlags::Attribute | file::SearchFlags::Dataset |
            file::SearchFlags::Datatype) == (H5F_OBJ_ATTR | H5F_OBJ_DATASET |
            H5F_OBJ_DATATYPE));
  }
SECTION("test AND and OR operators")
{
  using file::SearchFlags;
  using file::SearchFlagsBase;
  REQUIRE(static_cast<SearchFlagsBase>((file::SearchFlags::Datatype | file::SearchFlags::Dataset) &
            file::SearchFlags::Datatype) == H5F_OBJ_DATATYPE);
  REQUIRE(static_cast<SearchFlagsBase>(file::SearchFlags::Attribute &
	    (file::SearchFlags::Attribute | file::SearchFlags::Dataset)) ==
            H5F_OBJ_ATTR);
  REQUIRE(static_cast<SearchFlagsBase>((file::SearchFlags::Datatype | file::SearchFlags::Dataset) &
	    (file::SearchFlags::Attribute | file::SearchFlags::Dataset)) ==
            H5F_OBJ_DATASET);
}

SECTION("test values")
{
  REQUIRE(static_cast<file::SearchFlagsBase>(file::SearchFlags::All) ==
            H5F_OBJ_ALL);
  REQUIRE(static_cast<file::SearchFlagsBase>(file::SearchFlags::Attribute) ==
            H5F_OBJ_ATTR);
  REQUIRE(static_cast<file::SearchFlagsBase>(file::SearchFlags::Dataset) ==
            H5F_OBJ_DATASET);
  REQUIRE(static_cast<file::SearchFlagsBase>(file::SearchFlags::Datatype) ==
            H5F_OBJ_DATATYPE);
  REQUIRE(static_cast<file::SearchFlagsBase>(file::SearchFlags::File) ==
            H5F_OBJ_FILE);
  REQUIRE(static_cast<file::SearchFlagsBase>(file::SearchFlags::Group) ==
            H5F_OBJ_GROUP);
  REQUIRE(static_cast<file::SearchFlagsBase>(file::SearchFlags::Local) ==
            H5F_OBJ_LOCAL);
}
}

