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
// Created on: Nov 16, 2017
//
#include <catch2/catch_all.hpp>
#include <h5cpp/hdf5.hpp>

using namespace hdf5;

SCENARIO("testing the get node function") {
  auto file =
      file::create("GetNodeFunctionTest.h5", file::AccessFlags::Truncate);
  auto root = file.root();
  auto sensors = root.create_group("run_1").create_group("sensors");
  sensors.create_group("temperature");
  sensors.create_group("pressure");
  sensors = root.create_group("run_2").create_group("sensors");
  sensors.create_group("humidity");
  sensors.create_group("voltage");

  WHEN("trying to access a not existing node") {
    THEN("via the links view must fail") {
      REQUIRE_THROWS_AS(root.links["/invalid/node"], std::runtime_error);
    }
    THEN("via the nodes view must fail") {
      REQUIRE_THROWS_AS(root.nodes["/invalid/node"], std::runtime_error);
    }
  }
  WHEN("creating a link to run_1 below the root group") {
    root.create_link("invalid", root.nodes["run_1"]);
    REQUIRE(root.nodes.exists("run_1"));
    REQUIRE(root.nodes.exists("invalid"));
    AND_THEN("remove the run_1 group") {
      root.remove("run_1");
      THEN("also the node under invalid must be gone") {
        REQUIRE_FALSE(root.nodes.exists("invalid"));
      }
      THEN("the link invalid still exists") {
        REQUIRE(root.links.exists("invalid"));
      }
    }
  }
  GIVEN("run_1 as a base for searches") {
    node::Group base = root.nodes["run_1"];
    WHEN("trying to fetch an object by an empty path") {
      node::Group run_1 = node::get_node(base, Path());
      THEN("we get") {
        REQUIRE(run_1 == base);
        REQUIRE(run_1.link().path().name() == "run_1");
        REQUIRE(run_1.link().path().parent() == "/");
      }
    }
    WHEN("searching for the root group") {
      node::Group result = node::get_node(base, Path("/"));
      THEN("we also get the root group") { REQUIRE(root == result); }
    }
    WHEN("searching with a relative path") {
      node::Group result = node::get_node(base, Path("sensors/pressure"));
      THEN("we get the pressure group") {
        REQUIRE(result.link().path().name() == "pressure");
        REQUIRE(result.link().path().parent() == "/run_1/sensors");
      }
    }
    WHEN("searching using an absolute path") {
      node::Group result =
          node::get_node(base, Path("/run_2/sensors/humidity"));
      THEN("we get the humidity group") {
        REQUIRE(result.link().path().name() == "humidity");
        REQUIRE(result.link().path().parent() == "/run_2/sensors");
      }
    }
  }
}
