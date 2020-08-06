/************************************************************

  This example shows how to read and write data to a dataset
  using a data transform expression.  The program first
  writes integers to a dataset using the transform
  expression TRANSFORM, then closes the file.  Next, it
  reopens the file, reads back the data without a transform,
  and outputs the data to the screen.  Finally it reads the
  data using the transform expression RTRANSFORM and outputs
  the results to the screen.

  This file is intended for use with HDF5 Library version 1.8

 ************************************************************/

#include <h5cpp/hdf5.hpp>
#include "matrix_hdf5.hpp"

#define FILE            "h5ex_d_transform.h5"
#define DATASET         "DS1"
#define DIM0            4
#define DIM1            7
#define TRANSFORM       "x+1"
#define RTRANSFORM      "x-1"

using namespace hdf5;
using Int32Matrix = Matrix<int32_t,DIM0,DIM1>;

void write()
{
  // Initialize data.
  Int32Matrix wdata;
  for (int32_t i=0; i<DIM0; i++)
      for (int32_t j=0; j<DIM1; j++)
          wdata(i,j) = i * j - j;

  // Output the data to the screen.
  std::cout<<"Original Data:"<<std::endl<<wdata<<std::endl;

  // Create a new file using the default properties.
  file::File file = file::create (FILE,file::AccessFlags::TRUNCATE);

  // Create dataspace.  Setting maximum size to NULL sets the maximum
  // size to be the current size.
  dataspace::Simple memory_space({DIM0,DIM1});
  datatype::Datatype memory_type = datatype::create<int32_t>();

  // Create the dataset transfer property list and define the
  // transform expression.
  property::DatasetTransferList dxpl;
  dxpl.data_transform(TRANSFORM);

  // Create the dataset using the default properties.  Unfortunately
  // we must save as a native type or the transform operation will
  // fail.
  node::Dataset dset(file.root(), DATASET, memory_type,memory_space);


  // Write the data to the dataset using the dataset transfer
  // property list.
  dset.write(wdata,memory_type,memory_space,memory_space,dxpl);
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
  std::cout<<std::endl<<"Data as written with transform \""<<TRANSFORM<<"\":"<<std::endl;
  std::cout<<rdata<<std::endl;

  // Create the dataset transfer property list and define the
  // transform expression.
  property::DatasetTransferList dxpl;
  dxpl.data_transform(RTRANSFORM);

  // Read the data using the dataset transfer property list.
  dset.read(rdata,dset.datatype(),dset.dataspace(),dset.dataspace(),dxpl);

  // Output the data to the screen.
  std::cout<<std::endl<<"Data as written with transform \""<<TRANSFORM
           <<"\" and read with transform \""<<RTRANSFORM<<"\":"<<std::endl;
  std::cout<<rdata<<std::endl;
}

int
main (void)
{
  write();
  read();



    return 0;
}
