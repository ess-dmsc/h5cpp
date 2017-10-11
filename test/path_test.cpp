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
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE testing the path implementation
#include <boost/test/unit_test.hpp>
#include <h5cpp/path.hpp>

using namespace hdf5;
using namespace std;

BOOST_AUTO_TEST_SUITE(Path_test)

BOOST_AUTO_TEST_CASE(test_default_construction)
{
  Path p;
  BOOST_CHECK_EQUAL(p.size(),0);
  BOOST_CHECK(!p.is_absolute());
}

BOOST_AUTO_TEST_CASE(test_construction_from_string)
{
  Path p;

  p = Path("/hello/world/data");
  BOOST_CHECK_EQUAL(p.size(),3);
  BOOST_CHECK(p.is_absolute());

  p = Path("hello/world");
  BOOST_CHECK_EQUAL(p.size(),2);
  BOOST_CHECK(!p.is_absolute());

  p = Path("hello/world/instrument/data/");
  BOOST_CHECK_EQUAL(p.size(),4);
  BOOST_CHECK(!p.is_absolute());

  p = Path(".");
  BOOST_CHECK_EQUAL(p.size(),0);
  BOOST_CHECK(!p.is_absolute());

  p = Path("./");
  BOOST_CHECK_EQUAL(p.size(),0);
  BOOST_CHECK(!p.is_absolute());

  p = Path("/.");
  BOOST_CHECK_EQUAL(p.size(),0);
  BOOST_CHECK(p.is_absolute());
}

BOOST_AUTO_TEST_CASE(test_conversion_to_string)
{
  Path p;

  p = Path("/hello/world/data");
  BOOST_CHECK_EQUAL(static_cast<string>(p),"/hello/world/data");

  p = Path("hello/world");
  BOOST_CHECK_EQUAL(static_cast<string>(p),"hello/world");

  p = Path("hello/world/instrument/data/");
  BOOST_CHECK_EQUAL(static_cast<string>(p),"hello/world/instrument/data");

  p = Path(".");
  BOOST_CHECK_EQUAL(static_cast<string>(p),".");

  p = Path("");
  BOOST_CHECK_EQUAL(static_cast<string>(p),".");
}

BOOST_AUTO_TEST_CASE(test_sanitization)
{
  Path p;

  p = Path("./hello/world");
  BOOST_CHECK_EQUAL(static_cast<string>(p),"hello/world");

  p = Path("hello/world/.");
  BOOST_CHECK_EQUAL(static_cast<string>(p),"hello/world");

  p = Path("hello/./world");
  BOOST_CHECK_EQUAL(static_cast<string>(p),"hello/world");

  p = Path("s p a c e y/  ");
  BOOST_CHECK_EQUAL(static_cast<string>(p),"s p a c e y/  ");

  p = Path("d.o.t.s/...");
  BOOST_CHECK_EQUAL(static_cast<string>(p),"d.o.t.s/...");
}


BOOST_AUTO_TEST_CASE(test_conversion_from_list)
{
  list<string> l{"entry","instrument","detector"};
  Path p;
  copy(l.begin(),l.end(),back_inserter(p));
  BOOST_CHECK_EQUAL(p.size(),3);
  BOOST_CHECK_EQUAL(static_cast<string>(p),"entry/instrument/detector");
}

BOOST_AUTO_TEST_CASE(test_append_link_name)
{
  Path p("/entry/instrument/detector");
  p = p+"data";
  BOOST_CHECK_EQUAL(static_cast<string>(p),"/entry/instrument/detector/data");
  BOOST_CHECK_EQUAL(p.size(),4);
  BOOST_CHECK(p.is_absolute());

  p = Path("instrument/detector");
  p = p + "metadata/date";
  BOOST_CHECK_EQUAL(static_cast<string>(p),"instrument/detector/metadata/date");
  BOOST_CHECK_EQUAL(p.size(),4);
  BOOST_CHECK(!p.is_absolute());
}

BOOST_AUTO_TEST_CASE(test_prepend_link_name)
{
  Path p("instrument/detector");
  p = "/entry" + p;
  BOOST_CHECK_EQUAL(static_cast<string>(p),"/entry/instrument/detector");
  BOOST_CHECK(p.is_absolute());

  p = Path("detector/data");
  p = "/entry/instrument/" + p;
  BOOST_CHECK_EQUAL(static_cast<string>(p),"/entry/instrument/detector/data");
  BOOST_CHECK(p.is_absolute());

  p = Path("entry/instrument");
  p = "/" + p;
  BOOST_CHECK_EQUAL(p.size(),2);
  BOOST_CHECK(p.is_absolute());
}

BOOST_AUTO_TEST_CASE(test_adding_two_paths)
{
  Path p1("/entry/instrument"), p2("detector/data");
  Path p = p1+p2;
  BOOST_CHECK_EQUAL(p.size(),4);
  BOOST_CHECK(p.is_absolute());
  BOOST_CHECK_EQUAL(static_cast<string>(p),"/entry/instrument/detector/data");
}

BOOST_AUTO_TEST_CASE(test_root_path)
{
  Path p("/");
  BOOST_CHECK(p.is_root());
  BOOST_CHECK(p.is_absolute());
  BOOST_CHECK_EQUAL(static_cast<string>(p),"/");
}

BOOST_AUTO_TEST_CASE(test_front)
{
  Path p("/hello/world");
  BOOST_CHECK_EQUAL(p.front(),"hello");

  p = Path("/");
  BOOST_CHECK(p.is_root());
  BOOST_CHECK_EQUAL(p.front(),"/");
}

BOOST_AUTO_TEST_CASE(test_back)
{
  Path p("hello/world");
  BOOST_CHECK_EQUAL(p.back(),"world");

  p = Path("/");
  BOOST_CHECK(p.is_root());
  BOOST_CHECK_EQUAL(p.back(),"/");
}

BOOST_AUTO_TEST_CASE(test_object_name)
{
  Path p("hello/world");
  BOOST_CHECK_EQUAL(p.name(),"world");

  p = Path("/");
  BOOST_CHECK(p.is_root());
  BOOST_CHECK_EQUAL(p.name(),".");
}

BOOST_AUTO_TEST_CASE(test_parent_path)
{
  Path p("hello/world");
  BOOST_CHECK_EQUAL(static_cast<string>(p.parent()),"hello");

  p = Path("/hello/world");
  BOOST_CHECK_EQUAL(static_cast<string>(p.parent()),"/hello");

  p = Path("/");
  BOOST_CHECK(p.is_root());
  BOOST_CHECK_EQUAL(static_cast<string>(p.parent()),"/");
}

BOOST_AUTO_TEST_CASE(test_path_equality)
{
  Path p1("hello/world");
  Path p2("/hello/world");
  Path p3("/hello");
  BOOST_CHECK(p1 == p1);
  BOOST_CHECK(p1 != p2);
  BOOST_CHECK(p2 != p3);
}

BOOST_AUTO_TEST_SUITE_END()
