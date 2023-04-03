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
// Created on: Oct 4, 2017
//
#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>
#include <h5cpp/attribute/attribute.hpp>
#include <h5cpp/datatype/datatype.hpp>
#include <h5cpp/dataspace/dataspace.hpp>
#include <h5cpp/file/functions.hpp>
#include <h5cpp/node/group.hpp>


using namespace hdf5;

TEST_CASE("testing attribute construction","[h5cpp],[attribute],[create]") { 
  auto file = file::create("attribute_test.h5", file::AccessFlags::Truncate);
  auto root = file.root();

  SECTION("default construction") { 
    attribute::Attribute a;
    REQUIRE_THROWS_AS(a.datatype(), std::runtime_error);
    REQUIRE_THROWS_AS(a.dataspace(), std::runtime_error);
    REQUIRE_THROWS_AS(a.name(), std::runtime_error);
    REQUIRE_FALSE(a.is_valid());
  }

  SECTION("scalar construction") { 

    attribute::Attribute a;
    REQUIRE_NOTHROW(a = root.attributes.create<int>("test"));
    REQUIRE(a.dataspace().type() == dataspace::Type::Scalar);
    REQUIRE(a.parent_link().path() =="/");

    dataspace::Scalar space(a.dataspace());
    REQUIRE(a.datatype().get_class() == datatype::Class::Integer);
    REQUIRE(a.name() == "test");
    REQUIRE(root.attributes.size() == 1ul);

    REQUIRE_NOTHROW(a = root.attributes.create<float>("test2"));
    REQUIRE(a.dataspace().type() == dataspace::Type::Scalar);
    REQUIRE(a.datatype().get_class() == datatype::Class::Float);
    REQUIRE(a.name() == "test2");
    REQUIRE(root.attributes.size() == 2ul);

    //testing close function
    REQUIRE(a.is_valid());
    REQUIRE_NOTHROW(a.close());
    REQUIRE_FALSE(a.is_valid());
  }

  SECTION("test simple multidimensional construction") {
    attribute::Attribute a;
    REQUIRE_NOTHROW(a = root.attributes.create<int>("test",{1}));
    REQUIRE(a.dataspace().size() == 1L);
    REQUIRE(a.name() == "test");
    REQUIRE(a.dataspace().type() == dataspace::Type::Simple);
    dataspace::Simple space(a.dataspace());
    REQUIRE(space.rank() == 1u);
    REQUIRE(space.current_dimensions()[0] == 1ul);

    REQUIRE_NOTHROW(a = root.attributes.create<int>("matrix",{3,4}));
    REQUIRE(a.name() == "matrix");
    space = dataspace::Simple(a.dataspace());
    REQUIRE(space.rank() == 2u);
    REQUIRE(space.current_dimensions()[0] == 3ul);
    REQUIRE(space.current_dimensions()[1] == 4ul);
  }

  SECTION("multidimensional construction")
  {
    attribute::Attribute a;
    dataspace::Simple space{{3,4}};
    auto type = datatype::create<float>();

    REQUIRE_NOTHROW(a = root.attributes.create("test",type,space));
    REQUIRE(root.attributes.exists("test"));
    REQUIRE_FALSE(root.attributes.exists("bla"));
    REQUIRE(root.attributes.size() == 1ul);
    REQUIRE(a.name() == "test");
  }

  SECTION("creation from a scalar value")
  {
    auto a = root.attributes.create_from("test",float(23.4));
    float buffer;
    a.read(buffer);
    REQUIRE(buffer == Approx(23.4f));
  }

  SECTION("create from vector")
  {
    using AttributeData = std::vector<double>;
    AttributeData data{1,2,3,4,5};
    auto a = root.attributes.create_from("test",data);
    AttributeData buffer(data.size());
    a.read(buffer);
    REQUIRE(buffer == data);
  }
}






