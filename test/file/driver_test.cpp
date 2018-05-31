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
// Author: Martin Shetty <martin.shetty@esss.se>
// Created on: May 4, 2018
//

#include <gtest/gtest.h>
#include <h5cpp/file/functions.hpp>
#include <h5cpp/node/group.hpp>
#include <h5cpp/hdf5.hpp>

using namespace hdf5;
namespace fs = boost::filesystem;

TEST(MemoryDriver, create_default)
{
  file::MemoryDriver m;
  EXPECT_EQ(m.id(), file::DriverID::MEMORY);
}

TEST(MemoryDriver, create_custom)
{
  file::MemoryDriver m(7000, true);
  EXPECT_TRUE(m.backing_store());
  EXPECT_EQ(m.increment(), 7000);
}

TEST(MemoryDriver, backing_store)
{
  file::MemoryDriver m;
  EXPECT_FALSE(m.backing_store());
  m.backing_store(true);
  EXPECT_TRUE(m.backing_store());
}

TEST(MemoryDriver, increment)
{
  file::MemoryDriver m;
  EXPECT_EQ(m.increment(), 1024 * 1024);
  m.increment(5000);
  EXPECT_EQ(m.increment(), 5000);
}

TEST(MemoryDriver, apply)
{
  property::FileCreationList fcpl;
  property::FileAccessList fapl;
  file::MemoryDriver m(7000, true);
  m(fapl);
  file::create("memory_file.h5", file::AccessFlags::TRUNCATE, fcpl, fapl);

  ObjectHandle(static_cast<hid_t>(fapl)).close();
  EXPECT_THROW(m(fapl), std::runtime_error);
}


TEST(PosixDriver, create_default)
{
  file::PosixDriver m;
  EXPECT_EQ(m.id(), file::DriverID::POSIX);
}

TEST(PosixDriver, apply)
{
  property::FileCreationList fcpl;
  property::FileAccessList fapl;
  file::PosixDriver m;
  m(fapl);
  file::create("posix_file.h5", file::AccessFlags::TRUNCATE, fcpl, fapl);

  ObjectHandle(static_cast<hid_t>(fapl)).close();
  EXPECT_THROW(m(fapl), std::runtime_error);
}

#ifdef WITH_MPI

TEST(MPIDriver, create_default)
{
  file::MPIDriver m(MPI_COMM_WORLD,MPI_INFO_NULL);
  EXPECT_EQ(m.id(), file::DriverID::MPI);
}

TEST(MPIDriver, apply)
{
  property::FileCreationList fcpl;
  property::FileAccessList fapl;
  file::MPIDriver m(MPI_COMM_WORLD,MPI_INFO_NULL);
  m(fapl);
  file::create("posix_file.h5", file::AccessFlags::TRUNCATE, fcpl, fapl);

  ObjectHandle(static_cast<hid_t>(fapl)).close();
  EXPECT_THROW(m(fapl), std::runtime_error);
}

#endif
