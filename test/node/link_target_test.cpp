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
// Created on: Mar 1, 2018
//
#include <catch2/catch.hpp>
#ifdef H5CPP_WITH_BOOST
#include <boost/version.hpp>
#else
#define BOOST_VERSION 100
#endif
#include <iterator>
//#include "group_test_fixtures.hpp"
#include <h5cpp/hdf5.hpp>

namespace { 
  static size_t get_path_size(const fs::path& path) {
  #if BOOST_VERSION < 106000
    return std::distance(path.begin(), path.end());
  #else
    return path.size();
  #endif
  }
}

using namespace hdf5;

SCENARIO("testing lint targets") {
  WHEN("default costructing a link target") {
    node::LinkTarget target;
    THEN("the size of the object path is 0") {
      REQUIRE(target.object_path().size() == 0ul);
    }
    THEN("the size of the file path is 0") {
      REQUIRE(get_path_size(target.file_path()) == 0ul);
    }
  }

  GIVEN("a path to an object in a file") {
    hdf5::Path object_path("/data");
    WHEN("constructing a link target for the same file") {
      node::LinkTarget target(object_path);
      THEN("the original path and the target path must match") {
        REQUIRE(target.object_path() == object_path);
      }
      THEN("the file path size is 0") {
        REQUIRE(get_path_size(target.file_path()) == 0ul);
      }
    }
    AND_GIVEN("a path to a file") {
      fs::path file_path("test.h5");
      WHEN("constructing a link target for a different file ") {
        node::LinkTarget target(object_path, file_path);
        THEN("the object path must be same") {
          REQUIRE(target.object_path() == object_path);
        }
        THEN("the file path must be the same") {
          REQUIRE(target.file_path() == file_path);
        }
      }
    }
  }

  GIVEN("an open HDF5 file") {
    auto h5file = hdf5::file::create("LinkTargetTest.h5",
                                     hdf5::file::AccessFlags::Truncate);
    auto root_group = h5file.root();
    hdf5::node::Group(root_group, "original");
    hdf5::node::link("/original", root_group, "internal_link");

    AND_GIVEN("a link to the existing 'original' group") {
      auto link = root_group.links["original"];
      THEN("the link is resolvable") { REQUIRE(link.is_resolvable()); }
      THEN("the type of the link is HARD") {
        REQUIRE(link.type() == hdf5::node::LinkType::Hard);
      }
      WHEN("fetching the target for the link") {
        auto target = link.target();
        THEN("the object path will be '/original'") {
          REQUIRE(target.object_path() == "/original");
        }
        THEN("the file path size is 0") {
          REQUIRE(get_path_size(target.file_path()) == 0ul);
        }
      }
    }

    AND_GIVEN("a link to the /internal_link") {
      auto link = root_group.links["internal_link"];
      THEN("the link is resolvable") { REQUIRE(link.is_resolvable()); }

      WHEN("fetching the target of the link") {
        auto target = link.target();

        THEN("the object path will be /original") {
          REQUIRE(target.object_path() == "/original");
        }
        THEN("the file path size will be 0") {
          REQUIRE(get_path_size(target.file_path()) == 0ul);
        }
      }
    }

    AND_GIVEN("another open HDF5 file") {
      auto f = hdf5::file::create("LinkTargetTestExternal.h5",
                                  hdf5::file::AccessFlags::Truncate);
      hdf5::node::Group(f.root(), "external_group");
      hdf5::node::link("LinkTargetTestExternal.h5", "/external_group",
                       root_group, "external_link");

      AND_GIVEN("a link to /external_link") {
        auto link = root_group.links["external_link"];
        THEN("the link must be resolvable") { REQUIRE(link.is_resolvable()); }
        WHEN("fetching the target for this link") {
          auto target = link.target();
          THEN("the object path is the path in the orignal file") {
            REQUIRE(target.object_path() == "/external_group");
          }
          THEN("the file path is the path to the second file") {
            REQUIRE(target.file_path() == "LinkTargetTestExternal.h5");
          }
        }
      }
    }
  }
}
