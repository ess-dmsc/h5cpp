
//
// (c) Copyright 2017 DESY,ESS
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
// Created on: Oct 2, 2017
//

#include "group_test_fixtures.hpp"

using namespace hdf5;
namespace nd = hdf5::node;

class NodeFunctions : public BasicFixture {
 protected:
  void SetUp() override
  {
    BasicFixture::SetUp();

    group1_ = root_.create_group("group_1");
    group2_ = root_.create_group("group_2");
    target_ = group1_.create_group("target");
    target_.create_group("contents");
    root_.create_dataset("dataset", datatype::create<int>(), dataspace::Simple({0}));

    file2_ = hdf5::file::create("./file2.h5", file::AccessFlags::TRUNCATE);
    file2_target_ = file2_.root().create_group("group").create_group("contents");
    file2_.close();
  }
  virtual ~NodeFunctions() {}

  hdf5::node::Group group1_, group2_, target_;
  hdf5::file::File file2_;
  hdf5::node::Group file2_target_;
};

TEST_F(NodeFunctions, test_remove_node) {
  EXPECT_NO_THROW(nd::remove(root_, Path("group_2")));
  EXPECT_FALSE(root_.exists("group_2"));

  EXPECT_THROW(nd::remove(root_, Path("group_2")), std::runtime_error);

  EXPECT_NO_THROW(nd::remove(target_));
  EXPECT_FALSE(group1_.exists("target"));
  EXPECT_THROW(nd::remove(target_), std::runtime_error);

  property::LinkAccessList lapl;
  ObjectHandle(static_cast<hid_t>(lapl)).close();
  EXPECT_THROW(nd::remove(root_, Path("group_1"), lapl), std::runtime_error);
}

TEST_F(NodeFunctions, test_copy_node) {
  EXPECT_NO_THROW(nd::copy(target_, group2_, Path("gt")));
  EXPECT_TRUE(group2_.exists("gt"));
  EXPECT_THROW(nd::copy(target_, group2_, Path("gt")), std::runtime_error);

  property::ObjectCopyList ocpl;
  ObjectHandle(static_cast<hid_t>(ocpl)).close();
  EXPECT_THROW(nd::copy(target_, group2_, Path("gt2"), ocpl), std::runtime_error);

  EXPECT_NO_THROW(nd::copy(target_, group2_));
  EXPECT_TRUE(group2_.exists("target"));

  EXPECT_NO_THROW(nd::copy(target_, root_));
  EXPECT_TRUE(root_.exists("target"));

  EXPECT_THROW(nd::copy(target_, root_), std::runtime_error);

  //copying root does not work
  EXPECT_THROW(nd::copy(root_, group2_), std::runtime_error);
}

TEST_F(NodeFunctions, test_move_node) {
  EXPECT_NO_THROW(nd::move(target_, group2_, Path("gt")));
  EXPECT_FALSE(group1_.exists("target"));
  EXPECT_TRUE(group2_.exists("gt"));

  property::LinkCreationList lcpl;
  ObjectHandle(static_cast<hid_t>(lcpl)).close();
  EXPECT_THROW(nd::move(target_, group2_, Path("gt2"), lcpl), std::runtime_error);

  target_ = group1_.create_group("target");
  EXPECT_THROW(nd::move(target_, group2_, Path("gt")), std::runtime_error);

  nd::Group gm = group2_["gt"];
  EXPECT_NO_THROW(nd::move(gm, group1_));
  EXPECT_TRUE(group1_.exists("gt"));
  EXPECT_FALSE(group2_.exists("gt"));
  EXPECT_THROW(nd::move(gm, group1_), std::runtime_error);
}

TEST_F(NodeFunctions, test_external_link) {
  // Provoke underlying API error
  property::LinkCreationList lcpl;
  ObjectHandle(static_cast<hid_t>(lcpl)).close();
  EXPECT_THROW(nd::link("./file2.h5", Path("group"), root_, Path("link"), lcpl), std::runtime_error);

  // Parent path not group
  EXPECT_THROW(nd::link("./file2.h5", Path("group"), root_, Path("/dataset/NA")), std::runtime_error);

  // Relative path
  EXPECT_NO_THROW(nd::link("./file2.h5", Path("group"), root_, Path("link1")));
  EXPECT_TRUE(nd::Group(root_["link1"]).exists("contents"));

  // Absolute path
  EXPECT_NO_THROW(nd::link("./file2.h5", Path("group"), target_, Path("/link2")));
  EXPECT_TRUE(nd::Group(root_["link2"]).exists("contents"));

  // Non-existent node
  EXPECT_NO_THROW(nd::link("./file2.h5", Path("future_group"), root_, Path("/link3")));
  EXPECT_TRUE(root_.links.exists("link3"));
}

TEST_F(NodeFunctions, test_soft_link) {
  // Provoke underlying API error
  property::LinkCreationList lcpl;
  ObjectHandle(static_cast<hid_t>(lcpl)).close();
  EXPECT_THROW(nd::link(Path("/group_1"), target_, Path("/link"), lcpl), std::runtime_error);

  // Parent path not group
  EXPECT_THROW(nd::link(Path("/group_1"), root_, Path("/dataset/NA")), std::runtime_error);


  //Relative path
  EXPECT_NO_THROW(nd::link(Path("/group_1"), root_, Path("link1")));
  EXPECT_TRUE(nd::Group(root_["link1"]).exists("target"));

  //Absolute path
  EXPECT_NO_THROW(nd::link(Path("/group_1"), target_, Path("/link2")));
  EXPECT_TRUE(nd::Group(root_["link2"]).exists("target"));

  // Non-existent node
  EXPECT_NO_THROW(nd::link(Path("/group_1"), target_, Path("/group_2/link3")));
  EXPECT_TRUE(nd::Group(group2_["link3"]).exists("target"));
}

TEST_F(NodeFunctions, test_link)
{
  EXPECT_NO_THROW(nd::link(target_, root_, Path("internal")));
  EXPECT_NO_THROW(nd::link(file2_target_, root_, Path("external")));
}
