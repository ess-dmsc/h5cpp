/************************************************************

  This example shows how to create a chunked dataset.  The
  program first writes integers in a hyperslab selection to
  a chunked dataset with dataspace dimensions of DIM0xDIM1
  and chunk size of CHUNK0xCHUNK1, then closes the file.
  Next, it reopens the file, reads back the data, and
  outputs it to the screen.  Finally it reads the data again
  using a different hyperslab selection, and outputs
  the result to the screen.

  This file is intended for use with HDF5 Library version 1.8

 ************************************************************/

#include <h5cpp/hdf5.hpp>
#include <array>
#include "matrix_hdf5.hpp"

#define FILE            "h5ex_d_chunk.h5"
#define DATASET         "DS1"
#define DIM0            6
#define DIM1            8
#define CHUNK0          4
#define CHUNK1          4

using namespace hdf5;

using Int32Matrix = Matrix<int32_t,DIM0,DIM1>;

void write_data()
{
  /*
   * Create a new file using the default properties.
   */

  file::File file = file::create (FILE, file::AccessFlags::TRUNCATE);

  /*
   * Create dataspace.  Setting maximum size to NULL sets the maximum
   * size to be the current size.
   */
  dataspace::Simple file_space({ DIM0, DIM1 });

  /*
   * Create the dataset creation property list, and set the chunk
   * size.
   */
  property::DatasetCreationList dcpl;
  dcpl.layout (property::DatasetLayout::CHUNKED);
  dcpl.chunk (Dimensions{ CHUNK0, CHUNK1 });

  /*
   * Create the chunked dataset.
   */
  property::LinkCreationList lcpl;
  node::Dataset dset (file.root (), DATASET, datatype::create<int32_t> (),
                      file_space, lcpl, dcpl);

  /*
   * Define and select the first part of the hyperslab selection.
   */
  file_space.selection(dataspace::SelectionOperation::SET,
                       dataspace::Hyperslab({ 0, 0 },{ 2, 2 },{ 2, 3 },{ 3, 3 }));
  file_space.selection(dataspace::SelectionOperation::NOTB,
                       dataspace::Hyperslab({ 0, 0 },{ 1, 1 },{ 2, 3 },{ 3, 3 }));


  /*
   * Write the data to the dataset.
   */
  Int32Matrix matrix(1);
  std::cout<<"Original data: "<<std::endl<<matrix<<std::endl;

  dset.write (matrix,datatype::create<Int32Matrix>(),file_space,file_space);

}

void read_data()
{
  file::File file = file::open(FILE,file::AccessFlags::READONLY);
  node::Dataset dset = file.root()[DATASET];

  property::DatasetCreationList dcpl = dset.creation_list();
  std::cout<<"Dataset layout: "<<dcpl.layout()<<std::endl;

  Int32Matrix matrix;
  dset.read(matrix);
  std::cout<<std::endl<<matrix<<std::endl;

  matrix = Int32Matrix(0); //reinit array
  dataspace::Simple file_space = dset.dataspace();
  file_space.selection(dataspace::SelectionOperation::SET,dataspace::Hyperslab({0,1},{2,3},{2,2},{4,4}));
  dset.read(matrix,datatype::create<Int32Matrix>(),file_space,file_space);
  std::cout<<matrix<<std::endl;
}

int
main (void)
{
    write_data();
    read_data();

    return 0;
}
