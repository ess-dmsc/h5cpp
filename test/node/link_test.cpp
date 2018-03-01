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
// Created on: Sep 25, 2017
//

#include "group_test_fixtures.hpp"

using namespace hdf5;

class Link : public BasicFixture
{
};

TEST_F(Link, test_default_construction)
{
  node::Link link;
  EXPECT_EQ(link.type(),node::LinkType::ERROR);
  EXPECT_THROW(link.target(),std::runtime_error);
}

TEST_F(Link,test_false_construction)
{
  node::Link link(file_,"/","name1");
  EXPECT_THROW(link.type(),std::runtime_error);
}

TEST_F(Link, test_equality)
{
  node::Link link1(file_, "path1", "name1");
  node::Link link2(file_, "path1", "name1");
  node::Link link3(file_, "path2", "name2");

  EXPECT_EQ(link1, link2);
  EXPECT_NE(link1, link3);
}

TEST_F(Link,test_copy_construction)
{
	node::Link link1(file_,"path1","name1");
	node::Link link2(link1);

	EXPECT_EQ(link1,link2);
}

TEST_F(Link,test_copy_assignment)
{
	node::Link link1(file_,"path1","name1");
	node::Link link2;

	link2 = link1;
	EXPECT_EQ(link1,link2);
}

TEST_F(Link, test_validity)
{
  node::Link link1(file_, "path1", "name1");

  EXPECT_FALSE(link1.exists());
  EXPECT_FALSE(link1.is_resolvable());
}

TEST_F(Link,test_invalid_external_link)
{
  boost::filesystem::path file_path("external_data.h5");
  hdf5::Path data_path("/data");

  hdf5::node::link(file_path,data_path,file_.root(),hdf5::Path("external_data"));
  hdf5::node::Link link = file_.root().links["external_data"];

  EXPECT_TRUE(link.exists());
  EXPECT_EQ(link.type(),hdf5::node::LinkType::EXTERNAL);
  EXPECT_FALSE(link.is_resolvable());
}

TEST_F(Link,test_valid_soft_link)
{
  hdf5::node::Group(file_.root(),hdf5::Path("original_group"));
  hdf5::node::link(hdf5::Path("/original_group"),file_.root(),"linked_group");

  hdf5::node::Link link = file_.root().links["linked_group"];
  EXPECT_TRUE(link.exists());
  EXPECT_EQ(link.type(),hdf5::node::LinkType::SOFT);
  EXPECT_TRUE(link.is_resolvable());
}

TEST_F(Link,test_invalid_soft_link)
{
  hdf5::node::link(hdf5::Path("/original/data"),file_.root(),hdf5::Path("linked_data"));
  hdf5::node::Link link = file_.root().links["linked_data"];

  EXPECT_EQ(link.type(),hdf5::node::LinkType::SOFT);
  EXPECT_TRUE(link.exists());
  EXPECT_FALSE(link.is_resolvable());
}

