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
//   Eugen Wintersberger <eugen.wintersberger@desy.de>
//   Martin Shetty <martin.shetty@esss.se>
// Created on: Aug 21, 2017
//

#include <gtest/gtest.h>
#include <h5cpp/property/link_access.hpp>
#include <h5cpp/property/property_class.hpp>

namespace pl = hdf5::property;

TEST(LinkAccessList, test_default_construction) {
  pl::LinkAccessList lapl;
  EXPECT_TRUE(lapl.get_class() == pl::kLinkAccess);

  auto cl = pl::kGroupAccess;
  EXPECT_NO_THROW((pl::LinkAccessList(hdf5::ObjectHandle(H5Pcreate(static_cast<hid_t>(cl))))));

  cl = pl::kGroupCreate;
  EXPECT_THROW((pl::LinkAccessList(hdf5::ObjectHandle(H5Pcreate(static_cast<hid_t>(cl))))),
               std::runtime_error);
}

TEST(LinkAccessList, test_maximum_link_traversal) {
  pl::LinkAccessList lapl;
  EXPECT_NO_THROW(lapl.maximum_link_traversals(1000));
  EXPECT_EQ(lapl.maximum_link_traversals(), 1000ul);

  EXPECT_NO_THROW(lapl.maximum_link_traversals(2000));
  EXPECT_EQ(lapl.maximum_link_traversals(), 2000ul);

  hdf5::ObjectHandle(static_cast<hid_t>(lapl)).close();
  EXPECT_THROW(lapl.maximum_link_traversals(2000), std::runtime_error);
  EXPECT_THROW(lapl.maximum_link_traversals(), std::runtime_error);
}

TEST(LinkAccessList, test_external_link_prefix) {
  pl::LinkAccessList lapl;
  EXPECT_NO_THROW(lapl.external_link_prefix("/home/wintersb"));
#ifndef _MSC_VER
  EXPECT_EQ(lapl.external_link_prefix().string(), "/home/wintersb");
#endif

  hdf5::ObjectHandle(static_cast<hid_t>(lapl)).close();
  EXPECT_THROW(lapl.external_link_prefix("/home/wintersb"), std::runtime_error);
}
