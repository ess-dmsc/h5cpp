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
#include <vector>
#include <algorithm>

using namespace hdf5;

using Bins = std::vector<int>;
#define NBINS 6

node::Dataset create_dataset(const node::Group parent_group,const Bins bins)
{
  property::LinkCreationList lcpl;
  property::DatasetCreationList dcpl;
  dcpl.layout(property::DatasetLayout::Chunked);
  dcpl.chunk({100,bins.size()});

  dataspace::Simple space{{0,bins.size()},{dataspace::Simple::UNLIMITED,NBINS}};
  auto type = datatype::create(bins);

  return node::Dataset(parent_group,"data",type,space,lcpl,dcpl);
}

void print_data(const std::string &prefix,const Bins &bins)
{
  std::cout<<prefix;
  std::for_each(bins.begin(),bins.end(),
                 [](int value) { std::cout<<value<<"  "; });
  std::cout<<std::endl;
}

int main()
{
  file::File f = file::create("append_vector_data.h5",
                              file::AccessFlags::Truncate);
  node::Group root_group = f.root();
  Bins data(NBINS);
  node::Dataset dataset = create_dataset(root_group,data);

  //
  // writing the data to disk
  //
  dataspace::Hyperslab selection{{0,0},{1,data.size()},{1,1},{1,1},};
  for(size_t index=1;index<=5;++index)
  {
    std::fill(data.begin(),data.end(),index); //create data
    dataset.extent(0,1);            // extend dataset in order to store the new
                                    // data
    dataset.write(data,selection);  // write data
    selection.offset(0,index);      // update the selection offset
    print_data("writing: ",data);
  }
  std::cout<<std::endl;

  //
  // reading the data back from disk
  //
  for(size_t index=0;index<=4;index++)
  {
    selection.offset(0,index);
    dataset.read(data,selection);
    print_data("reading: ",data);
  }


}


