/************************************************************

  This example shows how to read and write array datatypes
  to a dataset.  The program first writes integers arrays of
  dimension ADIM0xADIM1 to a dataset with a dataspace of
  DIM0, then closes the  file.  Next, it reopens the file,
  reads back the data, and outputs it to the screen.

  This file is intended for use with HDF5 Library version 1.8

 ************************************************************/

#include <h5cpp/hdf5.hpp>
#include <vector>
#include <algorithm>
#include "t_array.hpp"

#define FILE            "h5ex_t_array.h5"
#define DATASET         "DS1"

#define DIM0            4
#define ADIM0           3
#define ADIM1           5

using namespace hdf5;
using Int32Item = DataItem<int32_t,ADIM0,ADIM1>;
using Int32Items = std::vector<Int32Item>;

void write_data()
{
  // Initialize data.  i is the element in the dataspace, j and k the
  // elements within the array datatype.
  Int32Items wdata(DIM0);
  for (int32_t i=0; i<DIM0; i++)
      for (int32_t j=0; j<ADIM0; j++)
          for (int32_t k=0; k<ADIM1; k++)
              wdata[i](j,k) = i * j - j * k + i * k;

  // Create a new file using the default properties.
  file::File file = file::create (FILE, file::AccessFlags::TRUNCATE);

  // Create array datatypes for file and memory.
  datatype::Array filetype = datatype::Array::create(datatype::create<int64_t>(),{ADIM0,ADIM1});

  // Create dataspace.  Setting maximum size to NULL sets the maximum
  // size to be the current size.
  dataspace::Simple space({DIM0});

  // Create the dataset and write the array data to it.
  node::Dataset dset(file.root(), DATASET, filetype, space);
  std::cout<<"Write data"<<std::endl;
  std::for_each(wdata.begin(),wdata.end(),
  [](const Int32Item &item) { std::cout<<item<<std::endl; }
  );

  dset.write(wdata);
}

void read_data()
{
  // Open file and dataset.
  file::File file = file::open (FILE, file::AccessFlags::READONLY);
  node::Dataset dset = file.root().nodes[DATASET];

  // Get the datatype and its dimensions.
  datatype::Array filetype = dset.datatype ();

  // Get dataspace and allocate memory for read buffer.  This is a
  // three dimensional dataset when the array datatype is included so
  // the dynamic allocation must be done in steps.
  dataspace::Simple space = dset.dataspace ();

  // Allocate array of pointers to two-dimensional arrays (the
  // elements of the dataset.
  Int32Items rdata(space.size());

  // Read the data.
  dset.read(rdata);

  // Output the data to the screen.
  std::for_each(rdata.begin(),rdata.end(),
                [](const Int32Item &item) { std::cout<<item<<std::endl; });
}

int main (void)
{
  write_data();

  // Now we begin the read section of this example.  Here we assume
  // the dataset and array have the same name and rank, but can have
  // any size.  Therefore we must allocate a new array to read in
  // data using malloc().
  std::cout<<"Read data"<<std::endl;
  read_data();

  return 0;
}
