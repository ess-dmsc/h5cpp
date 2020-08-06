/************************************************************

  This example shows how to read and write array datatypes
  to an attribute.  The program first writes integers arrays
  of dimension ADIM0xADIM1 to an attribute with a dataspace
  of DIM0, then closes the  file.  Next, it reopens the
  file, reads back the data, and outputs it to the screen.

  This file is intended for use with HDF5 Library version 1.8

 ************************************************************/

#include <h5cpp/hdf5.hpp>
#include <vector>
#include <algorithm>
#include "t_array.hpp"

#define FILE            "h5ex_t_arrayatt.h5"
#define DATASET         "DS1"
#define ATTRIBUTE       "A1"
#define DIM0            4
#define ADIM0           3
#define ADIM1           5

using namespace hdf5;
using Int32Item = DataItem<int32_t,ADIM0,ADIM1>;
using Int32Items = std::vector<Int32Item>;

void write_attribute()
{
  // Initialize data.  i is the element in the dataspace, j and k the
  // elements within the array datatype.
  Int32Items wdata(DIM0);
  for (int32_t i = 0; i < DIM0; i++)
    for (int32_t j = 0; j < ADIM0; j++)
      for (int32_t k = 0; k < ADIM1; k++)
        wdata[i](j,k) = i * j - j * k + i * k;


  // Create a new file using the default properties.
  file::File file = file::create (FILE, file::AccessFlags::TRUNCATE);

  // Create array datatypes for file and memory.
  datatype::Array filetype = datatype::Array::create (datatype::create<int>(),{ADIM0,ADIM1});

  // Create dataspace.  Setting maximum size to NULL sets the maximum
  // size to be the current size.
  dataspace::Simple space({DIM0});

  // Create the attribute and write the array data to it.
  attribute::Attribute attribute = file.root().attributes.create(ATTRIBUTE,filetype,space);
  attribute.write(wdata);
}

void read_attribute()
{
  // Open file, dataset, and attribute.
  file::File file = file::open (FILE, file::AccessFlags::READONLY);
  attribute::Attribute attribute = file.root().attributes[ATTRIBUTE];

  // Get the datatype and its dimensions.
  datatype::Array filetype = attribute.datatype();

  // Get dataspace and allocate memory for read buffer.  This is a
  // three dimensional attribute when the array datatype is included
  // so the dynamic allocation must be done in steps.
  dataspace::Simple space = attribute.dataspace();

  // Allocate array of pointers to two-dimensional arrays (the
  // elements of the attribute.
  Int32Items rdata(space.size());

  // Read the data.
  attribute.read(rdata);
  std::for_each(rdata.begin(),rdata.end(),
                [](const Int32Item &item) { std::cout<<item<<std::endl;});
}

int main (void)
{
  write_attribute();
  read_attribute();

  return 0;
}
