/************************************************************

  This example shows how to read and write data to a dataset
  using the shuffle filter with gzip compression.  The
  program first checks if the shuffle and gzip filters are
  available, then if they are it writes integers to a
  dataset using shuffle+gzip, then closes the file.  Next,
  it reopens the file, reads back the data, and outputs the
  types of filters and the maximum value in the dataset to
  the screen.

  This file is intended for use with HDF5 Library version 1.8

 ************************************************************/

#include <h5cpp/hdf5.hpp>
#include "matrix_hdf5.hpp"
#include <algorithm>

#define FILE            "h5ex_d_shuffle.h5"
#define DATASET         "DS1"
#define DIM0            32
#define DIM1            64
#define CHUNK0          4
#define CHUNK1          8

using namespace hdf5;
using Int32Matrix = Matrix<int32_t,DIM0,DIM1>;

void write()
{
  filter::Shuffle shuffle_filter;
  filter::Deflate deflate_filter;
  deflate_filter.level(9);

  Int32Matrix wdata;
  // Initialize data.
  for (size_t i=0; i<DIM0; i++)
    for (size_t j=0; j<DIM1; j++)
        wdata(i,j) = i * j - j;

  // Create a new file using the default properties.
  file::File file = file::create (FILE, file::AccessFlags::TRUNCATE);


  // Create dataspace.  Setting maximum size to NULL sets the maximum
  // size to be the current size.
  dataspace::Simple space ({ DIM0, DIM1 });

  // Create the dataset creation property list, add the shuffle
  // filter and the gzip compression filter and set the chunk size.
  // The order in which the filters are added here is significant -
  // we will see much greater results when the shuffle is applied
  // first.  The order in which the filters are added to the property
  // list is the order in which they will be invoked when writing
  // data.
  property::LinkCreationList lcpl;
  property::DatasetCreationList dcpl;
  shuffle_filter (dcpl);
  deflate_filter (dcpl);
  dcpl.layout (property::DatasetLayout::CHUNKED);
  dcpl.chunk ({ CHUNK0, CHUNK1 });

  // Create the dataset.
  node::Dataset dset (file.root (), DATASET, datatype::create<int32_t> (),
                      space, lcpl, dcpl);

  // Write the data to the dataset.
  dset.write (wdata);
}

void read()
{
  // Open file and dataset using the default properties.
  file::File file = file::open (FILE,file::AccessFlags::READONLY);
  node::Dataset dset = file.root().nodes[DATASET];

  // Retrieve dataset creation property list
  property::DatasetCreationList dcpl = dset.creation_list();

  // Retrieve the number of filters, and retrieve and print the
  // type of each.
  unsigned int flags,filter_info;
  int nfilters = H5Pget_nfilters (static_cast<hid_t>(dcpl));
  for (int i=0; i<nfilters; i++) {
    size_t nelmts = 0;
    int filter_type = H5Pget_filter (static_cast<hid_t>(dcpl), i, &flags, &nelmts, NULL, 0, NULL,
                                 &filter_info);
    std::cout<< "Filter "<<i<<": Type is: ";
    switch (filter_type)
      {
      case H5Z_FILTER_DEFLATE: std::cout<<"H5Z_FILTER_DEFLATE"<<std::endl;
        break;
      case H5Z_FILTER_SHUFFLE: std::cout<<"H5Z_FILTER_SHUFFLE"<<std::endl;
        break;
      case H5Z_FILTER_FLETCHER32: std::cout<<"H5Z_FILTER_FLETCHER32"<<std::endl;
        break;
      case H5Z_FILTER_SZIP: std::cout<<"H5Z_FILTER_SZIP"<<std::endl;
        break;
      case H5Z_FILTER_NBIT: std::cout<<"H5Z_FILTER_NBIT"<<std::endl;
        break;
      case H5Z_FILTER_SCALEOFFSET: std::cout<<"H5Z_FILTER_SCALEOFFSET"<<std::endl;
      }
  }

  /*
   * Read the data using the default properties.
   */
  Int32Matrix rdata;
  dset.read(rdata);

  /*
   * Find the maximum value in the dataset, to verify that it was
   * read correctly.
   */
  int32_t max_value = *std::max_element(rdata.begin(),rdata.end());

  /*
   * Print the maximum value.
   */
  std::cout<<"Maximum value in "<<DATASET<<" is: "<<max_value<<std::endl;
  std::cout<<rdata<<std::endl;


}

int main (void)
{
  write();
  read();
  return 0;
}
