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
// Created on: Oct 18, 2017
//
#include <h5cpp/h5cpp.hpp>
#include <h5cpp/core/filesystem.hpp>
#include <thread>
#include <chrono>
#include <algorithm>

#include "swmr_environment.hpp"

using namespace hdf5;

int main()
{
  SWMREnvironment env;

  file::File read_file = env.open_read_file("swmr_io.h5");
  node::Group root_group = read_file.root();
  node::Dataset dset = root_group.nodes["data"];

  dataspace::Hyperslab selection{{0},{1},{1},{1}};
  std::vector<double> buffer;
  size_t first_index = 0;

  for(;;)
  {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    dset.refresh();

    Dimensions current = dataspace::Simple(dset.dataspace()).current_dimensions();
    size_t block_size = current[0] - first_index;

    selection.offset(0,first_index);
    selection.block(0,block_size);
    buffer = std::vector<double>(block_size);
    dset.read(buffer,selection);

    std::for_each(buffer.begin(),buffer.end(),
                  [](double value){std::cout<<value<<std::endl;});

    //we have zero-based indexing, thus we need the -1
    first_index = current[0];

  }

  return 0;
}
