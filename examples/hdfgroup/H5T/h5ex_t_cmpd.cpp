/************************************************************

  This example shows how to read and write compound
  datatypes to a dataset.  The program first writes
  compound structures to a dataset with a dataspace of DIM0,
  then closes the file.  Next, it reopens the file, reads
  back the data, and outputs it to the screen.

  This file is intended for use with HDF5 Library version 1.8

 ************************************************************/

#include <h5cpp/hdf5.hpp>
#include <vector>
#include <algorithm>
#include "measurement_hdf5.hpp"

#define FILE            "h5ex_t_cmpd.h5"
#define DATASET         "DS1"
#define DIM0            4

using namespace hdf5;
using Measurements = std::vector<Measurement>;

void write_data()
{
  Measurements measurements{
    Measurement(1153,"Exterior (static)",53.23,24.57),
    Measurement(1184,"Intake",55.12,22.95),
    Measurement(1027,"Intake manifold",103.55,31.23),
    Measurement(1313,"Exhaust manifold",1252.89,84.11)
  };

  // Create a new file using the default properties.
  file::File file = file::create (FILE, file::AccessFlags::TRUNCATE);

  // Create dataspace.  Setting maximum size to NULL sets the maximum
  // size to be the current size.
  dataspace::Simple space({DIM0});

  // Create the dataset and write the compound data to it.
  node::Dataset dset(file.root(), DATASET, datatype::create<Measurement>(), space);
  dset.write(measurements);
}

void read_data()
{
  /*
   * Open file and dataset.
   */
  file::File file = file::open (FILE, file::AccessFlags::READONLY);
  node::Dataset dset = file.root().nodes[DATASET];

  /*
   * Get dataspace and allocate memory for read buffer.
   */
  dataspace::Simple file_space = dset.dataspace();
  Measurements measurements(file_space.size());

  /*
   * Read the data.
   */
  dset.read(measurements);
  std::for_each(measurements.begin(),measurements.end(),
    [](const Measurement &measurement) { std::cout<<measurement<<std::endl; }
  );

}

int main (void)
{
  write_data();
  read_data();

  return 0;
}
