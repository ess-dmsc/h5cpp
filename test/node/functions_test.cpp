
//
// (c) Copyright 2017 DESY,ESS
//               2020 Eugen Wintersberger <eugen.wintersberger@gmail.com>
//
// This file is part of h5cpp.
//
// h5cpp is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// h5cpp is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the imndied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  ee the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with h5cpp.  If not, see <http://www.gnu.org/licenses/>.
// ===========================================================================
//
// Author: Martin Shetty <martin.shetty@esss.se>
//         Eugen Wintersberger <eugen.wintersberger@gmail.com>
// Created on: Oct 2, 2017
//

#include <catch2/catch.hpp>
#include <h5cpp/hdf5.hpp>
#include "../utilities.hpp"

using namespace hdf5;
/*
class NodeFunctions : public BasicFixture {
 protected:
  void SetUp() override
  {
    BasicFixture::SetUp();

    group1_ = root_.create_group("group_1");
    group2_ = root_.create_group("group_2");
    target_ = group1_.create_group("target");
    target_.create_group("contents");
    root_.create_dataset("dataset", datatype::create<int>(),
dataspace::Simple({0}));

    file2_ = hdf5::file::create("./file2.h5", file::AccessFlags::Truncate);
    file2_target_ =
file2_.root().create_group("group").create_group("contents"); file2_.close();
  }
  virtual ~NodeFunctions() {}

  hdf5::node::Group group1_, group2_, target_;
  hdf5::file::File file2_;
  hdf5::node::Group file2_target_;
};
*/

SCENARIO("testing node removal") {
  auto file = file::create("node_test_1.h5", file::AccessFlags::Truncate);
  auto root = file.root();

  GIVEN("a group below the root group") {
    auto group = root.create_group("group");
    THEN("the group must exist") { REQUIRE(root.exists("group")); }
    WHEN("we remove the node by path") {
      node::remove(root, "group");
      THEN("the group no longer exists") {
        REQUIRE_FALSE(root.exists("group"));
        AND_WHEN("we try to remove the group a second time") {
          THEN("the operation must fail") {
            REQUIRE_THROWS_AS(node::remove(root, "group"), std::runtime_error);
          }
        }
      }
    }
    WHEN("we remove the group by reference") {
      node::remove(group);
      THEN("the group no longer exists") {
        REQUIRE_FALSE(root.exists("group"));
      }
    }
    GIVEN("a link access property list") {
      property::LinkAccessList lapl;
      WHEN("we close the list") {
        close(lapl);
        THEN("trying to use this list in a remove operation must fail") {
          REQUIRE_THROWS_AS(node::remove(root, "group", lapl),
                            std::runtime_error);
        }
      }
    }
  }
}

SCENARIO("Testing node copying") {
  const std::string filename = "testing_node_copying.h5";
  auto file = file::create(filename, file::AccessFlags::Truncate);
  auto root = file.root();
  GIVEN("a group below the root group") {
    auto g1 = root.create_group("group1");
    WHEN("trying to create a copy under the same name") {
      THEN("the operation must fail") {
        REQUIRE_THROWS_AS(node::copy(g1, root), std::runtime_error);
      }
    }
    WHEN("trying to copy the root group") {
      THEN("the operation must fail") {
        REQUIRE_THROWS_AS(node::copy(root, g1), std::runtime_error);
      }
    }
    AND_GIVEN("a second group below the root group") {
      auto g2 = root.create_group("group2");
      THEN("copy the second group into the first") {
        node::copy(g2, g1);
        AND_THEN("g1 must have a new child group group2") {
          REQUIRE(g1.exists("group2"));
        }
      }
      THEN("copy the second group into the first as gt") {
        node::copy(g2, g1, "gt");
        AND_THEN("we get") { REQUIRE(g1.exists("gt")); }
      }
      AND_GIVEN("an object copy property list") {
        property::ObjectCopyList ocpl;
        AND_THEN("closing the list") {
          close(ocpl);
          THEN("any attempt to use this list in a copy operation must fail") {
            REQUIRE_THROWS_AS(node::copy(g2, g1, ocpl), std::runtime_error);
          }
        }
      }
    }
  }
}

SCENARIO("testing moving nodes") {
  const std::string filename = "testing_moving_nodes.h5";
  auto file = file::create(filename, file::AccessFlags::Truncate);
  auto root = file.root();
  GIVEN("/group1 below the root") {
    auto g1 = root.create_group("group1");
    AND_GIVEN("/group2 below the root") {
      auto g2 = root.create_group("group2");
      WHEN("moving the second into the first") {
        node::move(g2, g1, "gt");
        AND_THEN("we get") {
          REQUIRE(g1.exists("gt"));
          REQUIRE_FALSE(root.exists("group2"));
        }
        AND_GIVEN("a third group below the root group") {
          auto g3 = root.create_group("group3");
          WHEN(
              "when try to move this to the same name in group1 the operation "
              "must fail") {
            REQUIRE_THROWS_AS(node::move(g3, g1, "gt"), std::runtime_error);
          }
        }
      }
      AND_GIVEN("a link creation property list") {
        property::LinkCreationList lcpl;
        WHEN("closing thist list") {
          close(lcpl);
          THEN("any move operation with thist list must fail") {
            REQUIRE_THROWS_AS(node::move(g2, g1, lcpl), std::runtime_error);
          }
        }
      }
    }
  }
}

/*

TEST_F(NodeFunctions, test_move_node) {

  nd::Group gm = group2_["gt"];
  EXPECT_NO_THROW(nd::move(gm, group1_));
  EXPECT_TRUE(group1_.exists("gt"));
  EXPECT_FALSE(group2_.exists("gt"));
  EXPECT_THROW(nd::move(gm, group1_), std::runtime_error);
}
*/

SCENARIO("testing external links") {
  const std::string filename = "testing_external_links.h5";
  auto dtype = datatype::create<double>();
  auto dspace = dataspace::Scalar{};
  auto f1 = file::create(filename, file::AccessFlags::Truncate);
  auto r1 = f1.root();
  r1.create_dataset("data", dtype, dspace);
  // create the second file where the targets of the external links are
  // located
  {
    auto f = file::create("./node_test2.h5", file::AccessFlags::Truncate);
    f.root().create_group("group2").create_dataset("content", dtype, dspace);
  }

  auto link = [&](const Path& p) {
    node::link("./node_test2.h5", "group2", r1, p);
  };
  GIVEN("a link creation property list") {
    property::LinkCreationList lcpl;
    WHEN("closing the list") {
      close(lcpl);
      THEN("any attempt to use it in an external linking operation will fail") {
        REQUIRE_THROWS_AS(
            node::link("./node_test2.h5", "group2", r1, "link", lcpl),
            std::runtime_error);
      }
    }
  }
  WHEN("The target location is not a group") {
    REQUIRE_THROWS_AS(link("/data"), std::runtime_error);
  }

  GIVEN("a list of paths") {
    auto paths = GENERATE(Path{"link"}, Path{"/link"});
    WHEN("creating a link to this path") {
      link(paths);
      THEN("the new group exists") {
        REQUIRE(r1.exists("link"));
        AND_THEN("we can also check for the contents") {
          REQUIRE(node::Group(r1["link"]).exists("content"));
        }
      }
    }
  }

  GIVEN("a path to a non yet existing object in the secondary file") {
    auto path = Path{"group2_future"};
    THEN("creating the link should work") {
      node::link("./node_test2.h5", path, r1, "link");
      THEN("the link must exist") { REQUIRE(r1.links.exists("link")); }
      THEN("access to the object must fail") {
        REQUIRE_THROWS_AS(r1["link"], std::runtime_error);
      }
    }
  }
}

SCENARIO("testing soft links") {
  const std::string filename = "testing_soft_links.h5";
  auto f = file::create(filename, file::AccessFlags::Truncate);
  auto r = f.root();

  GIVEN("a group below root") {
    auto g = r.create_group("group1");

    AND_GIVEN("absolute and relative link paths") {
      auto paths = GENERATE("link", "/link");
      WHEN("attempting to link") {
        node::link("/group1", r, paths);
        THEN("the group should exist") { REQUIRE(r.exists("link")); }
      }
      AND_GIVEN("a link creation property list") {
        property::LinkCreationList lcpl;
        AND_WHEN("closing this list") {
          close(lcpl);
          THEN("using ist in a link operation causes the operation to fail") {
            REQUIRE_THROWS_AS(node::link("/group1", r, paths, lcpl),
                              std::runtime_error);
          }
        }
      }
    }
    AND_GIVEN("a dataset") {
      auto d = r.create_dataset("data", datatype::create<double>(),
                                dataspace::Scalar{});
      WHEN("attempting to use this as a target for a link") {
        THEN("the linking must fail") {
          REQUIRE_THROWS_AS(node::link("/group1", r, "/data/NA"),
                            std::runtime_error);
        }
      }
    }
  }
  WHEN("creating a link to a non-existing object") { 
    node::link("dataset", r, "/data");
    THEN("the link must exist") { 
      REQUIRE(r.links.exists("data"));
    }
    THEN("accessing the object must fail") { 
      REQUIRE_THROWS_AS(r["data"], std::runtime_error);
    }
  }
}

SCENARIO("testing linking") {}
/*
TEST_F(NodeFunctions, test_link)
{
  EXPECT_NO_THROW(nd::link(target_, root_, Path("internal")));
  EXPECT_NO_THROW(nd::link(file2_target_, root_, Path("external")));
}
*/
