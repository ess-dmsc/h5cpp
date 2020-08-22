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
// Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
// Created on: Sep 8, 2017
//
#include <catch2/catch.hpp>
#include <fstream>
#include <h5cpp/core/filesystem.hpp>
#include <h5cpp/file/functions.hpp>

using namespace hdf5;

SCENARIO("Testing files for being an HDF5 file") {
  GIVEN("A text file") {
    std::ofstream ofile("test.txt");
    ofile << "hello world" << std::endl;
    ofile.close();
    THEN("testing for an HDF5 file must fail") {
      REQUIRE_FALSE(file::is_hdf5_file("test.txt"));
    }
    fs::remove("test.txt");
  }

  GIVEN("an HDF5 file") {
    file::create("test.h5", file::AccessFlags::TRUNCATE);
    THEN("the test for an HDF5 file must succeed") {
      REQUIRE(file::is_hdf5_file("test.h5"));
    }
    fs::remove("test.h5");
  }

  GIVEN("a non-existing file") {
    THEN("an exception will be thrown") {
      REQUIRE_THROWS_AS(file::is_hdf5_file("nonexistent.qqq"),
                        std::runtime_error);
    }
  }
}
