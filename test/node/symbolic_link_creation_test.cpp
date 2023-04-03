//
// (c) Copyright 2017 DESY,ESS
//               2021 Eugen Wintersberger <eugen.wintersberger@gmail.com>
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
// Created on: Nov 20, 2017
//
#include <catch2/catch_all.hpp>
#include <h5cpp/hdf5.hpp>

using hdf5::Path;
using hdf5::node::Group;
using hdf5::node::link;
using hdf5::node::Link;
using hdf5::node::LinkTarget;
using hdf5::property::LinkCreationList;
using namespace hdf5;

SCENARIO("testing symbolic link creation") {
  auto f = file::create("symbolic_link_creation_test.h5",
                        file::AccessFlags::Truncate);
  property::LinkCreationList lcpl;
  lcpl.enable_intermediate_group_creation();

  GIVEN("a group 'data' below the root group") {
    auto data = node::Group(f.root(), "data");
    THEN("we can create new linke to this group") {
      node::link(data, f.root(), Path("data_link"));
      auto l = f.root().links["data_link"];
      REQUIRE(l.type() == node::LinkType::Soft);
      REQUIRE(l.target().object_path() == Path("/data"));
    }
    AND_GIVEN("a second hierarchy of groups") {
      Group(f.root(), "/links/datalinks", lcpl);
      THEN("we can create a link from data into this group") {
        link(data, f.root(), "links/datalinks/new_link");
      }
    }
  }
}

/**
TEST_F(SymbolicLinkCreationTest, on_different_level) {
  Group data(file.root(), Path("data"));
  Group(file.root(), Path("links/datalinks"), lcpl);
  link(data, file.root(), Path("links/datalinks/new_data"));
  Link l = hdf5::node::get_node(file.root(), Path("links/datalinks/new_data"))
               .link();
  EXPECT_EQ(l.type(), hdf5::node::LinkType::Soft);
  EXPECT_EQ(l.target().object_path(), Path("/data"));
}
**/
