
//
// (c) Copyright 2017 DESY,ESS
//
// This file is part of h5pp.
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
// Created on: Oct 2, 2017
//

#include "group_test_fixtures.hpp"

#include <h5cpp/node/functions.hpp>
#include <h5cpp/file/functions.hpp>

using namespace hdf5;
namespace nd = hdf5::node;

class Node : public BasicFixture {
};

TEST_F(Node, test_remove_node) {
  nd::Group f = file_.root();

  f.create_group("group");
  EXPECT_TRUE(f.exists("group"));
  EXPECT_NO_THROW(nd::remove(f, Path("group")));
  EXPECT_FALSE(f.exists("group"));

  EXPECT_THROW(nd::remove(f, Path("group")), std::runtime_error);

  auto g = f.create_group("group2");
  EXPECT_TRUE(f.exists("group2"));
  EXPECT_NO_THROW(nd::remove(g));
  EXPECT_FALSE(f.exists("group2"));
  EXPECT_THROW(nd::remove(g), std::runtime_error);

  f.create_group("group");
  property::LinkAccessList lapl;
  ObjectHandle(static_cast<hid_t>(lapl)).close();
  EXPECT_THROW(nd::remove(f, Path("group"), lapl), std::runtime_error);
}

TEST_F(Node, test_copy_node) {
  nd::Group f = file_.root();
  auto g1 = f.create_group("group_1");
  auto gt = g1.create_group("target");
  auto g2 = f.create_group("group_2");

  EXPECT_FALSE(g2.exists("gt"));
  EXPECT_NO_THROW(nd::copy(gt, g2, Path("gt")));
  EXPECT_TRUE(g2.exists("gt"));
  EXPECT_THROW(nd::copy(gt, g2, Path("gt")), std::runtime_error);

  property::ObjectCopyList ocpl;
  ObjectHandle(static_cast<hid_t>(ocpl)).close();
  EXPECT_THROW(nd::copy(gt, g2, Path("gt2"), ocpl), std::runtime_error);

  EXPECT_NO_THROW(nd::copy(gt, g2));
  EXPECT_TRUE(g2.exists("target"));

  EXPECT_NO_THROW(nd::copy(gt, f));
  EXPECT_TRUE(f.exists("target"));

  EXPECT_THROW(nd::copy(gt, f), std::runtime_error);

  //copying root does not work
  EXPECT_THROW(nd::copy(f, g2), std::runtime_error);
}

TEST_F(Node, test_move_node) {
  nd::Group f = file_.root();
  auto g1 = f.create_group("group_1");
  auto gt = g1.create_group("target");
  auto g2 = f.create_group("group_2");

  EXPECT_TRUE(g1.exists("target"));
  EXPECT_FALSE(g2.exists("gt"));
  EXPECT_NO_THROW(nd::move(gt, g2, Path("gt")));
  EXPECT_FALSE(g1.exists("target"));
  EXPECT_TRUE(g2.exists("gt"));

  property::LinkCreationList lcpl;
  ObjectHandle(static_cast<hid_t>(lcpl)).close();
  EXPECT_THROW(nd::move(gt, g2, Path("gt2"), lcpl), std::runtime_error);

  gt = g1.create_group("target");
  EXPECT_THROW(nd::move(gt, g2, Path("gt")), std::runtime_error);

  nd::Group gm = g2["gt"];
  EXPECT_NO_THROW(nd::move(gm, g1));
  EXPECT_TRUE(g1.exists("gt"));
  EXPECT_FALSE(g2.exists("gt"));
  EXPECT_THROW(nd::move(gm, g1), std::runtime_error);
}

TEST_F(Node, test_external_link) {
  auto file2 = hdf5::file::create("./file2.h5", file::AccessFlags::TRUNCATE);
  file2.root().create_group("group").create_group("contents");
  file2.close();

  nd::Group f = file_.root();
  f.create_group("group");

  EXPECT_THROW(nd::link("./file2.h5", Path("group"),
                        f, Path("group")),
               std::runtime_error);
  EXPECT_NO_THROW(nd::link("./file2.h5", Path("group"),
                           f, Path("group2")));

  EXPECT_NO_THROW(nd::link("./file2.h5", Path("group"),
                           f, Path("/group3")));

  property::LinkCreationList lcpl;
  ObjectHandle(static_cast<hid_t>(lcpl)).close();
  EXPECT_THROW(nd::link("./file2.h5", Path("group"),
                        f, Path("group4"), lcpl),
               std::runtime_error);

  EXPECT_TRUE(f.links.exists("group2"));
  EXPECT_TRUE(f.exists("group2"));
  nd::Group gg2 = f["group2"];
  EXPECT_TRUE(gg2.exists("contents"));
}

TEST_F(Node, test_soft_link) {
  nd::Group f = file_.root();
  auto g = f.create_group("group");
  auto g1 = g.create_group("group_1");
  auto gt = g1.create_group("target");

  EXPECT_NO_THROW(nd::link(g1, g, Path("group_2")));
  EXPECT_TRUE(g.links.exists("group_2"));
  EXPECT_TRUE(nd::Group(g["group_2"]).exists("target"));

  EXPECT_NO_THROW(nd::link(g1, gt, Path("/group_abs")));
  EXPECT_TRUE(f.links.exists("group_abs"));

  EXPECT_THROW(nd::link(g1, gt, Path("/group_abs")), std::runtime_error);

  property::LinkCreationList lcpl;
  ObjectHandle(static_cast<hid_t>(lcpl)).close();
  EXPECT_THROW(nd::link(g1, gt, Path("/group_bad_lcp"), lcpl), std::runtime_error);

  auto file2 = hdf5::file::create("./file2.h5", file::AccessFlags::TRUNCATE);
  auto target = file2.root().create_group("group").create_group("contents");
  EXPECT_NO_THROW(nd::link(target, g, Path("group_5")));
}
