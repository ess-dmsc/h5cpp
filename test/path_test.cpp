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
// Authors:
//    Eugen Wintersberger <eugen.wintersberger@desy.de>
//    Martin Shetty <martin.shetty@esss.se>
// Created on: Aug 24, 2017
//
#include <gtest/gtest.h>
#include <h5cpp/path.hpp>

using namespace hdf5;
using namespace std;

TEST(Path, test_default_construction)
{
  Path p;
  EXPECT_EQ(p.size(),0);
  EXPECT_FALSE(p.is_absolute());
}

TEST(Path, test_construction_from_string)
{
  Path p;

  p = Path("/hello/world/data");
  EXPECT_EQ(p.size(),3);
  EXPECT_TRUE(p.is_absolute());

  p = Path("hello/world");
  EXPECT_EQ(p.size(),2);
  EXPECT_FALSE(p.is_absolute());

  p = Path("hello/world/instrument/data/");
  EXPECT_EQ(p.size(),4);
  EXPECT_FALSE(p.is_absolute());

  p = Path(".");
  EXPECT_EQ(p.size(),0);
  EXPECT_FALSE(p.is_absolute());

  p = Path("./");
  EXPECT_EQ(p.size(),0);
  EXPECT_FALSE(p.is_absolute());

  p = Path("/.");
  EXPECT_EQ(p.size(),0);
  EXPECT_TRUE(p.is_absolute());

  p = Path(".///");
  EXPECT_EQ(p.size(),0);
  EXPECT_FALSE(p.is_absolute());
}

TEST(Path, test_conversion_to_string)
{
  Path p;

  p = Path("/hello/world/data");
  EXPECT_EQ(static_cast<string>(p),"/hello/world/data");

  p = Path("hello/world");
  EXPECT_EQ(static_cast<string>(p),"hello/world");

  p = Path("hello/world/instrument/data/");
  EXPECT_EQ(static_cast<string>(p),"hello/world/instrument/data");

  p = Path(".");
  EXPECT_EQ(static_cast<string>(p),".");

  p = Path("");
  EXPECT_EQ(static_cast<string>(p),".");
}

TEST(Path, test_sanitization)
{
  Path p;

  p = Path("./hello");
  EXPECT_EQ(static_cast<string>(p),"hello");

  p = Path("hello/world/.");
  EXPECT_EQ(static_cast<string>(p),"hello/world");

  p = Path("hello/./world");
  EXPECT_EQ(static_cast<string>(p),"hello/world");

  p = Path(".././../world");
  EXPECT_EQ(static_cast<string>(p),"../../world");

  p = Path("hello/..");
  EXPECT_EQ(static_cast<string>(p),".");

  p = Path("hello/../world");
  EXPECT_EQ(static_cast<string>(p),"world");

  p = Path("hello/world/!/../..");
  EXPECT_EQ(static_cast<string>(p),"hello");

  p = Path("hello/world/../../../..");
  EXPECT_EQ(static_cast<string>(p),"../..");

  p = Path("/hello/world/../../../..");
  EXPECT_EQ(static_cast<string>(p),"../..");
}

TEST(Path, relative_to)
{
  Path p1("a/b/c/d/e");
  Path p2("a/b/c/x/y");
  auto p = p1.relative_to(p2);
  EXPECT_EQ(static_cast<string>(p),"../../d/e");
}

TEST(Path, test_conversion_from_list)
{
  list<string> l{"entry","instrument","detector"};
  Path p;
  copy(l.begin(),l.end(),back_inserter(p));
  EXPECT_EQ(p.size(),3);
  EXPECT_EQ(static_cast<string>(p),"entry/instrument/detector");
}

TEST(Path, test_append)
{
  Path p;

  p = Path("/entry/instrument");
  p.append(Path("detector/data"));
  EXPECT_EQ(static_cast<string>(p),"/entry/instrument/detector/data");

  p = Path("/entry/instrument");
  p.append(Path("../data"));
  EXPECT_EQ(static_cast<string>(p),"/entry/data");

  p = Path("entry/instrument");
  p.append(Path("../../.."));
  EXPECT_EQ(static_cast<string>(p),"..");

  p = Path("/entry/instrument");
  p.append(Path("../../.."));
  EXPECT_EQ(static_cast<string>(p),"..");
}

TEST(Path,test_append_link_name)
{
  Path p("/entry/instrument/detector");
  p = p+"data";
  EXPECT_EQ(static_cast<string>(p),"/entry/instrument/detector/data");
  EXPECT_EQ(p.size(),4);
  EXPECT_TRUE(p.is_absolute());

  p = Path("instrument/detector");
  p = p + "metadata/date";
  EXPECT_EQ(static_cast<string>(p),"instrument/detector/metadata/date");
  EXPECT_EQ(p.size(),4);
  EXPECT_FALSE(p.is_absolute());
}

TEST(Path,test_prepend_link_name)
{
  Path p("instrument/detector");
  p = "/entry" + p;
  EXPECT_EQ(static_cast<string>(p),"/entry/instrument/detector");
  EXPECT_TRUE(p.is_absolute());

  p = Path("detector/data");
  p = "/entry/instrument/" + p;
  EXPECT_EQ(static_cast<string>(p),"/entry/instrument/detector/data");
  EXPECT_TRUE(p.is_absolute());

  p = Path("entry/instrument");
  p = "/" + p;
  EXPECT_EQ(p.size(),2);
  EXPECT_TRUE(p.is_absolute());
}

TEST(Path,test_adding_two_paths)
{
  Path p1("/entry/instrument"), p2("detector/data");
  Path p = p1+p2;
  EXPECT_EQ(p.size(),4);
  EXPECT_TRUE(p.is_absolute());
  EXPECT_EQ(static_cast<string>(p),"/entry/instrument/detector/data");
}

TEST(Path,test_root_path)
{
  Path p("/");
  EXPECT_TRUE(p.is_root());
  EXPECT_TRUE(p.is_absolute());
  EXPECT_EQ(static_cast<string>(p),"/");
}

TEST(Path,test_front)
{
  Path p("/hello/world");
  EXPECT_EQ(p.front(),"hello");

  p = Path("/");
  EXPECT_TRUE(p.is_root());
  EXPECT_EQ(p.front(),"/");
}

TEST(Path,test_back)
{
  Path p("hello/world");
  EXPECT_EQ(p.back(),"world");

  p = Path("/");
  EXPECT_TRUE(p.is_root());
  EXPECT_EQ(p.back(),"/");
}

TEST(Path,test_name)
{
  Path p("hello/world");
  EXPECT_EQ(p.name(),"world");

  p = Path("/");
  EXPECT_TRUE(p.is_root());
  EXPECT_EQ(p.name(),".");
}

TEST(Path,test_parent_path)
{
  Path p("hello/world");
  EXPECT_EQ(static_cast<string>(p.parent()),"hello");

  p = Path("/hello/world");
  EXPECT_EQ(static_cast<string>(p.parent()),"/hello");

  p = Path("/");
  EXPECT_TRUE(p.is_root());
  EXPECT_EQ(static_cast<string>(p.parent()),"/");
}

TEST(Path,test_path_equality)
{
  Path p1("hello/world");
  Path p2("/hello/world");
  Path p3("/hello");
  EXPECT_TRUE(p1 == p1);
  EXPECT_TRUE(p1 != p2);
  EXPECT_TRUE(p2 != p3);
}
