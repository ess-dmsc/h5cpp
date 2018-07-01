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

int main()
{
  file::File f = file::create("append_vector_data.h5",
                              file::AccessFlags::TRUNCATE);
  node::Group root_group = f.root();
  property::LinkCreationList lcpl;
  property::DatasetCreationList dcpl;
  dcpl.layout(property::DatasetLayout::CHUNKED);
  dcpl.chunk({100,NBINS});

  Bins data(NBINS);
  dataspace::Simple space{{0,NBINS},{dataspace::Simple::UNLIMITED,NBINS}};
  auto type = datatype::create(data);

  node::Dataset dset(root_group,"data",type,space,lcpl,dcpl);

  int value=0;
  dataspace::Hyperslab slab{{0,0},{1,NBINS},{1,1},{1,1},};
  for(size_t index=1;index<=5;++index,++value)
  {
    std::fill(data.begin(),data.end(),value);
    dset.extent(0,1);
    dset.write(data,slab);
    slab.offset(0,index);

  }
}


