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
// Created on: Aug 21, 2017
//

#include <gtest/gtest.h>
#include <h5cpp/property/link_access_list.hpp>
#include <h5cpp/property/class.hpp>

namespace pl = hdf5::property;
namespace fs = boost::filesystem;

TEST(LinkAccessList, test_default_construction)
{
  pl::LinkAccessList lapl;
  EXPECT_TRUE(lapl.get_class() == pl::kLinkAccess);
}

TEST(LinkAccessList, test_maximum_link_traversal)
{
  pl::LinkAccessList lapl;
  EXPECT_NO_THROW(lapl.maximum_link_traversals(1000));
  EXPECT_EQ(lapl.maximum_link_traversals(),1000ul);

  EXPECT_NO_THROW(lapl.maximum_link_traversals(2000));
  EXPECT_EQ(lapl.maximum_link_traversals(),2000ul);
}

TEST(LinkAccessList, test_external_link_prefix)
{
  pl::LinkAccessList lapl;
  EXPECT_NO_THROW(lapl.external_link_prefix("/home/wintersb"));
  EXPECT_EQ(lapl.external_link_prefix().string(),"/home/wintersb");
}


