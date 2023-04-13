//
// (c) Copyright 2017 DESY,ESS
//               2020 Eugen Wintersberger <eugen.wintersberger@gmail.com>
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
// Author: Eugen Wintersberger <eugen.wintersberger@gmail.com>
// Created on: Sep 25, 2017
//

#ifdef H5CPP_CATCH2_V2
#include <catch2/catch.hpp>
#else
#include <catch2/catch_all.hpp>
#endif
#include <h5cpp/hdf5.hpp>

using namespace hdf5;

SCENARIO("testing basic HDF5 link operations") {
  GIVEN("a default constructed link") {
    node::Link link;
    THEN("the type must be error") {
      REQUIRE(link.type() == node::LinkType::Error);
      AND_THEN("accessing the target must fail") {
        REQUIRE_THROWS_AS(link.target(), std::runtime_error);
      }
    }
  }
  GIVEN("a valid hdf5 file") {
    auto f = file::create("link_test.h5", file::AccessFlags::Truncate);
    WHEN("creating non-existing link (not in the file)") {
      node::Link l(f, "/", "name1");
      THEN("fetching the type will fail") {
        REQUIRE_THROWS_AS(l.type(), std::runtime_error);
      }
      THEN("the link does not exist") { REQUIRE_FALSE(l.exists()); }
      THEN("the link is not resolvable") { REQUIRE_FALSE(l.is_resolvable()); }
    }
    GIVEN("given a  link to an object") {
      node::Link l1(f, "path1", "name1");
      AND_GIVEN("a link with of equal name to the same object") {
        node::Link l2(f, "path1", "name1");
        THEN("the two links are considered equal") { REQUIRE(l1 == l2); }
      }
      AND_GIVEN("a link to a different object with different name") {
        node::Link l2(f, "path2", "name2");
        THEN("the two links are considered unequal") { REQUIRE(l1 != l2); }
      }
      WHEN("copy construct from this link") {
        node::Link l2 = l1;
        THEN("the two links are considered equal") { REQUIRE(l2 == l1); }
      }
      AND_GIVEN("a default constructed link") {
        node::Link l2;
        THEN("we can copy assign") {
          l2 = l1;
          AND_THEN("the two links are considered equal") { REQUIRE(l2 == l1); }
        }
      }
    }
    AND_GIVEN("a second HDF5 file") {
      auto f2 = file::create("link_test2.h5", file::AccessFlags::Truncate);
      WHEN("creating an external link to an nonexisting object") {
        node::link("link_test2.h5", "data", f.root(), "external_data");
        THEN("the link exists") {
          auto l = f.root().links["external_data"];
          REQUIRE(l.exists());
          AND_THEN("the link is of external type ") {
            REQUIRE(l.type() == node::LinkType::External);
          }
          AND_THEN("the link is not resolveable") {
            REQUIRE_FALSE(l.is_resolvable());
          }
        }
      }
    }
    GIVEN("the root node of the file") {
      auto root = f.root();
      AND_GIVEN("a group below the root node") {
        root.create_group("original");
        WHEN("creating a soft link to this group") {
          node::link("/original", root, "linked");
          auto l = root.links["linked"];
          THEN("the link must have the following properties") {
            REQUIRE(l.exists());
            REQUIRE(l.type() == node::LinkType::Soft);
            REQUIRE(l.is_resolvable());
          }
        }
        WHEN("creating a link to a non-existing object") {
          node::link("/original/data", root, "link");
          auto l = root.links["link"];
          THEN("the link must be") {
            REQUIRE(l.exists());
            REQUIRE(l.type() == node::LinkType::Soft);
            REQUIRE_FALSE(l.is_resolvable());
          }
        }
      }
    }
  }
}
