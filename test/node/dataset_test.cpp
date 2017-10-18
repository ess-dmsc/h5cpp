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
// Created on: Sep 12, 2017
//

#include <boost/test/floating_point_comparison.hpp>
#include <h5cpp/datatype/datatype.hpp>
#include <h5cpp/property/dataset_creation_list.hpp>
#include <h5cpp/property/dataset_access_list.hpp>
#include <h5cpp/property/link_creation_list.hpp>
#include <h5cpp/property/link_access_list.hpp>
#include <h5cpp/dataspace/simple.hpp>
#include <h5cpp/dataspace/scalar.hpp>
#include <h5cpp/node/dataset.hpp>
#include "../fixture.hpp"

using namespace hdf5;

class Dataset : public BasicFixture
{
};


TEST_F(Dataset, test_default_construction)
{
  node::Dataset dset;

  EXPECT_THROW(dset.dataspace(),std::runtime_error);
  EXPECT_THROW(dset.datatype(),std::runtime_error);
  EXPECT_THROW(dset.extent({10,100}),std::runtime_error);
}

TEST_F(Dataset, test_scalar_dataset)
{
  node::Dataset dset = root_.create_dataset("data",datatype::create<int>(),
                                            dataspace::Scalar());

  EXPECT_EQ(dset.dataspace().type(),dataspace::Type::SCALAR);
  EXPECT_EQ(dset.datatype().get_class(),datatype::Class::INTEGER);

  EXPECT_THROW(dset.extent({10}),std::runtime_error);
}









