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
// Created on: Aug 28, 2017
//

#include <gtest/gtest.h>
#include <h5cpp/property/dataset_transfer.hpp>
#include <h5cpp/property/property_class.hpp>

namespace pl = hdf5::property;

TEST(DatasetTransferList, test_default_construction)
{
  pl::DatasetTransferList dtpl;
  EXPECT_TRUE(dtpl.get_class() == pl::kDatasetXfer);

  auto cl = pl::kDatasetXfer;
  EXPECT_NO_THROW((pl::DatasetTransferList(hdf5::ObjectHandle(H5Pcreate(static_cast<hid_t>(cl))))));

  cl = pl::kGroupCreate;
  EXPECT_THROW((pl::DatasetTransferList(hdf5::ObjectHandle(H5Pcreate(static_cast<hid_t>(cl))))),
               std::runtime_error);
}

// Missing MPI-related functions tests here

