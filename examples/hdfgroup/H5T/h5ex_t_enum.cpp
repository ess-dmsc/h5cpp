/************************************************************

  This example shows how to read and write enumerated
  datatypes to a dataset.  The program first writes
  enumerated values to a dataset with a dataspace of
  DIM0xDIM1, then closes the file.  Next, it reopens the
  file, reads back the data, and outputs it to the screen.

  This file is intended for use with HDF5 Library version 1.8

 ************************************************************/

#include <h5cpp/hdf5.hpp>
#include "phase.hpp"
#include "../H5D/matrix_hdf5.hpp"
#include <vector>

#define FILE            "h5ex_t_enum.h5"
#define DATASET         "DS1"
#define DIM0            4
#define DIM1            7
#define F_BASET         H5T_STD_I16BE       /* File base type */
#define M_BASET         H5T_NATIVE_INT      /* Memory base type */
#define NAME_BUF_SIZE   16

using namespace hdf5;
using PhaseMatrix = Matrix<Phase,DIM0,DIM1>;

void write_data()
{
  // Initialize data.
  PhaseMatrix phases;
  for (unsigned char i = 0; i < DIM0; i++)
    for (unsigned char j = 0; j < DIM1; j++)
      phases(i,j) = static_cast<Phase>(((i + 1) * j - j) % ((unsigned char) (Phase::PLASMA) + 1));

  // Create a new file using the default properties.
  file::File file = file::create(FILE,file::AccessFlags::TRUNCATE);

  // Create dataspace.  Setting maximum size to NULL sets the maximum
  // size to be the current size.
  dataspace::Simple space({DIM0,DIM1});

  // Create the dataset and write the enumerated data to it.
  node::Dataset dset(file.root(), DATASET, datatype::create<Phase>(), space);
  dset.write(phases);
}

void read_data()
{
  // Open file and dataset.
  file::File file = file::open (FILE, file::AccessFlags::READONLY);
  node::Dataset dset = file.root().nodes[DATASET];

  // Get dataspace and allocate memory for read buffer.  This is a
  // two dimensional dataset so the dynamic allocation must be done
  // in steps.
  dataspace::Simple space = dset.dataspace();

  // Read the data.
  PhaseMatrix phases;
  dset.read(phases);

  // Output the data to the screen.
  std::cout<<phases<<std::endl;
}

int main (void)
{
  write_data();
  read_data();
  return 0;
}
