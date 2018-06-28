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
// Created on: Oct 09, 2017
//

#include <gtest/gtest.h>
#include <h5cpp/property/object_copy.hpp>

using namespace hdf5;

TEST(ObjectCopyClasses, test_string_representation) {
  std::stringstream stream;

  stream << property::CopyFlag::SHALLOW_HIERARCHY;
  EXPECT_EQ(stream.str(), "SHALLOW_HIERARCHY");

  stream.str(std::string());
  stream << property::CopyFlag::EXPAND_SOFT_LINKS;
  EXPECT_EQ(stream.str(), "EXPAND_SOFT_LINKS");

  stream.str(std::string());
  stream << property::CopyFlag::EXPAND_EXTERNAL_LINKS;
  EXPECT_EQ(stream.str(), "EXPAND_EXTERNAL_LINKS");

  stream.str(std::string());
  stream << property::CopyFlag::EXPAND_REFERENCES;
  EXPECT_EQ(stream.str(), "EXPAND_REFERENCES");

  stream.str(std::string());
  stream << property::CopyFlag::WITHOUT_ATTRIBUTES;
  EXPECT_EQ(stream.str(), "WITHOUT_ATTRIBUTES");

  stream.str(std::string());
  stream << property::CopyFlag::MERGE_COMMITTED_TYPES;
  EXPECT_EQ(stream.str(), "MERGE_COMMITTED_TYPES");
}

TEST(ObjectCopyClasses, test_or_operator_1) {
  property::CopyFlags flags = property::CopyFlag::SHALLOW_HIERARCHY |
      property::CopyFlag::EXPAND_SOFT_LINKS;
  EXPECT_TRUE(flags.shallow_hierarchy());
  EXPECT_TRUE(flags.expand_soft_links());
  EXPECT_FALSE(flags.expand_external_links());
  EXPECT_FALSE(flags.expand_references());
  EXPECT_FALSE(flags.without_attributes());
  EXPECT_FALSE(flags.merge_committed_types());
}

TEST(ObjectCopyClasses, test_or_operator_2) {
  property::CopyFlags flags = property::CopyFlag::EXPAND_SOFT_LINKS |
      property::CopyFlag::EXPAND_EXTERNAL_LINKS;

  EXPECT_FALSE(flags.shallow_hierarchy());
  EXPECT_TRUE(flags.expand_soft_links());
  EXPECT_TRUE(flags.expand_external_links());
  EXPECT_FALSE(flags.expand_references());
  EXPECT_FALSE(flags.without_attributes());
  EXPECT_FALSE(flags.merge_committed_types());
}

TEST(ObjectCopyClasses, test_or_operator_3) {
  property::CopyFlags flags = property::CopyFlag::EXPAND_EXTERNAL_LINKS |
      property::CopyFlag::EXPAND_REFERENCES;

  EXPECT_FALSE(flags.shallow_hierarchy());
  EXPECT_FALSE(flags.expand_soft_links());
  EXPECT_TRUE(flags.expand_external_links());
  EXPECT_TRUE(flags.expand_references());
  EXPECT_FALSE(flags.without_attributes());
  EXPECT_FALSE(flags.merge_committed_types());
}

TEST(ObjectCopyClasses, test_or_operator_4) {
  property::CopyFlags flags = property::CopyFlag::EXPAND_REFERENCES |
      property::CopyFlag::WITHOUT_ATTRIBUTES;

  EXPECT_FALSE(flags.shallow_hierarchy());
  EXPECT_FALSE(flags.expand_soft_links());
  EXPECT_FALSE(flags.expand_external_links());
  EXPECT_TRUE(flags.expand_references());
  EXPECT_TRUE(flags.without_attributes());
  EXPECT_FALSE(flags.merge_committed_types());
}

TEST(ObjectCopyClasses, test_or_operator_5) {
  property::CopyFlags flags = property::CopyFlag::WITHOUT_ATTRIBUTES |
      property::CopyFlag::MERGE_COMMITTED_TYPES;

  EXPECT_FALSE(flags.shallow_hierarchy());
  EXPECT_FALSE(flags.expand_soft_links());
  EXPECT_FALSE(flags.expand_external_links());
  EXPECT_FALSE(flags.expand_references());
  EXPECT_TRUE(flags.without_attributes());
  EXPECT_TRUE(flags.merge_committed_types());
}

TEST(ObjectCopyClasses, test_or_operator_6) {
  property::CopyFlags flags = property::CopyFlag::MERGE_COMMITTED_TYPES |
      property::CopyFlag::SHALLOW_HIERARCHY;

  EXPECT_TRUE(flags.shallow_hierarchy());
  EXPECT_FALSE(flags.expand_soft_links());
  EXPECT_FALSE(flags.expand_external_links());
  EXPECT_FALSE(flags.expand_references());
  EXPECT_FALSE(flags.without_attributes());
  EXPECT_TRUE(flags.merge_committed_types());
}



//=============================================================================
// test suite for the CopyFlags class
//=============================================================================

TEST(CopyFlags, test_default_construction) {
  property::CopyFlags flags;
  EXPECT_FALSE(flags.shallow_hierarchy());
  EXPECT_FALSE(flags.expand_soft_links());
  EXPECT_FALSE(flags.expand_external_links());
  EXPECT_FALSE(flags.expand_references());
  EXPECT_FALSE(flags.without_attributes());
  EXPECT_FALSE(flags.merge_committed_types());
}

TEST(CopyFlags, test_shallow_hierarchy) {
  property::CopyFlags flags;
  flags.expand_soft_links(true);
  EXPECT_TRUE(flags.expand_soft_links());
  flags.expand_soft_links(false);
  EXPECT_FALSE(flags.expand_soft_links());
}

TEST(CopyFlags, test_expand_soft_links) {
  property::CopyFlags flags;
  flags.expand_soft_links(true);
  EXPECT_TRUE(flags.expand_soft_links());
  flags.expand_soft_links(false);
  EXPECT_FALSE(flags.expand_soft_links());
}

TEST(CopyFlags, test_expand_external_links) {
  property::CopyFlags flags;
  flags.expand_external_links(true);
  EXPECT_TRUE(flags.expand_external_links());
  flags.expand_external_links(false);
  EXPECT_FALSE(flags.expand_external_links());
}

TEST(CopyFlags, test_expand_references) {
  property::CopyFlags flags;
  flags.expand_references(true);
  EXPECT_TRUE(flags.expand_references());
  flags.expand_references(false);
  EXPECT_FALSE(flags.expand_references());
}

TEST(CopyFlags, test_without_attributes) {
  property::CopyFlags flags;
  flags.without_attributes(true);
  EXPECT_TRUE(flags.without_attributes());
  flags.without_attributes(false);
  EXPECT_FALSE(flags.without_attributes());
}

TEST(CopyFlags, test_merge_committed_types) {
  property::CopyFlags flags;
  flags.merge_committed_types(true);
  EXPECT_TRUE(flags.merge_committed_types());
  flags.merge_committed_types(false);
  EXPECT_FALSE(flags.merge_committed_types());
}

TEST(CopyFlags, test_unary_or_1) {
  property::CopyFlags flags;
  flags |= property::CopyFlag::EXPAND_EXTERNAL_LINKS;
  EXPECT_TRUE(flags.expand_external_links());
}

TEST(CopyFlags, test_or_operations_1) {
  property::CopyFlags flags = property::CopyFlag::EXPAND_EXTERNAL_LINKS |
      property::CopyFlag::EXPAND_SOFT_LINKS |
      property::CopyFlag::WITHOUT_ATTRIBUTES;
  EXPECT_TRUE(flags.without_attributes());
  EXPECT_TRUE(flags.expand_soft_links());
  EXPECT_TRUE(flags.expand_external_links());
}

TEST(ObjectCopy, construction) {
  property::ObjectCopyList ocpl;
  EXPECT_TRUE(ocpl.get_class() == property::kObjectCopy);

  auto cl = property::kObjectCopy;
  EXPECT_NO_THROW((property::ObjectCopyList(hdf5::ObjectHandle(H5Pcreate(static_cast<hid_t>(cl))))));

  cl = property::kGroupCreate;
  EXPECT_THROW((property::ObjectCopyList(hdf5::ObjectHandle(H5Pcreate(static_cast<hid_t>(cl))))),
               std::runtime_error);
}

TEST(ObjectCopy, set_flags) {
  property::CopyFlags flags = property::CopyFlag::EXPAND_SOFT_LINKS |
      property::CopyFlag::EXPAND_EXTERNAL_LINKS;
  property::ObjectCopyList ocpl;
  EXPECT_NO_THROW(ocpl.flags(flags));
  EXPECT_TRUE(ocpl.flags().expand_soft_links());
  EXPECT_NO_THROW(ocpl.flags(property::CopyFlag::EXPAND_EXTERNAL_LINKS));
  EXPECT_TRUE(ocpl.flags().expand_external_links());

  hdf5::ObjectHandle(static_cast<hid_t>(ocpl)).close();
  EXPECT_THROW(ocpl.flags(flags), std::runtime_error);
  EXPECT_THROW(ocpl.flags(), std::runtime_error);
  EXPECT_THROW(ocpl.flags(property::CopyFlag::EXPAND_EXTERNAL_LINKS), std::runtime_error);

}