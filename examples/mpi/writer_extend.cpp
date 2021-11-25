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
// Created on: Nov 7, 2017
//

#include <h5cpp/hdf5.hpp>
#include <iostream>

using namespace hdf5;

file::File create_file(MPI_Comm comm,MPI_Info info)
{
  property::FileCreationList fcpl;
  property::FileAccessList fapl;
  fapl.driver(file::MPIDriver(comm,info));

  file::File f = file::create("mpi_write_extend.h5",
                              file::AccessFlags::Truncate,
                              fcpl,fapl);
  return f;
}

node::Dataset create_dataset(const node::Group &base)
{
  auto file_type = datatype::create<int>();
  dataspace::Simple file_space{{0},{dataspace::Simple::unlimited}};

  property::LinkCreationList lcpl;
  property::DatasetCreationList dcpl;
  dcpl.layout(property::DatasetLayout::Chunked);
  dcpl.chunk({1024*1024});

  return base.create_dataset("extended_data",file_type,file_space,lcpl,dcpl);
}

int main(int argc,char **argv)
{
  MPI_Init(&argc,&argv);

  int total_procs,my_id;

  MPI_Comm_rank(MPI_COMM_WORLD,&my_id);
  MPI_Comm_size(MPI_COMM_WORLD,&total_procs);

  std::cout<<"Hello world from "<<my_id<<" of "<<total_procs<<std::endl;

  //we need this as a guard to ensure that all HDF5 objects are closed
  //before MPI_Finalize() is called.
  {
    file::File f = create_file(MPI_COMM_WORLD,MPI_INFO_NULL);
    node::Group root_group = f.root();
    node::Dataset dataset = create_dataset(root_group);

    //writing interlaced data to the dataset
    size_t index=0;
    while(index<10)
    {
      dataset.extent(0,total_procs);
      dataspace::Hyperslab selection{{index*total_procs+my_id},{1},{1},{1}};
      dataset.write(my_id,selection);
      index++;
    }
  }


  MPI_Finalize();

  return 0;
}
