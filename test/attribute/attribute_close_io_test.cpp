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
// Author: Jan Kotanski <jan.kotanski@desy.de>
// Created on: Jun 19, 2018
//
#include <gtest/gtest.h>
#include <h5cpp/hdf5.hpp>
#include <string>

using namespace hdf5;

class AttributeCloseIO  : public testing::Test
{};

TEST_F(AttributeCloseIO, test_closeattr_close)
{
  auto nexus_file = file::create("AttributeCloseIO.h5",
				 file::AccessFlags::TRUNCATE);
  std::string hdf5_version =  "1.0.0";
  auto type = datatype::create<std::string>();
  dataspace::Scalar space;

  auto r1 = nexus_file.root();
  r1.attributes.create("HDF5_version", type, space).write(hdf5_version);

  // without this line works
  r1.close();

  nexus_file.close();

  auto file2 = hdf5::file::open("AttributeCloseIO.h5",
				hdf5::file::AccessFlags::READONLY);
  auto r2 = file2.root();

  //  { // with this bracket works
  auto attr = r2.attributes[0];
  std::cout << attr.name() << std::endl;
  attr.close(); // does not help
  // } // with this bracket works

  r2.close();
  file2.close();

  auto file3 = hdf5::file::open("AttributeCloseIO.h5",
				hdf5::file::AccessFlags::READWRITE);
  file3.close();
}

TEST_F(AttributeCloseIO, test_closeattr_withoutclose)
{
  auto nexus_file = file::create("AttributeCloseIO.h5",
				       file::AccessFlags::TRUNCATE);
  std::string hdf5_version =  "1.0.0";
  auto type = datatype::create<std::string>();
  dataspace::Scalar space;

  auto r1 = nexus_file.root();
  r1.attributes.create("HDF5_version", type, space).write(hdf5_version);

  // without this line works
  r1.close();
  nexus_file.close();

  auto file2 = hdf5::file::open("AttributeCloseIO.h5",
				hdf5::file::AccessFlags::READONLY);
  auto r2 = file2.root();

  //  { // with this bracket works

  auto attr = r2.attributes[0];
  std::cout << attr.name() << std::endl;
  // attr.close(); // does not help
  // } // with this bracket works

  r2.close();
  file2.close();


  auto file3 = hdf5::file::open("AttributeCloseIO.h5",
				hdf5::file::AccessFlags::READWRITE);

  file3.close();
}

TEST_F(AttributeCloseIO, test_closeattr_bracket)
{
  auto nexus_file = file::create("AttributeCloseIO.h5",
				       file::AccessFlags::TRUNCATE);
  std::string hdf5_version =  "1.0.0";
  auto type = datatype::create<std::string>();
  dataspace::Scalar space;

  auto r1 = nexus_file.root();
  r1.attributes.create("HDF5_version", type, space).write(hdf5_version);
  r1.close();
  nexus_file.close();

  auto file2 = hdf5::file::open("AttributeCloseIO.h5",
				hdf5::file::AccessFlags::READONLY);
  auto r2 = file2.root();

  { // with this bracket works

    auto attr = r2.attributes[0];
    std::cout << attr.name() << std::endl;
  } // with this bracket works

  r2.close();
  file2.close();

  auto file3 = hdf5::file::open("AttributeCloseIO.h5",
				hdf5::file::AccessFlags::READWRITE);

  file3.close();
}


TEST_F(AttributeCloseIO, test_closeattr_bracketclose)
{
  {
    auto nexus_file = file::create("AttributeCloseIO.h5",
				   file::AccessFlags::TRUNCATE);
    std::string hdf5_version =  "1.0.0";
    auto type = datatype::create<std::string>();
    dataspace::Scalar space;


    auto r1 = nexus_file.root();
    r1.attributes.create("HDF5_version", type, space).write(hdf5_version);

    nexus_file.close();
  }


  auto file2 = hdf5::file::open("AttributeCloseIO.h5",
				hdf5::file::AccessFlags::READONLY);
  auto r2 = file2.root();

  //  { // with this bracket works
  auto attr = r2.attributes[0];
  std::cout << attr.name() << std::endl;
  attr.close(); // does not help
  // } // with this bracket works

  r2.close();
  file2.close();

  auto file3 = hdf5::file::open("AttributeCloseIO.h5",
				hdf5::file::AccessFlags::READWRITE);

  file3.close();
}
