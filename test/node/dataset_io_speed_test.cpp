//
// (c) Copyright 2017 DESY,ESS
//               2021 Eugen Wintersberger <eugen.wintersberger@gmail.com>
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
// Author: Jan Kotanski <jan.kotanski@desy.de>
//         Eugen Wintersberger <eugen.wintersberger@gmail.com>
// Created on: Nov 12, 2018
//
#include <catch2/catch_amalgamated.hpp>
#include <h5cpp/core/filesystem.hpp>
#include <h5cpp/dataspace/hyperslab.hpp>
#include <h5cpp/file/functions.hpp>
#include <h5cpp/node/group.hpp>
using namespace hdf5;

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wexit-time-destructors"
#pragma clang diagnostic ignored "-Wglobal-constructors"
#endif
namespace { 
const static long long unsigned int xdim = 867;
const static long long unsigned int ydim = 700;
const static long long unsigned int nframe = 33;
static std::string filename = "dataset_io_speed.h5";
using UShorts = std::vector<unsigned short int>;

static hdf5::Dimensions current_dimensions(const hdf5::node::Dataset& dataset) {
  hdf5::dataspace::Simple dataspace(dataset.dataspace());
  return dataspace.current_dimensions();
}
}
#ifdef __clang__
#pragma clang diagnostic pop
#endif

class create {
 public:
  static property::FileCreationList fcpl() {
    return property::FileCreationList();
  }
  static property::LinkCreationList lcpl() {
    return property::LinkCreationList();
  }
  static property::DatasetAccessList dapl() {
    return property::DatasetAccessList();
  }

  static property::DatasetCreationList dcpl() {
    property::DatasetCreationList dcpl;
    dcpl.layout(property::DatasetLayout::Chunked);
    dcpl.chunk({1, xdim, ydim});
    return dcpl;
  }
  static property::FileAccessList fapl() {
    property::FileAccessList fapl;
#if H5_VERSION_GE(1, 10, 0)
    fapl.library_version_bounds(property::LibVersion::Latest,
                                property::LibVersion::Latest);
#endif
    return fapl;
  }
  static file::File file() {
    return file::create(filename, file::AccessFlags::Truncate, fcpl(), fapl());
  }
  static dataspace::Simple ds(Dimensions current) {
    Dimensions dmax(current.size());
    std::fill(std::begin(dmax), std::end(dmax), dataspace::Simple::unlimited);
    return dataspace::Simple(current, dmax);
  }

  static UShorts buffer(size_t size) {
    UShorts b(size);
    std::fill(std::begin(b), std::end(b), 1);
    return b;
  }
};

SCENARIO("Testing IO performance using different memory and file spaces") {
  auto ds_frame3 = create::ds({0, xdim, ydim});  // 3d dataspace for a 2D frame
  auto ds_all =
      create::ds({nframe, xdim, ydim});       // full dataspace of the block
  auto ds_frame2 = create::ds({xdim, ydim});  // 2d dataspace for a 2d frame
  auto dcpl = create::dcpl();
  auto lcpl = create::lcpl();
  auto dapl = create::dapl();
  property::DatasetTransferList dtpl;
  auto dtype = datatype::create<unsigned short int>();
  auto buffer_all = create::buffer(nframe * xdim * ydim);
  auto buffer_frame = create::buffer(xdim * ydim);
  auto buffer_selection = create::buffer(11 * xdim * ydim);

  GIVEN("A new HDF5 file") {
    auto file = create::file();
    AND_GIVEN("an initially empty dataset") {
      node::Dataset dataset(file.root(), "data", dtype, ds_frame3, lcpl, dcpl,
                            dapl);
      auto selection = dataspace::Hyperslab({{0, 0, 0}, {1, xdim, ydim}});
      THEN("we can fill in frame by frame with full controll") {
        BENCHMARK("writing by single frame setting everything manually") {
          // here we set everything manually -> total control about what is
          // happening
          for (size_t frame_index = 0; frame_index < nframe; frame_index++) {
            dataset.extent(0, 1);
            selection.offset({frame_index, 0, 0});
            auto file_space = dataset.dataspace();
            file_space.selection(dataspace::SelectionOperation::Set, selection);
            dataset.write(buffer_frame, dtype, ds_frame2, file_space, dtpl);
          }
        };
      }
      THEN("we can fill in frame by frame with derived ") {
        BENCHMARK("writing by single frame using auto setup") {
          // in this case the hyperlab is applied automatically and, more
          // important, the code derives every parameter of the memory
          // source by itself.
          for (size_t frame_index = 0; frame_index < nframe; frame_index++) {
            dataset.extent(0, 1);
            selection.offset({frame_index, 0, 0});
            dataset.write(buffer_frame, selection);
          }
        };
      }
    }
    AND_GIVEN("a dataset all elements present after construction") {
      node::Dataset dataset(file.root(), "data", dtype, ds_all, lcpl, dcpl,
                            dapl);
      THEN("we can write the entire data at once") {
        BENCHMARK("writing the entire dataset at once") {
          dataset.write(buffer_all);
        };
        AND_THEN("we can perform some read operations") {
          auto dims = current_dimensions(dataset);
          dataspace::Simple dspace = dataset.dataspace();
          BENCHMARK("selecting the entire dataset block") {
            hdf5::Dimensions frameoffset{0, 0, 0};
            hdf5::Dimensions frameblock{dims[0], dims[1], dims[2]};
            hdf5::dataspace::Hyperslab selected_frames{frameoffset, frameblock};
            return dataset.read(buffer_all, dtype, dspace, selected_frames);
          };
          BENCHMARK("reading the entire dataset") {
            return dataset.read(buffer_all);
          };
          BENCHMARK(
              "reading 11 frames with a hyperslab and a memory dataspace of "
              "the "
              "correct rank") {
            hdf5::dataspace::Hyperslab selection{{10, 0, 0},
                                                 {11, dims[1], dims[2]}};
            dataspace::Simple memory_dataspace(
                Dimensions({11, dims[1], dims[2]}));
            return dataset.read(buffer_selection, dtype, memory_dataspace,
                                selection);
          };
          BENCHMARK("reading 11 frames with a default dataspace") {
            hdf5::dataspace::Hyperslab selection{{10, 0, 0},
                                                 {11, dims[1], dims[2]}};
            return dataset.read(buffer_selection, selection);
          };
        }
      }
    }
  }

  // create_initial_datafile();
  /*
  GIVEN("The data file with the data to read") {
    auto file = file::open(filename, file::AccessFlags::ReadOnly);
    auto dataset = file.root().get_dataset("/data");
    auto dtype = dataset.datatype();
  }*/
}
