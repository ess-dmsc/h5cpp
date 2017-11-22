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
// Created on: Nov 20, 2017
//
#include <gtest/gtest.h>
#include <h5cpp/hdf5.hpp>

using hdf5::node::link;
using hdf5::node::Group;
using hdf5::node::Link;
using hdf5::Path;
using hdf5::node::LinkTarget;
using hdf5::property::LinkCreationList;

class SymbolicLinkCreationTest : public testing::Test
{
  public:
    hdf5::property::LinkCreationList lcpl;
    hdf5::file::File file;

    SymbolicLinkCreationTest();
};

SymbolicLinkCreationTest::SymbolicLinkCreationTest():
    lcpl(),
    file()
{
  using hdf5::file::AccessFlags;
  file = hdf5::file::create("SymbolicLinkCreationTest.h5",AccessFlags::TRUNCATE);

  lcpl.enable_intermediate_group_creation();
}

TEST_F(SymbolicLinkCreationTest,on_same_level)
{
  Group data(file.root(),Path("data"));
  link(data,file.root(),Path("data_link"));
  Link l = file.root().links["data_link"];
  EXPECT_EQ(l.type(),hdf5::node::LinkType::SOFT);
  EXPECT_EQ(l.target().object_path(),Path("/data"));
}

TEST_F(SymbolicLinkCreationTest,on_different_level)
{
  Group data(file.root(),Path("data"));
  Group(file.root(),Path("links/datalinks"),lcpl);
  link(data,file.root(),Path("links/datalinks/new_data"));
  Link l = hdf5::node::get_node(file.root(),Path("links/datalinks/new_data")).link();
  EXPECT_EQ(l.type(),hdf5::node::LinkType::SOFT);
  EXPECT_EQ(l.target().object_path(),Path("/data"));

}
