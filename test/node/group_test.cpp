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
// Authors:
//    Eugen Wintersberger <eugen.wintersberger@gmail.com>
//    Martin Shetty <martin.shetty@esss.se>
// Created on: Sep 12, 2017
//

#include <catch2/catch.hpp>
#include <h5cpp/hdf5.hpp>
#include <vector>
#include "../utilities.hpp"

using namespace hdf5;

SCENARIO("testing group constructors") {
  auto f = file::create("group_test.h5", file::AccessFlags::TRUNCATE);
  auto dt = datatype::create<int>();
  auto ds = dataspace::Scalar{};

  GIVEN("a default constructed group") {
    node::Group g;
    THEN("the group must have the following properties") {
      REQUIRE_FALSE(g.is_valid());
    }
  }

  GIVEN("the node reference to a dataset") {
    auto d = f.root().create_dataset("data", dt, ds);
    node::Node& nr = d;
    THEN("trying to create a group from this will fail") {
      REQUIRE_THROWS_AS(node::Group(nr), std::runtime_error);
    }
  }

  GIVEN("the root group of the file") {
    auto root = f.root();
    WHEN("using this as a parent in the constructor") {
      node::Group g(root, "test_group");
      THEN("we can use this to construct a new group with") {
        REQUIRE(g.is_valid());
        REQUIRE(g.link().path().name() == "test_group");
        REQUIRE(g.link().path().parent() == "/");
      }
    }
  }
  GIVEN("the node reference to the root group") {
    auto root = f.root();
    const node::Node& root_ref = root;
    THEN("we can construct a group from this") {
      node::Group g(root_ref);
      REQUIRE(g.link().path() == "/");
      const auto& nodes = root.nodes;
      WHEN("closing the original group") {
        root.close();
        THEN("the original reference must be invalid") {
          REQUIRE_FALSE(root.is_valid());
          AND_THEN("the new group must still be valid") {
            REQUIRE(g.is_valid());
          }
        }
        THEN("requesting the size of the nodes it must fail") {
          REQUIRE_THROWS_AS(nodes.size(), std::runtime_error);
        }
      }
    }
  }
}

SCENARIO("testing object creation and iteration") {
  auto f = file::create("group_test.h5", file::AccessFlags::TRUNCATE);
  auto root = f.root();

  THEN("the group must have the followin properties") {
    REQUIRE(root.is_valid());
    REQUIRE(root.type() == node::Type::GROUP);
    REQUIRE(root.link().path() == "/");
    REQUIRE(root.link().file().path() == "group_test.h5");
    AND_THEN("for a non-existing child group") {
      REQUIRE_FALSE(root.exists("hello"));
    }
    AND_THEN("we expect for the links view") {
      REQUIRE(root.links.size() == 0ul);
      GIVEN("the name of a non-existing child") {
        THEN("we can ask for its existance") {
          REQUIRE_FALSE(root.links.exists("data_group"));
        }
      }
      GIVEN("a path to a non-existing object") {
        THEN("the exists method must throw an exception") {
          REQUIRE_THROWS_AS(root.links.exists("data_group/elements"),
                            std::runtime_error);
          REQUIRE_THROWS_AS(root.links.exists("/data_group"),
                            std::runtime_error);
        }
      }
      WHEN("we try to access any link by index") {
        THEN("the operation must fail") {
          REQUIRE_THROWS_AS(root.links[1], std::runtime_error);
        }
      }
    }
    AND_THEN("we expect for the nodes view") {
      REQUIRE(root.nodes.size() == 0ul);
    }
  }

  GIVEN("a link creation property list") {
    property::LinkCreationList lcpl;
    WHEN("this list is closed") {
      close(lcpl);
      THEN("trying to create a group with this list must fail") {
        REQUIRE_THROWS_AS(root.create_group("group_1", lcpl),
                          std::runtime_error);
      }
    }
  }

  WHEN("creating a new group below the root group") {
    auto g = root.create_group("group_1");
    THEN("there must be") {
      REQUIRE(root.exists("group_1"));
      REQUIRE(root.nodes.size() == 1ul);
      REQUIRE(root.links.size() == 1ul);
    }
    THEN("the IDs of every reference to the new group must match") {
      REQUIRE(g.id() == root["group_1"].id());
    }
    AND_WHEN("creating a second group") {
      root.create_group("group_2");
      THEN("there must be") {
        REQUIRE(root.nodes.size() == 2ul);
        REQUIRE(root.links.size() == 2ul);
      }
      WHEN("trying to create a group of identical name") {
        THEN("the attempt must fail") {
          REQUIRE_THROWS_AS(root.create_group("group_2"), std::runtime_error);
        }
      }
    }
  }
  GIVEN("a dataspace and a datatype") {
    auto dt = datatype::create<int>();
    auto ds = dataspace::Simple({0});

    WHEN("creating a first dataset below the root group") {
      auto d1 = root.create_dataset("data_1", dt, ds);
      THEN("the root group must have one child element") {
        REQUIRE(root.nodes.size() == 1ul);
        REQUIRE(root.links.size() == 1ul);
      }
      AND_WHEN("creating a second dataset") {
        auto d2 = root.create_dataset("data_2", dt, ds);
        THEN("the root group must have two children") {
          REQUIRE(root.nodes.size() == 2ul);
          REQUIRE(root.links.size() == 2ul);
        }
        GIVEN("the links view to this group") {
          const auto& links = root.links;
          THEN("the links to the datasets must exist") {
            REQUIRE(links.exists("data_1"));
            REQUIRE(links.exists("data_2"));
            AND_THEN("we can compare this links with the created objects") {
              REQUIRE(d1.link() == links["data_1"]);
              REQUIRE(d2.link() == links["data_2"]);
            }
          }
        }
        GIVEN("the nodes view to this group") {
          const auto& nodes = root.nodes;
          THEN("the references to the datasets must exists") {
            REQUIRE(nodes.exists("data_1"));
            REQUIRE(nodes.exists("data_2"));
            AND_THEN("we can check the id") {
              REQUIRE(d1.id() == nodes["data_1"].id());
              REQUIRE(d2.id() == nodes["data_2"].id());
            }
          }
        }
      }
      AND_WHEN("trying to create a a second dataset with the same name") {
        REQUIRE_THROWS_AS(root.create_dataset("data_1", dt, ds),
                          std::runtime_error);
      }
    }
    WHEN("trying to create a dataset with a non-existing path") {
      REQUIRE_THROWS_AS(root.create_dataset("/bad/name", dt, ds),
                        std::runtime_error);
    }
  }
}

SCENARIO("Testing group creation with funny names") {
  auto f = file::create("group_test.h5", file::AccessFlags::TRUNCATE);
  auto r = f.root();
  WHEN("creating a group with the name 's p a c e y'") {
    REQUIRE_NOTHROW(r.create_group("s p a c e y"));
    REQUIRE(r.exists("s p a c e y"));
  }
  WHEN("creating a group with the name ' sp'") {
    REQUIRE_NOTHROW(r.create_group(" sp"));
    REQUIRE(r.exists(" sp"));
  }
  WHEN("creating a group with the name 'sp '") {
    REQUIRE_NOTHROW(r.create_group("sp "));
    REQUIRE(r.exists("sp "));
  }
  WHEN("creating a group with name 'sp'") {
    REQUIRE_NOTHROW(r.create_group("sp"));
    REQUIRE(r.exists("sp"));
  }
  WHEN("creating a group with name ' '") {
    REQUIRE_NOTHROW(r.create_group(" "));
    REQUIRE(r.exists(" "));
  }
  WHEN("creating a group with name '  '") {
    REQUIRE_NOTHROW(r.create_group("  "));
    REQUIRE(r.exists("  "));
  }
  WHEN("creating a group with name 'd.o.t.s'") {
    REQUIRE_NOTHROW(r.create_group("d.o.t.s"));
    REQUIRE(r.exists("d.o.t.s"));
  }
  WHEN("creating a group with name '.d.o.t'") {
    REQUIRE_NOTHROW(r.create_group(".d.o.t"));
    REQUIRE(r.exists(".d.o.t"));
  }
  WHEN("creating a group with name 'd..t'") {
    REQUIRE_NOTHROW(r.create_group("d..t"));
    REQUIRE(r.exists("d..t"));
  }
  WHEN("creating a group with name '..dt'") {
    REQUIRE_NOTHROW(r.create_group("..dt"));
    REQUIRE(r.exists("..dt"));
  }
  WHEN("creating a group with name '..'") {
    REQUIRE_NOTHROW(r.create_group(".."));
    REQUIRE(r.exists(".."));
  }

  //  EXPECT_NO_THROW(g.create_group("g/g2"));
  //  EXPECT_NO_THROW(g.create_group("./g/g3"));
  WHEN("trying to create group of name '.'") {
    THEN("the attempt must fail") {
      REQUIRE_THROWS_AS(r.create_group("."), std::exception);
    }
  }
}

SCENARIO("testing group convenience functions") {
  auto dt = datatype::create<int>();
  auto ds = dataspace::Scalar{};
  auto f = file::create("group_test.h5", file::AccessFlags::TRUNCATE);
  auto r = f.root();

  GIVEN("a new group") {
    auto g = r.create_group("group_1");
    THEN("we get") {
      REQUIRE(r.has_group("group_1"));
      REQUIRE_FALSE(r.has_group("group_2"));
      REQUIRE(g == r.get_group("group_1"));
    }
  }
  GIVEN("a new dataset") {
    auto d = r.create_dataset("data_1", dt, ds);
    THEN("we get") {
      REQUIRE(r.has_dataset("data_1"));
      REQUIRE_FALSE(r.has_dataset("data_2"));
      REQUIRE(d == r.get_dataset("data_1"));
    }
  }

  GIVEN("a group and a dataset below the root group") {
    auto g = r.create_group("group_1");
    auto d = r.create_dataset("data_1", dt, ds);
    THEN("we can copy the dataset to the new group") {
      g.copy_here(d);
      AND_THEN("we get") {
        REQUIRE(g.exists("data_1"));
        REQUIRE(r.exists("data_1"));
        WHEN("removing the dataset from the new group") {
          g.remove("data_1");
          AND_THEN("we get") {
            REQUIRE_FALSE(g.exists("data_1"));
            REQUIRE(r.exists("data_1"));
          }
        }
      }
    }
    WHEN("we can create an internal link to the dataset in the group") {
      g.create_link("internal", "/data_1");
      THEN("we get") { REQUIRE(g.has_dataset("internal")); }
    }
    THEN("we can move the dataset to the new group") {
      g.move_here(d);
      AND_THEN("we get") {
        REQUIRE(g.exists("data_1"));
        REQUIRE_FALSE(r.exists("data_1"));
      }
    }
    AND_GIVEN("a second file") {
      auto f2 = file::create("group_test_2.h5", file::AccessFlags::TRUNCATE);
      auto r2 = f2.root();
      auto g2 = r2.create_group("group").create_group("contents");
      THEN("we can copy the dataset to the new group") {
        g2.copy_here(d);
        AND_THEN("we get") {
          REQUIRE(g2.exists("data_1"));
          REQUIRE(g2.has_dataset("data_1"));
          REQUIRE(r.exists("data_1"));
          REQUIRE(r.has_dataset("data_1"));
        }
      }
      WHEN("trying to move the dataset to the second file") {
        THEN("the operation must fail") {
          REQUIRE_THROWS_AS(g2.move_here(d), std::runtime_error);
        }
      }
      WHEN("creating an external link to the second file") {
        REQUIRE_NOTHROW(
            g.create_link("external", "group_test_2.h5", "/group/contents"));
        THEN("we can check") { REQUIRE(g.get_group("external") == g2); }
      }
    }
  }
}