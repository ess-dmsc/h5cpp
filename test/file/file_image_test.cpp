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
//   Jan Kotanski <jan.kotanski@desy.de>
// Created on: Sep 10, 2017
//
#include <fstream>

#include <gtest/gtest.h>
#include <h5cpp/file/functions.hpp>
#include <h5cpp/node/group.hpp>
#include <h5cpp/core/filesystem.hpp>

using namespace hdf5;

class FileImage : public testing::Test
{
  protected:
    FileImage() {}
    virtual ~FileImage() {}

    virtual void SetUp()
    {
      for(auto filename : files_)
        fs::remove(filename);
    }

    virtual void TearDown() {}

    static const std::vector<std::string> files_;
};

const std::vector<std::string> FileImage::files_ = {
						    "./test_image.h5",
						    "./test_image_from.h5",
						    "./test_image_to.h5",
						    "./test_buffer.h5",
};

TEST_F(FileImage, test_image_from_buffer)
{
  std::string hdf5_version =  "1.0.0";
  {
    auto nexus_file = file::create("test_image_from.h5",
				   file::AccessFlags::TRUNCATE);
    auto type = datatype::create<std::string>();
    dataspace::Scalar space;

    auto r1 = nexus_file.root();
    r1.attributes.create("HDF5_version", type, space).write(hdf5_version);
  } // close all nexus_file objects

  std::ifstream fin("test_image_from.h5", std::ios::binary);
  std::vector<unsigned char> ibuffer(std::istreambuf_iterator<char>(fin), {});
  auto nexus_file2 = file::from_buffer(ibuffer);
  auto r2 = nexus_file2.root();
  EXPECT_TRUE(r2.attributes.exists("HDF5_version"));
  auto a = r2.attributes["HDF5_version"];
  std::string st;
  a.read(st);
  EXPECT_EQ(st, hdf5_version);
  a.close();
  r2.close();
  nexus_file2.close();
}


TEST_F(FileImage, test_image_to_buffer)
{
  size_t size;
  std::vector<unsigned char> obuffer;
  std::string hdf5_version =  "1.0.0";
  {
    auto nexus_file = file::create("test_image_to.h5",
				   file::AccessFlags::TRUNCATE);
    auto type = datatype::create<std::string>();
    dataspace::Scalar space;


    auto r1 = nexus_file.root();
    r1.attributes.create("HDF5_version", type, space).write(hdf5_version);
    size = nexus_file.buffer_size();
    obuffer.resize(size);
    size_t realsize = nexus_file.to_buffer(obuffer);
    EXPECT_EQ(realsize, size);
    std::ofstream fout("test_buf.h5", std::ios::out | std::ios::binary);
    fout.write(reinterpret_cast<char*>(&obuffer[0]), realsize);
    fout.close();
    nexus_file.close();
  } //close nexus_file objects

  auto file2 = hdf5::file::open("test_buf.h5",
  				hdf5::file::AccessFlags::READONLY);
  auto r2 = file2.root();

  auto a = r2.attributes["HDF5_version"];
  std::string st;
  a.read(st);
  EXPECT_EQ(st, hdf5_version);
  a.close();
  r2.close();
  file2.close();


}

TEST_F(FileImage, test_image_buffer)
{
  std::string hdf5_version =  "1.0.0";
  auto nexus_file = file::create("test_image_to.h5",
				 file::AccessFlags::TRUNCATE);
  auto type = datatype::create<std::string>();
  dataspace::Scalar space;


  auto r1 = nexus_file.root();
  r1.attributes.create("HDF5_version", type, space).write(hdf5_version);
  size_t size = nexus_file.buffer_size();
  std::vector<unsigned char> buffer(size);
  size_t realsize = nexus_file.to_buffer(buffer);
  EXPECT_EQ(realsize, size);
  nexus_file.close();

  auto file2 = file::from_buffer(buffer);
  auto r2 = file2.root();

  auto a = r2.attributes["HDF5_version"];
  std::string st;
  a.read(st);
  EXPECT_EQ(st, hdf5_version);
  a.close();
  r2.close();
  file2.close();

}

TEST_F(FileImage, test_image_buffer_flags)
{
  std::string hdf5_version =  "1.0.0";
  auto nexus_file = file::create("test_image_to.h5",
				 file::AccessFlags::TRUNCATE);
  auto type = datatype::create<std::string>();
  dataspace::Scalar space;


  auto r1 = nexus_file.root();
  r1.attributes.create("HDF5_version", type, space).write(hdf5_version);
  size_t size = nexus_file.buffer_size();
  std::vector<unsigned char> buffer(size);
  size_t realsize = nexus_file.to_buffer(buffer);
  EXPECT_EQ(realsize, size);
  nexus_file.close();
  const std::vector<unsigned char> cbuffer = buffer;
  EXPECT_THROW(file::from_buffer(buffer, file::ImageFlags::DONT_COPY),
	       std::runtime_error);
  EXPECT_THROW(file::from_buffer(cbuffer,
				 file::ImageFlags::DONT_COPY |
				 file::ImageFlags::DONT_RELEASE |
				 file::ImageFlags::READWRITE),
	       std::runtime_error);
  auto file2 = file::from_buffer(cbuffer,
				 file::ImageFlags::DONT_COPY |
				 file::ImageFlags::DONT_RELEASE);
  auto r2 = file2.root();

  auto a = r2.attributes["HDF5_version"];
  std::string st;
  a.read(st);
  EXPECT_EQ(st, hdf5_version);
  a.close();
  r2.close();
  file2.close();

}
