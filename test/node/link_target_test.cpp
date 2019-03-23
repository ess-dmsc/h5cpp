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
// Created on: Mar 1, 2018
//

#include <boost/version.hpp>
#include <iterator>
#include "group_test_fixtures.hpp"

size_t get_path_size(const boost::filesystem::path& path)
{
#if BOOST_VERSION < 106000
  return std::distance(path.begin(),path.end());
#else
  return path.size();
#endif
}

using namespace hdf5;

class LinkTargetTest : public BasicFixture
{
 public:
  LinkTargetTest()
  {
    h5file = hdf5::file::create("LinkTargetTest.h5",
                                hdf5::file::AccessFlags::TRUNCATE);
    root_group = h5file.root();

    hdf5::node::Group(root_group, "original");
    hdf5::node::link("/original", root_group, "internal_link");

    hdf5::file::File f = hdf5::file::create("LinkTargetTestExternal.h5", hdf5::file::AccessFlags::TRUNCATE);
    hdf5::node::Group(f.root(), "external_group");

    hdf5::node::link("LinkTargetTestExternal.h5", "/external_group", root_group, "external_link");
  }

 protected:
  hdf5::file::File h5file;
  hdf5::node::Group root_group;
};

TEST_F(LinkTargetTest, default_construction)
{
  node::LinkTarget target;

  EXPECT_EQ(target.object_path().size(), 0ul);
  EXPECT_EQ(get_path_size(target.file_path()), 0ul);

}

TEST_F(LinkTargetTest, internal_target_construction)
{
  node::LinkTarget target(hdf5::Path("/data"));
  EXPECT_EQ(target.object_path(), hdf5::Path("/data"));
  EXPECT_EQ(get_path_size(target.file_path()), 0ul);
}

TEST_F(LinkTargetTest, external_target_construction)
{
  hdf5::Path object_path("/entry/data");
  boost::filesystem::path file_path("test.h5");
  node::LinkTarget target(object_path, file_path);

  EXPECT_EQ(target.object_path(), object_path);
  EXPECT_EQ(target.file_path(), file_path);
}

TEST_F(LinkTargetTest, hard_link_target)
{
  hdf5::node::Link link = root_group.links["original"];
  EXPECT_TRUE(link.is_resolvable());
  EXPECT_EQ(link.type(), hdf5::node::LinkType::HARD);

  hdf5::node::LinkTarget target = link.target();
  EXPECT_EQ(target.object_path(), "/original");
  EXPECT_EQ(get_path_size(target.file_path()), 0ul);
}

TEST_F(LinkTargetTest, internal_link_target)
{
  hdf5::node::Link link = root_group.links["internal_link"];
  EXPECT_TRUE(link.is_resolvable());

  hdf5::node::LinkTarget target = link.target();
  EXPECT_EQ(target.object_path(), "/original");
  EXPECT_EQ(get_path_size(target.file_path()), 0ul);
}

TEST_F(LinkTargetTest, external_link_target)
{
  hdf5::node::Link link = root_group.links["external_link"];
  EXPECT_TRUE(link.is_resolvable());

  hdf5::node::LinkTarget target = link.target();
  EXPECT_EQ(target.object_path(), "/external_group");
  EXPECT_EQ(target.file_path(), "LinkTargetTestExternal.h5");
}



