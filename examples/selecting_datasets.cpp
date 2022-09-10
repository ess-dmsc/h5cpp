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
// Created on: Oct 07, 2017
//
#include <h5cpp/h5cpp.hpp>
#include <iostream>
#include <vector>

using namespace hdf5;

int main()
{

  file::File f = file::create("selecting_datasets.h5",file::AccessFlags::Truncate);
  node::Group root_group = f.root();

  root_group.create_group("g1");
  root_group.create_dataset("d1",datatype::create<int>(),dataspace::Scalar());
  root_group.create_group("g2");
  root_group.create_dataset("d2",datatype::create<double>(),dataspace::Scalar());
  root_group.create_group("g3");
  root_group.create_dataset("d3",datatype::create<float>(),dataspace::Scalar());

  std::cout<<"file contains "<<root_group.nodes.size()<<" nodes"<<std::endl;
  for(auto n: root_group.nodes)
    std::cout<<n.link().path()<<std::endl;

  std::vector<node::Dataset> datasets;
  std::copy_if(root_group.nodes.begin(),root_group.nodes.end(),
               std::back_inserter(datasets),
               [](const node::Node &n) { return n.type()==node::Type::Dataset;});

  std::cout<<"Found "<<datasets.size()<<" datasets"<<std::endl;
  for(auto dset: datasets)
    std::cout<<dset.link().path()<<std::endl;

  return 0;
}
