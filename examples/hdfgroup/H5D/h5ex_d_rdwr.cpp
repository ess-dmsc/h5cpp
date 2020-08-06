/************************************************************

  This example shows how to read and write data to a
  dataset.  The program first writes integers to a dataset
  with dataspace dimensions of DIM0xDIM1, then closes the
  file.  Next, it reopens the file, reads back the data, and
  outputs it to the screen.

  This file is intended for use with HDF5 Library version 1.8

 ************************************************************/

#include <h5cpp/hdf5.hpp>
#include "matrix_hdf5.hpp"

#define FILE            "h5ex_d_rdwr.h5"
#define DATASET         "DS1"
#define DIM0            4
#define DIM1            7

using Int32Matrix = Matrix<int32_t,DIM0,DIM1>;
using namespace hdf5;

void write()
{
  Int32Matrix wdata;

  // Initialize data.
  for (int32_t i = 0; i < DIM0; i++)
    for (int32_t j = 0; j < DIM1; j++)
      wdata (i, j) = i * j - j;


  // Create a new file using the default properties.
  file::File file = file::create (FILE, file::AccessFlags::TRUNCATE);

  // Create dataspace.  Setting maximum size to NULL sets the maximum
  // size to be the current size.
  dataspace::Simple space ({ DIM0, DIM1 });


  // Create the dataset.  We will use all default properties for this
  // example.
  std::cout<<"Data to write:"<<std::endl;
  std::cout<<wdata<<std::endl;
  node::Dataset dset (file.root(), DATASET, datatype::create (wdata), space);


  // Write the data to the dataset.
  dset.write(wdata);
}

void read()
{
  // Open file and dataset using the default properties.
  file::File file = file::open (FILE, file::AccessFlags::READONLY);
  node::Dataset dset = file.root().nodes[DATASET];

  // Read the data using the default properties.
  Int32Matrix rdata;
  dset.read(rdata);

  // Output the data to the screen.
  std::cout<<DATASET<<std::endl;
  std::cout<<rdata<<std::endl;
}

int
main (void)
{
  write();
  read();

  return 0;
}
