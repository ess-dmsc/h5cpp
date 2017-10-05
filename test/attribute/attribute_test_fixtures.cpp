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
// Created on: Oct 5, 2017
//
#include "attribute_test_fixtures.hpp"
#include <cstdint>
#include <h5cpp/file/functions.hpp>
#include <h5cpp/property/file_creation_list.hpp>
#include <h5cpp/property/file_access_list.hpp>

using namespace hdf5;
namespace fs = boost::filesystem;

Fixture::Fixture(const fs::path &file_path):
    file(),
    root_group()

{
  property::FileCreationList fcpl;
  property::FileAccessList fapl;

  fcpl.link_creation_order(property::CreationOrder().enable_indexed());
  fapl.library_version_bounds(property::LibVersion::LATEST,
                              property::LibVersion::LATEST);

  file = file::create(file_path,file::AccessFlags::TRUNCATE,fcpl,fapl);
  root_group = file.root();
}


AttributeFixture::AttributeFixture():
    Fixture("AttributeTest.h5")
{}


AttributeIterationFixture::AttributeIterationFixture():
    Fixture("AttributeIterationTest.h5")
{
  root_group.attributes.create<int>("index");
  root_group.attributes.create<float>("elasticity",{6,6});
  root_group.attributes.create<std::uint32_t>("counter");
}
