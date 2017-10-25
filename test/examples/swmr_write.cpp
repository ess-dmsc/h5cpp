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
// Created on: Oct 16, 2017
//
#include <h5cpp/hdf5.hpp>
#include <boost/filesystem.hpp>
#include <thread>
#include <chrono>
#include <csignal>
#include <atomic>

#include "swmr_builder.hpp"
#include "swmr_environment.hpp"

using namespace hdf5;
namespace fs = boost::filesystem;

static std::atomic<bool> terminated(false);

void SIGINT_handler(int signo)
{
  std::cerr<<"Program was terminated by CTRL-C by the user"<<std::endl;
  terminated = true;
}

void SIGTERM_handler(int signo)
{
  std::cerr<<"Program was terminated by SIGTERM"<<std::endl;
  terminated = true;
}


int main()
{
  SWMREnvironment env;
  SWMRBuilder builder;

  std::signal(SIGINT,SIGINT_handler);
  std::signal(SIGTERM,SIGTERM_handler);

  env.create_file("swmr_io.h5",builder);

  file::File write_file = env.open_write_file("swmr_io.h5");

  dataspace::Hyperslab selection{{0},{1},{1},{1}};
  node::Dataset dset = write_file.root()["data"];
  double buffer=0;

  for(size_t index=0;index<100 && !terminated;index++,buffer++)
  {
    dset.extent(0,1);                     //extend dataset
    selection.start(0,index);             //update selection
    dset.write(buffer,selection);         //write data to selection
    write_file.flush(file::Scope::GLOBAL); // flush file
    std::cout<<"Writing "<<buffer<<std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
  return 0;

}
