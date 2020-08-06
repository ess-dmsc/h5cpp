/************************************************************

  This example shows how to read and write data to a
  dataset by hyberslabs.  The program first writes integers
  in a hyperslab selection to a dataset with dataspace
  dimensions of DIM0xDIM1, then closes the file.  Next, it
  reopens the file, reads back the data, and outputs it to
  the screen.  Finally it reads the data again using a
  different hyperslab selection, and outputs the result to
  the screen.

  This file is intended for use with HDF5 Library version 1.8

 ************************************************************/

#include <h5cpp/hdf5.hpp>
#include "matrix_hdf5.hpp"
#include <algorithm>

#define FILE            "h5ex_d_hyper.h5"
#define DATASET         "DS1"
#define DIM0            6
#define DIM1            8

using Int32Matrix = Matrix<int32_t,DIM0,DIM1>;
using namespace hdf5;

void write ()
{
  Int32Matrix wdata;
  std::fill (wdata.begin (), wdata.end (), 1);

  // Print the data to the screen.
  std::cout << "Original Data:" << std::endl;
  std::cout << wdata << std::endl;

  // Create a new file using the default properties.
  file::File file = file::create (FILE, file::AccessFlags::TRUNCATE);

  // Create dataspace.  Setting maximum size to NULL sets the maximum
  // size to be the current size.
  dataspace::Simple space ({ DIM0, DIM1 });

  // Create the dataset.  We will use all default properties for this
  // example.
  node::Dataset dset (file.root (), DATASET, datatype::create<int32_t> (),
                      space);

  // Define and select the first part of the hyperslab selection.
  dataspace::Hyperslab hyperslab1 (  { 0, 0 },  //offset
                                     { 2, 2 },  //block
                                     { 2, 3 },  //count
                                     { 3, 3 }); //stride

  // Define and select the second part of the hyperslab selection.
  dataspace::Hyperslab hyperslab2 (  { 0, 0 },  //offset
                                     { 1, 1 },  //block
                                     { 2, 3 },  //count
                                     { 3, 3 }); //stride

  //apply the hyperslabs to the dataspace
  space.selection (dataspace::SelectionOperation::SET, hyperslab1);
  space.selection (dataspace::SelectionOperation::NOTB, hyperslab2);


  //Write the data to the dataset.
  dset.write (wdata, datatype::create (wdata), space,
              space);
}

void read()
{
  // Open file and dataset using the default properties.
  file::File file = file::open(FILE,file::AccessFlags::READONLY);
  node::Dataset dset = file.root().nodes[DATASET];


  // Read the data using the default properties.
  Int32Matrix rdata;
  dset.read(rdata);

  // Output the data to the screen.

  std::cout<<"Data as written to disk by hyberslabs:"<<std::endl;
  std::cout<<rdata<<std::endl;

  // Initialize the read array.
  std::fill(rdata.begin(),rdata.end(),0);

  // Define and select the hyperslab to use for reading.
  dataspace::Dataspace space = dset.dataspace();
  dataspace::Hyperslab hyperslab( {0,1},   // offset
                                  {2,3},   // block
                                  {2,2},   // count
                                  {4,4});  // stride
  space.selection(dataspace::SelectionOperation::SET,hyperslab);

  // Read the data using the previously defined hyperslab.
  dset.read(rdata,datatype::create(rdata),space,space);

  // Output the data to the screen.
  std::cout<<"Data as read from disk by hyperslab:"<<std::endl;
  std::cout<<rdata<<std::endl;
}

int
main (void)
{
  write();
  read();

  return 0;
}
