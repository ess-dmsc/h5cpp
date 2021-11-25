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
#include <h5cpp/hdf5.hpp>
#include <iostream>
#include <vector>

using namespace hdf5;

void createFile() {
  file::File File = file::create("SomeFile.hdf5", file::AccessFlags::Truncate);
  node::Group RootGroup = File.root();

  std::vector<int> Data{1, 2, 3, 4, 5, 6};
  Dimensions Shape{2, 3};
  Dimensions MaxShape{dataspace::Simple::unlimited, 3};
  Dimensions ChunkSize{512, 3};
  dataspace::Simple Dataspace{Shape, MaxShape};
  datatype::Datatype Datatype = datatype::create<std::int32_t>();
  auto Dataset = node::ChunkedDataset(RootGroup, "test_data", Datatype,
                                      Dataspace, ChunkSize);
  Dataset.write(Data);
}

int main() {
  createFile();
  auto AnotherFile = file::open("SomeFile.hdf5");
  auto RootGroup = AnotherFile.root();
  auto Dataset = RootGroup.get_dataset("test_data");
  dataspace::Simple Dataspace(Dataset.dataspace());
  auto Dimensions = Dataspace.current_dimensions();
  auto MaxDimensions = Dataspace.maximum_dimensions();
  std::cout << "Dataset dimensions\n";
  std::cout << "   Current | Max\n";
  for (int i = 0; i < Dimensions.size(); i++) {
    std::cout << "i:" << i << "      " << Dimensions[i] << " | "
              << MaxDimensions[i] << "\n";
  }

  auto CreationProperties = Dataset.creation_list();
  auto ChunkDims = CreationProperties.chunk();
  std::cout << "\nChunk size\n";
  for (int i = 0; i < ChunkDims.size(); i++) {
    std::cout << "i:" << i << "     " << ChunkDims[i] << "\n";
  }

  std::cout << "\nData type\n";
  auto Int32Type = datatype::create<std::int32_t>();
  auto UInt32Type = datatype::create<std::uint32_t>();
  auto FloatType = datatype::create<float>();
  auto DataTypeClass = Dataset.datatype().get_class();
  auto CurrentType = Dataset.datatype();
  std::cout << "Is:        " << DataTypeClass << std::endl;
  std::cout << "Is  int32: " << (Int32Type == CurrentType) << std::endl;
  std::cout << "Is uint32: " << (UInt32Type == CurrentType) << std::endl;
  std::cout << "Is  float: " << (FloatType == CurrentType) << std::endl;

  std::cout << "\nAll elements\n";
  std::vector<int> AllElements(Dataspace.size());
  Dataset.read(AllElements);
  for (auto Value : AllElements) {
    std::cout << Value << " ";
  }
  std::cout << "\n\nRow access\n";
  std::vector<int> RowData(static_cast<size_t>(Dimensions[1]));
  for (size_t i = 0; i < Dimensions[0]; i++) {
    dataspace::Hyperslab RowSelection{{i, 0}, {1, 3}};
    Dataset.read(RowData, RowSelection);
    std::cout << "i: " << i << " | ";
    for (auto Value : RowData) {
      std::cout << Value << " ";
    }
    std::cout << "\n";
  }
  std::cout << "\nElement access\n     j:0  j:1 j:2\n";
  for (size_t i = 0; i < Dimensions[0]; i++) {
    std::cout << "i:" << i << "    ";
    for (size_t j = 0; j < Dimensions[1]; j++) {
      int Value;
      dataspace::Hyperslab ElementSelection{{i, j}, {1, 1}};
      Dataset.read(Value, ElementSelection);
      std::cout << Value << "    ";
    }
    std::cout << "\n";
  }
  return 0;
}
