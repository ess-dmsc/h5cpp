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
// Created on: Oct 11, 2017
//
#include <iostream>
#include <h5cpp/hdf5.hpp>

using namespace hdf5;

int main()
{
  file::File f = file::create("append_scalar_data.h5",
                              file::AccessFlags::TRUNCATE);
  node::Group root_group = f.root();
  property::LinkCreationList lcpl;
  property::DatasetCreationList dcpl;
  dcpl.layout(property::DatasetLayout::CHUNKED);
  dcpl.chunk(Dimensions{1024});


  dataspace::Simple space({0},{dataspace::Simple::UNLIMITED});
  auto type = datatype::create<int>();

  node::Dataset dset = root_group.create_dataset("data",type,space,
                                                 lcpl,dcpl);

  dataspace::Hyperslab slab{{0},{1},{1},{1}};
  int data=0;
  for(size_t index=1;index<=25;++index,++data)
  {
    dset.extent(0,1);      //grow dataset
    dset.write(data,slab); //write data
    slab.offset(0,index);   //update selection
  }
}



