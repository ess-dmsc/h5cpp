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
#include <h5cpp/property/link_creation.hpp>
#include <h5cpp/property/property_class.hpp>
#include <h5cpp/datatype/types.hpp>

namespace pl = hdf5::property;
namespace tp = hdf5::datatype;

TEST(LinkCreationList, test_default_construction) {
  pl::LinkCreationList lcpl;
  EXPECT_TRUE(lcpl.get_class() == pl::kLinkCreate);

  auto cl = pl::kLinkCreate;
  EXPECT_NO_THROW((pl::LinkCreationList(hdf5::ObjectHandle(H5Pcreate(static_cast<hid_t>(cl))))));

  cl = pl::kStringCreate;
  EXPECT_THROW((pl::LinkCreationList(hdf5::ObjectHandle(H5Pcreate(static_cast<hid_t>(cl))))),
               std::runtime_error);

  cl = pl::kGroupCreate;
  EXPECT_THROW((pl::LinkCreationList(hdf5::ObjectHandle(H5Pcreate(static_cast<hid_t>(cl))))),
               std::runtime_error);
}

TEST(LinkCreationList, test_intermediate_gruop_creation) {
  pl::LinkCreationList lcpl;
  EXPECT_NO_THROW(lcpl.enable_intermediate_group_creation());
  EXPECT_TRUE(lcpl.intermediate_group_creation());
  EXPECT_NO_THROW(lcpl.disable_intermediate_group_creation());

  EXPECT_FALSE(lcpl.intermediate_group_creation());

  hdf5::ObjectHandle(static_cast<hid_t>(lcpl)).close();
  EXPECT_THROW(lcpl.enable_intermediate_group_creation(), std::runtime_error);
  EXPECT_THROW(lcpl.disable_intermediate_group_creation(), std::runtime_error);
  EXPECT_THROW(lcpl.intermediate_group_creation(), std::runtime_error);
}
