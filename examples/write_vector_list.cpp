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
// Created on: Oct 10, 2017
//

#include <h5cpp/h5cpp.hpp>
#include "vector.hpp"
#include "vector_h5.hpp"
#include <vector>

using namespace hdf5;

using DoubleVector = Vector<double>;
using Positions = std::vector<DoubleVector>;
using Velocities = std::vector<DoubleVector>;

class VectorAppender
{
  private:
    node::Dataset dataset_;
    dataspace::Hyperslab selection_;
    std::string log_prefix_;
  public:
    VectorAppender() = delete;
    VectorAppender(node::Dataset dataset,const std::string &log_prefix):
      dataset_(dataset),
      selection_(dataspace::Hyperslab({0},{1},{1},{1})),
      log_prefix_(log_prefix)
    {
      dataspace::Simple dataspace = dataset_.dataspace();
      selection_.offset(0,dataspace.current_dimensions()[0]);
    }

    void operator()(const DoubleVector vector)
    {
      std::cout<<"write "<<log_prefix_<<": "<<vector<<std::endl;
      dataset_.extent(0,1); //extend the dataset
      dataset_.write(vector,selection_); //write the data
      selection_.offset(0,selection_.offset()[0]+1); // extend the selection
    }
};

node::Dataset create_vector_dataset(const std::string &name,const node::Group &parent_group)
{
  property::LinkCreationList lcpl;
  property::DatasetCreationList dcpl;
  dcpl.layout(property::DatasetLayout::Chunked);
  dcpl.chunk(Dimensions{1024});

  auto datatype = datatype::TypeTrait<DoubleVector>::create();
  dataspace::Simple dataspace({0},{dataspace::Simple::unlimited});

  return node::Dataset(parent_group,name,datatype,dataspace,lcpl,dcpl);
}


int main()
{
  Positions positions(10);
  Velocities velocities(10);

  file::File file = file::create("write_vector_list.h5",file::AccessFlags::Truncate);
  node::Group root_group = file.root();

  VectorAppender positions_appender(create_vector_dataset("positions",root_group),"position");
  VectorAppender velocities_appender(create_vector_dataset("velocities",root_group),"velocity");


  std::for_each(positions.begin(),positions.end(),positions_appender);
  std::for_each(velocities.begin(),velocities.end(),velocities_appender);

  return 0;
}


