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
// Created on: Oct 5, 2017
//
#ifdef H5CPP_CATCH2_V2
#include <catch2/catch.hpp>
#else
#include <catch2/catch_all.hpp>
#endif
#include <h5cpp/hdf5.hpp>

using namespace hdf5;

SCENARIO("testing attribute manageument functionality") { 
  auto file = file::create("attribute_management_test.h5", file::AccessFlags::Truncate);
  auto root = file.root();
  using datatype::Class;
  root.attributes.create<int>("index");
  root.attributes.create<float>("elasticity", {6, 6});
  root.attributes.create<std::uint32_t>("counter");
  root.attributes.iterator_config().index(IterationIndex::CreationOrder);
  root.attributes.iterator_config().order(IterationOrder::Increasing);

  GIVEN("that we want to remove an attribute") { 

    REQUIRE(root.attributes.size() == 3ul);
    REQUIRE(root.attributes.exists("index"));
    REQUIRE(root.attributes.exists("elasticity"));

    THEN("We can remove an attribute by its index") { 

      REQUIRE_NOTHROW(root.attributes.remove(0));
      REQUIRE(root.attributes.size() == 2ul);
      REQUIRE_FALSE(root.attributes.exists("index"));

      AND_THEN("remove another attribute by name") { 

        REQUIRE_NOTHROW(root.attributes.remove("elasticity"));
        REQUIRE_FALSE(root.attributes.exists("elasticity"));
        REQUIRE(root.attributes.size() == 1ul);
      }
    }
  } 

  GIVEN("want that a removed object remains") { 

    REQUIRE(root.attributes.size() == 3ul);
    auto a = root.attributes["counter"];
    REQUIRE(a.is_valid());
    REQUIRE_NOTHROW(root.attributes.remove("counter"));
    REQUIRE_FALSE(root.attributes.exists("counter"));
    REQUIRE(root.attributes.size() == 2ul);

    //however an already opened attribute remains alive
    REQUIRE(a.is_valid());
    REQUIRE(a.name() == "counter");
  }

  GIVEN("taht we want to remove an attribute which does not exist") {
    REQUIRE_THROWS_AS(root.attributes.remove("hello"), std::runtime_error);
    REQUIRE_THROWS_AS(root.attributes.remove(3), std::runtime_error);
  }

  GIVEN("we have an existing counter attribute") { 

    REQUIRE(root.attributes.exists("counter"));
    auto a = root.attributes["counter"];
    THEN("we can rename the attribute with") { 
      REQUIRE_NOTHROW(root.attributes.rename("counter","counter_2"));
      REQUIRE_FALSE(root.attributes.exists("counter"));
      REQUIRE(root.attributes.exists("counter_2"));
      REQUIRE(a.name() == "counter_2");
    }

    AND_THEN("we get an error when we try to remove") { 
      REQUIRE_FALSE(root.attributes.exists("counter_2"));
      REQUIRE_THROWS_AS(root.attributes.rename("counter_2","hello"), std::runtime_error);
    }

  }
  
}
