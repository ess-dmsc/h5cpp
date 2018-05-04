//
// (c) Copyright 2017 DESY,ESS
//
// This file is part of h5cpp.
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
// Created on: Aug 18, 2017
//

#include <gtest/gtest.h>
#include <h5cpp/property/string_creation.hpp>

namespace pl = hdf5::property;
namespace type = hdf5::datatype;

TEST(StringCreationList, test_default_construction) {
  pl::StringCreationList scl;
  EXPECT_TRUE(scl.get_class() == pl::kStringCreate);

  auto cl = pl::kStringCreate;
  EXPECT_NO_THROW((pl::StringCreationList(hdf5::ObjectHandle(H5Pcreate(static_cast<hid_t>(cl))))));

  cl = pl::kGroupCreate;
  EXPECT_THROW((pl::StringCreationList(hdf5::ObjectHandle(H5Pcreate(static_cast<hid_t>(cl))))),
               std::runtime_error);
}

TEST(StringCreationList, test_encoding) {
  pl::StringCreationList scl;
  EXPECT_NO_THROW(scl.character_encoding(type::CharacterEncoding::ASCII));
  EXPECT_TRUE(scl.character_encoding() == type::CharacterEncoding::ASCII);

  EXPECT_NO_THROW(scl.character_encoding(type::CharacterEncoding::UTF8));
  EXPECT_TRUE(scl.character_encoding() == type::CharacterEncoding::UTF8);

  hdf5::ObjectHandle(static_cast<hid_t>(scl)).close();
  EXPECT_THROW(scl.character_encoding(type::CharacterEncoding::UTF8), std::runtime_error);
  EXPECT_THROW(scl.character_encoding(), std::runtime_error);
}

