
//
// (c) Copyright 2017 DESY,ESS
//               2020 Eugen Wintersberger <eugen.wintersberger@gmail.com>
//
// This file is part of h5pp.
//
// h5cpp is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// h5cpp is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  ee the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with h5cpp.  If not, see <http://www.gnu.org/licenses/>.
// ===========================================================================
//
// Authors:
//   Eugen Wintersberger <eugen.wintersberger@gmail.com>
//   Martin Shetty <martin.shetty@esss.se>
// Created on: Aug 16, 2017
//
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <h5cpp/property/property_class.hpp>
#include <tuple>

namespace pl = hdf5::property;

SCENARIO("Property list class construction") {
  GIVEN("the handle to a H5P_ATTRIBUTE_ACCESS") {
    auto handle = hdf5::ObjectHandle(H5P_ATTRIBUTE_ACCESS);
    THEN("construction of the property list class will suceed") {
      pl::Class c(std::move(handle));
      REQUIRE(c.name() == "attribute access");
    }
  }

  GIVEN("a handle to a simple dataspace") {
    auto handle = hdf5::ObjectHandle(H5Screate(H5S_SIMPLE));
    THEN("creation of the property list class will fail") {
      REQUIRE_THROWS_AS(pl::Class(std::move(handle)), std::runtime_error);
    }
  }
  WHEN("provided with the handle to a simple dataspace") {}
}

TEST_CASE("Testing the property class constants", "[hdf5],[property lists]") {
  SECTION("testing class names") {
    REQUIRE(pl::kAttributeCreate.name() == "attribute create");
    REQUIRE(pl::kDatasetAccess.name() == "dataset access");
    REQUIRE(pl::kDatasetCreate.name() == "dataset create");
    REQUIRE(pl::kDatasetXfer.name() == "data transfer");
    REQUIRE(pl::kDatatypeAccess.name() == "datatype access");
    REQUIRE(pl::kDatatypeCreate.name() == "datatype create");
    REQUIRE(pl::kFileAccess.name() == "file access");
    REQUIRE(pl::kFileCreate.name() == "file create");
    REQUIRE(pl::kFileMount.name() == "file mount");
    REQUIRE(pl::kGroupAccess.name() == "group access");
    REQUIRE(pl::kGroupCreate.name() == "group create");
    REQUIRE(pl::kLinkAccess.name() == "link access");
    REQUIRE(pl::kLinkCreate.name() == "link create");
    REQUIRE(pl::kObjectCopy.name() == "object copy");
    REQUIRE(pl::kObjectCreate.name() == "object create");
    REQUIRE(pl::kStringCreate.name() == "string create");
  }
}

SCENARIO("writing the property list class to a stream") {
  std::stringstream stream;
  WHEN("writing the AttributeCreate class") {
    stream << pl::kAttributeCreate;
    THEN("the output will be") {
      REQUIRE(stream.str() == "AttributeClass(attribute create)");
    }
  }
  WHEN("writing DatasetAccess class") {
    stream << pl::kDatasetAccess;
    REQUIRE(stream.str() == "AttributeClass(dataset access)");
  }
  WHEN("writing DatasetCreate class") {
    stream << pl::kDatasetCreate;
    REQUIRE(stream.str() == "AttributeClass(dataset create)");
  }
  WHEN("writing DatasetXfer class") {
    stream << pl::kDatasetXfer;
    REQUIRE(stream.str() == "AttributeClass(data transfer)");
  }
  WHEN("writing DatatypeAccess class") {
    stream << pl::kDatatypeAccess;
    REQUIRE(stream.str() == "AttributeClass(datatype access)");
  }
  WHEN("writing DatatyepCreate") {
    stream << pl::kDatatypeCreate;
    REQUIRE(stream.str() == "AttributeClass(datatype create)");
  }
  WHEN("writing FileAccess class") {
    stream << pl::kFileAccess;
    REQUIRE(stream.str() == "AttributeClass(file access)");
  }
  WHEN("writing FileCreate class") {
    stream << pl::kFileCreate;
    REQUIRE(stream.str() == "AttributeClass(file create)");
  }
  WHEN("writing FileMount class") {
    stream << pl::kFileMount;
    REQUIRE(stream.str() == "AttributeClass(file mount)");
  }
  WHEN("writing GroupAccess class") {
    stream << pl::kGroupAccess;
    REQUIRE(stream.str() == "AttributeClass(group access)");
  }
  WHEN("writing GroupCreate class") {
    stream << pl::kGroupCreate;
    REQUIRE(stream.str() == "AttributeClass(group create)");
  }
  WHEN("writing LinkAccess class") {
    stream << pl::kLinkAccess;
    REQUIRE(stream.str() == "AttributeClass(link access)");
  }
  WHEN("writing LinkCreate class") {
    stream << pl::kLinkCreate;
    REQUIRE(stream.str() == "AttributeClass(link create)");
  }
  WHEN("writing ObjectCopy class") {
    stream << pl::kObjectCopy;
    REQUIRE(stream.str() == "AttributeClass(object copy)");
  }
  WHEN("writing ObjectCreate class") {
    stream << pl::kObjectCreate;
    REQUIRE(stream.str() == "AttributeClass(object create)");
  }
  WHEN("writing StringCreate class") {
    stream << pl::kStringCreate;
    REQUIRE(stream.str() == "AttributeClass(string create)");
  }

  GIVEN("a default constructed class") {
    pl::Class cl;
    THEN("the output would be AttributeClass()") {
      stream << cl;
      REQUIRE(stream.str() == "AttributeClass()");
    }
  }
}

SCENARIO("testing comparison operators for the property list class") {
  GIVEN("a AttributeCreate class") {
    const auto& c1 = pl::kAttributeCreate;
    AND_GIVEN("another AttributeCreate class") {
      const auto& c2 = pl::kAttributeCreate;
      THEN("they will be considered equl") {
        REQUIRE(c1 == c2);
        REQUIRE_FALSE(c1 != c2);
      }
    }
    AND_GIVEN("a FileAccess class") {
      const auto& c2 = pl::kFileAccess;
      THEN("they will be considered not equal") {
        REQUIRE(c1 != c2);
        REQUIRE_FALSE(c1 == c2);
      }
    }
    AND_GIVEN("a default constructed class") {
      pl::Class c;
      THEN("the comparison will fail") {
        REQUIRE_THROWS_AS((pl::kAttributeCreate == c), std::runtime_error);
        REQUIRE_THROWS_AS((pl::kAttributeCreate != c), std::runtime_error);
      }
    }
  }
}
