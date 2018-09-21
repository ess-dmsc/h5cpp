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
// Created on: Sep 12, 2017
//

#include <h5cpp/hdf5.hpp>
#include "group_test_fixtures.hpp"

using namespace hdf5;

class Extent : public BasicFixture
{
  protected:
    node::Dataset fin_data;
    node::Dataset inf_data;
    dataspace::Simple sspace;

    virtual void SetUp()
    {
      BasicFixture::SetUp();
      auto type = datatype::create<int>();
      property::DatasetCreationList dcpl;
      property::LinkCreationList lcpl;
      property::DatasetAccessList dapl;

      dcpl.layout(property::DatasetLayout::CHUNKED);
      dcpl.chunk({1024});

      dataspace::Simple fin_space({0},{4096});
      fin_data = node::Dataset(root_,Path("fin_data"),type,fin_space,lcpl,dcpl,dapl);

      dataspace::Simple inf_space({0},{dataspace::Simple::UNLIMITED});
      inf_data = node::Dataset(root_,Path("inf_data"),type,inf_space,lcpl,dcpl,dapl);
    }

};


TEST_F(Extent, test_infinite_extent_absolut)
{
  sspace = inf_data.dataspace();
  EXPECT_EQ(sspace.current_dimensions()[0],0ul);
  EXPECT_NO_THROW(inf_data.extent({1000}));
  EXPECT_NO_THROW(sspace = inf_data.dataspace());
  sspace = inf_data.dataspace();
  EXPECT_EQ(sspace.current_dimensions()[0],1000ul);
}

TEST_F(Extent,test_infinite_resize_absolute)
{
  sspace = inf_data.dataspace();
  EXPECT_EQ(sspace.current_dimensions()[0],0ul);
  EXPECT_NO_THROW(inf_data.resize({1000}));
  EXPECT_NO_THROW(sspace = inf_data.dataspace());
  sspace = inf_data.dataspace();
  EXPECT_EQ(sspace.current_dimensions()[0],1000ul);
}

TEST_F(Extent, test_infinite_extent_relative)
{
  sspace = inf_data.dataspace();
  EXPECT_EQ(sspace.current_dimensions()[0],0ul);
  EXPECT_NO_THROW(inf_data.extent(0,123));
  sspace = inf_data.dataspace();
  EXPECT_EQ(sspace.current_dimensions()[0],123ul);

  EXPECT_THROW(inf_data.extent(0,-1000),std::runtime_error);
  EXPECT_THROW(inf_data.extent(1,100),std::runtime_error);
}

TEST_F(Extent, test_infinite_resize_by)
{
  sspace = inf_data.dataspace();
  EXPECT_EQ(sspace.current_dimensions()[0],0ul);
  EXPECT_NO_THROW(resize_by(inf_data,0,123));
  sspace = inf_data.dataspace();
  EXPECT_EQ(sspace.current_dimensions()[0],123ul);

  EXPECT_THROW(resize_by(inf_data,0,-1000),std::runtime_error);
  EXPECT_THROW(resize_by(inf_data,1,100),std::runtime_error);
}

TEST_F(Extent, test_finite_extent_absolute)
{
  EXPECT_NO_THROW(fin_data.extent({100}));
  sspace = fin_data.dataspace();
  EXPECT_EQ(sspace.current_dimensions()[0],100ul);

  EXPECT_THROW(fin_data.extent({100000}),std::runtime_error);
}

TEST_F(Extent, test_finite_resize_absolute)
{
  EXPECT_NO_THROW(fin_data.extent({100}));
  sspace = fin_data.dataspace();
  EXPECT_EQ(sspace.current_dimensions()[0],100ul);

  EXPECT_THROW(fin_data.resize({100000}),std::runtime_error);
}


TEST_F(Extent, test_finite_extent_relative)
{
  EXPECT_NO_THROW(fin_data.extent(0,100));
  sspace = fin_data.dataspace();
  EXPECT_EQ(sspace.current_dimensions()[0],100ul);

  EXPECT_THROW(fin_data.extent(0,-1000000),std::runtime_error);
  EXPECT_THROW(fin_data.extent(1,100),std::runtime_error);
  EXPECT_THROW(fin_data.extent(0,100000),std::runtime_error);
}

TEST_F(Extent, test_finite_resize_by)
{
  EXPECT_NO_THROW(resize_by(fin_data,0,100));
  sspace = fin_data.dataspace();
  EXPECT_EQ(sspace.current_dimensions()[0],100ul);

  EXPECT_THROW(resize_by(fin_data,0,-1000000),std::runtime_error);
  EXPECT_THROW(resize_by(fin_data,1,100),std::runtime_error);
  EXPECT_THROW(resize_by(fin_data,0,100000),std::runtime_error);
}







