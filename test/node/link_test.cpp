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

class Link : public BasicFixture {
};

TEST_F(Link, test_default_construction)
{
  node::Link link;
  EXPECT_EQ(link.type(),node::LinkType::ERROR);
}

TEST_F(Link, test_equality)
{
  node::Link link1(file_, "path1", "name1");
  node::Link link2(file_, "path1", "name1");
  node::Link link3(file_, "path2", "name2");

  EXPECT_EQ(link1, link2);
  EXPECT_NE(link1, link3);
}

TEST_F(Link, test_validity)
{
  node::Link link1(file_, "path1", "name1");

  EXPECT_FALSE(link1.exists());
  EXPECT_FALSE(link1.is_resolvable());
}

