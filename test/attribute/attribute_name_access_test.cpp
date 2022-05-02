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
// Created on: Oct 5, 2017
//
#include <catch2/catch.hpp>
#include <vector>
#include <algorithm>
#include <iterator>
#include <h5cpp/hdf5.hpp>
#include <h5cpp/contrib/stl/stl.hpp>

using namespace hdf5;

using names_t = std::vector<std::string>;

namespace { 
static datatype::Class type_class(const attribute::Attribute &attribute)
{
  return attribute.datatype().get_class();
}

static names_t attr_names(const node::Node &node)
{
  names_t names;
  std::transform(std::begin(node.attributes), std::end(node.attributes),
                 std::back_inserter(names),
                 [](const attribute::Attribute &a) { return a.name(); });
  return names;
}
}

SCENARIO("Accessing attribute names")
{
  auto file = file::create("attribute_name_access_test.h5", file::AccessFlags::Truncate);
  auto root = file.root();
  using datatype::Class;
  root.attributes.create<int>("index");
  root.attributes.create<float>("elasticity", {6, 6});
  root.attributes.create<std::uint32_t>("counter");

  GIVEN("the standard")
  {
    THEN("the number of attribute")
    {
      REQUIRE(root.attributes.size() == 3ul);
    }
    AND_THEN("the attributes have the following types")
    {
      REQUIRE(type_class(root.attributes["index"]) == Class::Integer);
      REQUIRE(type_class(root.attributes["elasticity"]) == Class::Float);
      REQUIRE(type_class(root.attributes["counter"]) == Class::Integer);
    }

    AND_THEN("we get in case of illegal access")
    {
      REQUIRE_THROWS_AS(root.attributes[3], std::runtime_error);
      REQUIRE_THROWS_AS(root.attributes["hello"], std::runtime_error);
    }
  }

  GIVEN("Using the creation order as an index")
  {
    root.attributes.iterator_config().index(IterationIndex::CreationOrder);

    AND_GIVEN("increasing ordering")
    {
      root.attributes.iterator_config().order(IterationOrder::Increasing);
      THEN("we expect the following attributes names")
      {
        REQUIRE(root.attributes[0].name() == "index");
        REQUIRE(root.attributes[1].name() == "elasticity");
        REQUIRE(root.attributes[2].name() == "counter");
      }
      AND_THEN("algorithms should produce the same result")
      {
        auto ref_names = names_t{"index", "elasticity", "counter"};
        REQUIRE_THAT(ref_names, Catch::Matchers::Equals(attr_names(root)));
      }
    }

    AND_GIVEN("decreasing ordering")
    {
      root.attributes.iterator_config().order(IterationOrder::Decreasing);
      THEN("the names are")
      {
        REQUIRE(root.attributes[2].name() == "index");
        REQUIRE(root.attributes[1].name() == "elasticity");
        REQUIRE(root.attributes[0].name() == "counter");
      }
      AND_THEN("the iterators give")
      {
        auto ref_names = names_t{"counter", "elasticity", "index"};
        REQUIRE_THAT(ref_names, Catch::Matchers::Equals(attr_names(root)));
      }
    }
  }

  GIVEN("using the attribute name as an index")
  {
    root.attributes.iterator_config().index(IterationIndex::Name);
    AND_GIVEN("increasing ordering")
    {
      root.attributes.iterator_config().order(IterationOrder::Increasing);
      THEN("the names are")
      {
        REQUIRE(root.attributes[2].name() == "index");
        REQUIRE(root.attributes[1].name() == "elasticity");
        REQUIRE(root.attributes[0].name() == "counter");
      }
      AND_THEN("the iterator yields")
      {
        auto ref_names = names_t{"counter", "elasticity", "index"};
        REQUIRE_THAT(ref_names, Catch::Matchers::Equals(attr_names(root)));
      }
    }

    AND_GIVEN("decreasing ordering")
    {
      root.attributes.iterator_config().order(IterationOrder::Decreasing);

      THEN("the attribute names are")
      {
        REQUIRE(root.attributes[0].name() == "index");
        REQUIRE(root.attributes[1].name() == "elasticity");
        REQUIRE(root.attributes[2].name() == "counter");
      }

      AND_THEN("we get for the iteration")
      {
        auto ref_names = names_t{"index", "elasticity", "counter"};
        REQUIRE_THAT(ref_names, Catch::Matchers::Equals(attr_names(root)));
      }

      AND_THEN("we get for the iterator increments")
      {
        auto iter = root.attributes.begin();
        REQUIRE((iter++)->name() == "index");
        REQUIRE(iter->name() == "elasticity");
        REQUIRE((++iter)->name() == "counter");
      }

      AND_THEN("we get for the iterator decrements")
      {
        auto iter = std::begin(root.attributes);

        std::advance(iter, 2);
        REQUIRE((iter--)->name() == "counter");
        REQUIRE(iter->name() == "elasticity");
        REQUIRE((--iter)->name() == "index");
      }

      AND_THEN("for an invalid iterator we get")
      {
        auto iter = std::end(root.attributes);

        REQUIRE_THROWS_AS((*iter), std::runtime_error);
        REQUIRE_FALSE(static_cast<bool>(iter));
      }

      AND_THEN("we get for unary arithmetics")
      {
        auto iter = std::begin(root.attributes);
        std::advance(iter, 2);
        REQUIRE(iter->name() == "counter");
        iter -= 2;
        REQUIRE(iter->name() == "index");
      }
    }
  }

  GIVEN("an additional entry group") { 
    auto entry = hdf5::node::Group(root, "entry");
    entry.attributes.create("names",hdf5::datatype::create<std::string>(),
                            hdf5::dataspace::Scalar());

    THEN("we get for two iterators") { 
      REQUIRE_FALSE(std::begin(root.attributes) == std::begin(entry.attributes));
    }
  }
}

/*


TEST_F(AttributeName, test_iterator_random_access)
{
  root_.attributes.iterator_config().index(IterationIndex::Name);
  root_.attributes.iterator_config().order(IterationOrder::Decreasing);

  std::vector<std::string> ref_names{"index", "elasticity", "counter"};

  auto iter = root_.attributes.begin();
  auto iter_end = root_.attributes.end();
  std::advance(iter, 1);
  EXPECT_EQ(iter->name(), "elasticity");
  EXPECT_NO_THROW(iter--);
  EXPECT_EQ(iter->name(), "index");
}

*/
