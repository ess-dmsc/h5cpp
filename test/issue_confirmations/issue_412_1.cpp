//
// (c) Copyright 2019 DESY,ESS
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
// Authors:
//   Eugen Wintersberger <eugen.wintersberger@desy.de>
//   Jan Kotanski <jan.kotanski@desy.de>
//
// Created on: Aug 31, 2019
//
#include <iostream>
#include <boost/filesystem.hpp>
#include <h5cpp/hdf5.hpp>
#include <ctime>

using namespace hdf5;

int main()
{
  boost::filesystem::path file_path("data.h5");
  file::File f1 = file::create(file_path);

  node::Group root_group = f1.root();

  filter::Deflate filter(2u);
  property::DatasetCreationList dcpl;
  auto type = datatype::create<int>();
  property::LinkCreationList lcpl;
  property::DatasetAccessList dapl;

  dcpl.layout(property::DatasetLayout::CHUNKED);
  dcpl.chunk({1, 4096L* 4096L});
  filter(dcpl);

  dataspace::Simple fin_space({0, 4096L* 4096L},
                              {dataspace::Simple::UNLIMITED, dataspace::Simple::UNLIMITED});
  auto fdata = node::Dataset(root_group,Path("fin_data"), type, fin_space, lcpl, dcpl, dapl);
  std::vector<int> v(4096L* 4096L);
  std::generate(v.begin(), v.end(), std::rand);
  dataspace::Hyperslab slab {{0, 0}, {1, 4096L* 4096L}, {1, 1}, {1, 1}};

  std::clock_t begin = clock();
  for(unsigned long int i = 0; i < 10; i++){
    std::cout << "Write " << i << std::endl;
    fdata.extent(0, 1);
    slab.offset({i, 0});
    fdata.write(v, slab);
  }
  std::clock_t end = clock();
  double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
  std::cout << "Time " << elapsed_secs << std::endl;

  fdata.close();
  root_group.close();
  f1.close();
  return 0;
}




