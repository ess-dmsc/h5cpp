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
// Created on: Aug 24, 2017
//
#include <gtest/gtest.h>
#include <h5cpp/path.hpp>

TEST(PathTest,test_default_construction)
{
  hdf5::Path p;
  EXPECT_EQ(p.size(),0);
  EXPECT_TRUE(!p.is_absolute_path());

}

TEST(PathTest,test_construction_from_string)
{
  hdf5::Path p("/hello/world/data");
  EXPECT_EQ(p.size(),3);
  EXPECT_TRUE(p.is_absolute_path());

  p = hdf5::Path("hello/world");
  EXPECT_EQ(p.size(),2);
  EXPECT_TRUE(!p.is_absolute_path());

  p = hdf5::Path("hello/world/instrument/data/");
  EXPECT_EQ(p.size(),4);
  EXPECT_TRUE(!p.is_absolute_path());
}

TEST(PathTest,test_conversion_to_string)
{
  hdf5::Path p("/hello/world/data");
  EXPECT_EQ(static_cast<std::string>(p),"/hello/world/data");

  p = hdf5::Path("hello/world");
  EXPECT_EQ(static_cast<std::string>(p),"hello/world");

  p = hdf5::Path("hello/world/instrument/data/");
  EXPECT_EQ(static_cast<std::string>(p),"hello/world/instrument/data");
}

TEST(PathTest,test_conversion_from_list)
{
  std::list<std::string> l{"entry","instrument","detector"};
  hdf5::Path p;
  std::copy(l.begin(),l.end(),std::back_inserter(p));
  EXPECT_EQ(p.size(),3);
  EXPECT_EQ(static_cast<std::string>(p),"entry/instrument/detector");
}

TEST(PathTest,test_append_link_name)
{
  hdf5::Path p("/entry/instrument/detector");
  p = p+"data";
  EXPECT_EQ(static_cast<std::string>(p),"/entry/instrument/detector/data");
  EXPECT_EQ(p.size(),4);
  EXPECT_TRUE(p.is_absolute_path());

  p = hdf5::Path("instrument/detector");
  p = p + "metadata/date";
  EXPECT_EQ(static_cast<std::string>(p),"instrument/detector/metadata/date");
  EXPECT_EQ(p.size(),4);
  EXPECT_TRUE(!p.is_absolute_path());
}

TEST(PathTest,test_prepend_link_name)
{
  hdf5::Path p("instrument/detector");
  p = "/entry" + p;
  EXPECT_EQ(static_cast<std::string>(p),"/entry/instrument/detector");
  EXPECT_TRUE(p.is_absolute_path());

  p = hdf5::Path("detector/data");
  p = "/entry/instrument/" + p;
  EXPECT_EQ(static_cast<std::string>(p),"/entry/instrument/detector/data");
  EXPECT_TRUE(p.is_absolute_path());

  p = hdf5::Path("entry/instrument");
  p = "/" + p;
  EXPECT_EQ(p.size(),2);
  EXPECT_TRUE(p.is_absolute_path());
}

TEST(PathTest,test_adding_two_paths)
{
  hdf5::Path p1("/entry/instrument"), p2("detector/data");
  hdf5::Path p = p1+p2;
  EXPECT_EQ(p.size(),4);
  EXPECT_TRUE(p.is_absolute_path());
  EXPECT_EQ(static_cast<std::string>(p),"/entry/instrument/detector/data");
}

TEST(PathTest,test_root_path)
{
  hdf5::Path p("/");
  EXPECT_TRUE(p.is_root());
  EXPECT_TRUE(p.is_absolute_path());
  EXPECT_EQ(static_cast<std::string>(p),"/");
}

TEST(PathTest,test_front)
{
  hdf5::Path p("/hello/world");
  EXPECT_EQ(p.front(),"hello");

  p = hdf5::Path("/");
  EXPECT_TRUE(p.is_root());
  EXPECT_EQ(p.front(),"/");
}

TEST(PathTest,test_back)
{
  hdf5::Path p("hello/world");
  EXPECT_EQ(p.back(),"world");

  p = hdf5::Path("/");
  EXPECT_TRUE(p.is_root());
  EXPECT_EQ(p.back(),"/");
}

TEST(PathTest,test_object_name)
{
  hdf5::Path p("hello/world");
  EXPECT_EQ(hdf5::Path::object_name(p),"world");

  p = hdf5::Path("/");
  EXPECT_TRUE(p.is_root());
  EXPECT_EQ(hdf5::Path::object_name(p),"/");
}

TEST(PathTest,test_parent_path)
{
  hdf5::Path p("hello/world");
  EXPECT_EQ(static_cast<std::string>(hdf5::Path::parent_path(p)),"hello");

  p = hdf5::Path("/");
  EXPECT_TRUE(p.is_root());
  EXPECT_EQ(static_cast<std::string>(hdf5::Path::parent_path(p)),"/");
}

TEST(PathTest,test_path_equality)
{
  hdf5::Path p1("hello/world");
  hdf5::Path p2("/hello/world");
  hdf5::Path p3("/hello");
  EXPECT_TRUE(p1 == p1);
  EXPECT_TRUE(p1 != p2);
  EXPECT_TRUE(p2 != p3);
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
