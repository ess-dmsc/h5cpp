/************************************************************

  This example shows how to create and extend an unlimited
  dataset.  The program first writes integers to a dataset
  with dataspace dimensions of DIM0xDIM1, then closes the
  file.  Next, it reopens the file, reads back the data,
  outputs it to the screen, extends the dataset, and writes
  new data to the extended portions of the dataset.  Finally
  it reopens the file again, reads back the data, and
  outputs it to the screen.

  This file is intended for use with HDF5 Library version 1.8

 ************************************************************/

#include <h5cpp/hdf5.hpp>
#include "matrix_hdf5.hpp"
#include <vector>


#define FILE            "h5ex_d_unlimadd.h5"
#define DATASET         "DS1"
#define DIM0            4
#define DIM1            7
#define EDIM0           6
#define EDIM1           10
#define CHUNK0          4
#define CHUNK1          4

using namespace hdf5;
using Int32Matrix = Matrix<int32_t,DIM0,DIM1>;
using Int32MatrixExtended = Matrix<int32_t,EDIM0,EDIM1>;

void write_initial_data()
{
  // Initialize data.
  Int32Matrix wdata;
  for (int32_t i=0; i<DIM0; i++)
      for (int32_t j=0; j<DIM1; j++)
          wdata(i,j) = i * j - j;

  // Create a new file using the default properties.
  file::File file = file::create (FILE, file::AccessFlags::TRUNCATE);

  // Create dataspace with unlimited dimensions.
  dataspace::Simple space({DIM0,DIM1},
                          {dataspace::Simple::UNLIMITED,
                           dataspace::Simple::UNLIMITED});

  // Create the dataset creation property list, and set the chunk size.
  property::LinkCreationList lcpl;
  property::DatasetCreationList dcpl;
  dcpl.layout(property::DatasetLayout::CHUNKED);
  dcpl.chunk({CHUNK0,CHUNK1});

  // Create the unlimited dataset.
  node::Dataset dset (file.root(), DATASET, datatype::create<int32_t>(), space,lcpl, dcpl);

  // Write the data to the dataset.
  dset.write(wdata);
}

void append_data()
{
  // Open file and dataset using the default properties.
  file::File file = file::open (FILE, file::AccessFlags::READWRITE);
  node::Dataset dset = file.root().nodes[DATASET];

  // Get dataspace and allocate memory for read buffer.  This is a
  // two dimensional dataset so the dynamic allocation must be done
  // in steps.
  dataspace::Simple space = dset.dataspace();

  // Read the data using the default properties.
  Int32Matrix rdata;
  dset.read(rdata);

  // Output the data to the screen.
  std::cout<<"Dataset before extension:"<<std::endl;
  std::cout<<rdata<<std::endl;

  // Extend the dataset.
  dset.extent({EDIM0,EDIM1});

  // Retrieve the dataspace for the newly extended dataset.
  space = dset.dataspace();

  /*
   * Initialize data for writing to the extended dataset.
   */
  Int32MatrixExtended wextdata;
  for (int32_t i=0; i<EDIM0; i++)
      for (int32_t j=0; j<EDIM1; j++)
          wextdata(i,j) = j;

  // Subtract a hyperslab reflecting the original dimensions from the
  // selection.  The selection now contains only the newly extended
  // portions of the dataset.
  dataspace::Hyperslab selection({0,0},{DIM0,DIM1});
  space.selection(dataspace::SelectionOperation::NOTB,selection);

  // Write the data to the selected portion of the dataset.
  dset.write(wextdata,datatype::create(wextdata),space,space);

}

void read()
{
  // Open file and dataset using the default properties.
  file::File file = file::open (FILE, file::AccessFlags::READONLY);
  node::Dataset dset = file.root().nodes[DATASET];

  // Get dataspace and allocate memory for the read buffer as before.
  Int32MatrixExtended rextdata;

  // Read the data using the default properties.
  dset.read(rextdata);

  // Output the data to the screen.
  std::cout<< "Dataset after extension:"<<std::endl;
  std::cout<<rextdata<<std::endl;

}

int
main (void)
{
  write_initial_data();
  append_data();
  read();

  return 0;
}
