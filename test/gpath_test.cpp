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

TEST(PathTests, test_default_construction)
{
  hdf5::Path p;
  ASSERT_EQ(p.size(),0);
  ASSERT_TRUE(!p.is_absolute_path());

}

TEST(PathTests, test_construction_from_string)
{
  hdf5::Path p("/hello/world/data");
  ASSERT_EQ(p.size(),3);
  ASSERT_TRUE(p.is_absolute_path());

  p = hdf5::Path("hello/world");
  ASSERT_EQ(p.size(),2);
  ASSERT_TRUE(!p.is_absolute_path());

  p = hdf5::Path("hello/world/instrument/data/");
  ASSERT_EQ(p.size(),4);
  ASSERT_TRUE(!p.is_absolute_path());
}

TEST(PathTests, test_conversion_to_string)
{
  hdf5::Path p("/hello/world/data");
  ASSERT_EQ(static_cast<std::string>(p),"/hello/world/data");

  p = hdf5::Path("hello/world");
  ASSERT_EQ(static_cast<std::string>(p),"hello/world");

  p = hdf5::Path("hello/world/instrument/data/");
  ASSERT_EQ(static_cast<std::string>(p),"hello/world/instrument/data");
}

TEST(PathTests, test_conversion_from_list)
{
  std::list<std::string> l{"entry","instrument","detector"};
  hdf5::Path p;
  std::copy(l.begin(),l.end(),std::back_inserter(p));
  ASSERT_EQ(p.size(),3);
  ASSERT_EQ(static_cast<std::string>(p),"entry/instrument/detector");
}

TEST(PathTests, test_append_link_name)
{
  hdf5::Path p("/entry/instrument/detector");
  p = p+"data";
  ASSERT_EQ(static_cast<std::string>(p),"/entry/instrument/detector/data");
  ASSERT_EQ(p.size(),4);
  ASSERT_TRUE(p.is_absolute_path());

  p = hdf5::Path("instrument/detector");
  p = p + "metadata/date";
  ASSERT_EQ(static_cast<std::string>(p),"instrument/detector/metadata/date");
  ASSERT_EQ(p.size(),4);
  ASSERT_TRUE(!p.is_absolute_path());
}

TEST(PathTests, test_prepend_link_name)
{
  hdf5::Path p("instrument/detector");
  p = "/entry" + p;
  ASSERT_EQ(static_cast<std::string>(p),"/entry/instrument/detector");
  ASSERT_TRUE(p.is_absolute_path());

  p = hdf5::Path("detector/data");
  p = "/entry/instrument/" + p;
  ASSERT_EQ(static_cast<std::string>(p),"/entry/instrument/detector/data");
  ASSERT_TRUE(p.is_absolute_path());

  p = hdf5::Path("entry/instrument");
  p = "/" + p;
  ASSERT_EQ(p.size(),2);
  ASSERT_TRUE(p.is_absolute_path());
}

TEST(PathTests, test_adding_two_paths)
{
  hdf5::Path p1("/entry/instrument"), p2("detector/data");
  hdf5::Path p = p1+p2;
  ASSERT_EQ(p.size(),4);
  ASSERT_TRUE(p.is_absolute_path());
  ASSERT_EQ(static_cast<std::string>(p),"/entry/instrument/detector/data");
}

TEST(PathTests, test_root_path)
{
  hdf5::Path p("/");
  ASSERT_TRUE(p.is_root());
  ASSERT_TRUE(p.is_absolute_path());
  ASSERT_EQ(static_cast<std::string>(p),"/");
}

TEST(PathTests, test_front)
{
  hdf5::Path p("/hello/world");
  ASSERT_EQ(p.front(),"hello");

  p = hdf5::Path("/");
  ASSERT_TRUE(p.is_root());
  ASSERT_EQ(p.front(),"/");
}

TEST(PathTests, test_back)
{
  hdf5::Path p("hello/world");
  ASSERT_EQ(p.back(),"world");

  p = hdf5::Path("/");
  ASSERT_TRUE(p.is_root());
  ASSERT_EQ(p.back(),"/");
}

TEST(PathTests, test_object_name)
{
  hdf5::Path p("hello/world");
  ASSERT_EQ(hdf5::Path::object_name(p),"world");

  p = hdf5::Path("/");
  ASSERT_TRUE(p.is_root());
  ASSERT_EQ(hdf5::Path::object_name(p),"/");
}

TEST(PathTests, test_parent_path)
{
  hdf5::Path p("hello/world");
  ASSERT_EQ(static_cast<std::string>(hdf5::Path::parent_path(p)),"hello");

  p = hdf5::Path("/");
  ASSERT_TRUE(p.is_root());
  ASSERT_EQ(static_cast<std::string>(hdf5::Path::parent_path(p)),"/");
}

TEST(PathTests, test_path_equality)
{
  hdf5::Path p1("hello/world");
  hdf5::Path p2("/hello/world");
  hdf5::Path p3("/hello");
  ASSERT_TRUE(p1 == p1);
  ASSERT_TRUE(p1 != p2);
  ASSERT_TRUE(p2 != p3);
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
