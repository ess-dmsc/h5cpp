/************************************************************

  This example shows how to read and write data to a compact
  dataset.  The program first writes integers to a compact
  dataset with dataspace dimensions of DIM0xDIM1, then
  closes the file.  Next, it reopens the file, reads back
  the data, and outputs it to the screen.

  This file is intended for use with HDF5 Library version 1.8

 ************************************************************/

#include <h5cpp/hdf5.hpp>
#include "matrix_hdf5.hpp"

#define FILE            "h5ex_d_compact.h5"
#define DATASET         "DS1"
#define DIM0            4
#define DIM1            7

using Int32Matrix = Matrix<int32_t,DIM0,DIM1>;

void write_data()
{
  using namespace hdf5;

  //
  // Create a new file using the default properties.
  //
  file::File file = file::create(FILE,file::AccessFlags::TRUNCATE);

  //
  // Create dataspace.  Setting maximum size to NULL sets the maximum
  // size to be the current size.
  //
  dataspace::Simple space({DIM0,DIM1});

  //
  // Create the dataset creation property list, set the layout to
  // compact.
  //
  property::LinkCreationList lcpl;
  property::DatasetCreationList  dcpl;
  dcpl.layout(property::DatasetLayout::COMPACT);

  //
  // Create the dataset.  We will use all default properties for this
  // example.
  //
  node::Dataset dset(file.root(), DATASET, datatype::create<Int32Matrix>(),
                     space,lcpl, dcpl);

  //
  // Initialize data
  //
  Int32Matrix data;
  for (size_t i=0; i<DIM0; i++)
      for (size_t j=0; j<DIM1; j++)
          data(i,j) = i * j - j;

  //
  // write data to disk
  //
  dset.write(data);

  std::cout<<"Data written to disk: "<<std::endl<<data<<std::endl;

}

void read_data()
{
  using namespace hdf5;

  //
  // Open file and dataset using the default properties.
  //
  file::File file = file::open(FILE,file::AccessFlags::READONLY);
  node::Dataset dset = file.root()[DATASET];

  //
  // Retrieve the dataset creation property list, and print the
  // storage layout.
  //
  property::DatasetCreationList dcpl = dset.creation_list();
  std::cout<<"Storage layout is: "<<dcpl.layout()<<std::endl<<std::endl;

  Int32Matrix data;
  dset.read(data);

  std::cout<<"Read data: "<<std::endl<<data<<std::endl;

}

int
main (void)
{
   write_data();
   read_data();

   return 0;
}
