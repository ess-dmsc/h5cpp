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

node::Dataset create_dataset(const node::Group parent_group)
{
  property::LinkCreationList lcpl;
  property::DatasetCreationList dcpl;

  // in order to append data we have to use a chunked layout of the dataset
  dcpl.layout(property::DatasetLayout::CHUNKED);
  dcpl.chunk(Dimensions{1024});

  // create dataspace (infinitely extensible) and datatype
  dataspace::Simple space({0},{dataspace::Simple::UNLIMITED});
  auto type = datatype::create<int>();

  // finally create the dataset
  return node::Dataset(parent_group,"data",type,space,lcpl,dcpl);
}

int main()
{
  file::File f = file::create("append_scalar_data.h5",
                              file::AccessFlags::TRUNCATE);
  node::Group root_group = f.root();

  //
  // create the dataset to which we want to write data
  //
  node::Dataset dataset = create_dataset(root_group);

  //
  // write individual elements to the dataset using a Hyperslab selection
  //
  std::cout<<"writing: ";
  dataspace::Hyperslab selection{{0},{1},{1},{1}};
  int data=0;
  for(size_t index=1;index<=25;++index,++data)
  {
    dataset.extent(0,1);           //grow dataset
    dataset.write(data,selection); //write data
    selection.offset(0,index);  //update selection
    std::cout<<data<<"  ";
  }
  std::cout<<std::endl;

  //
  // reading individual data elements from the dataset
  //
  std::cout<<"reading: ";
  for(size_t index=0;index<=24;++index)
  {
    selection.offset(0,index);
    int value;
    dataset.read(value,selection);
    std::cout<<value<<"  ";
  }
  std::cout<<std::endl;

  return 0;
}



