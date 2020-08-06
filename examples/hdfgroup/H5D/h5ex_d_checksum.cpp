/************************************************************

  This example shows how to read and write data to a dataset
  using the Fletcher32 checksum filter.  The program first
  checks if the Fletcher32 filter is available, then if it
  is it writes integers to a dataset using Fletcher32, then
  closes the file.  Next, it reopens the file, reads back
  the data, checks if the filter detected an error and
  outputs the type of filter and the maximum value in the
  dataset to the screen.

  This file is intended for use with HDF5 Library version 1.8

 ************************************************************/

#include <h5cpp/hdf5.hpp>
#include <array>
#include <algorithm>
#include "matrix_hdf5.hpp"

#define FILE            "h5ex_d_checksum.h5"
#define DATASET         "DS1"
#define DIM0            32
#define DIM1            64
#define CHUNK0          4
#define CHUNK1          8

using Int32Matrix = Matrix<int32_t,DIM0,DIM1>;

int32_t generator()
{
  static size_t i = 0;
  static size_t j = 0;

  i = i<DIM0 ? i++ : 0;
  j = j<DIM1 ? j++ : 0;

  return i*j-j;
}

using namespace hdf5;

void write_data()
{
    Int32Matrix  matrix;
    std::generate(matrix.begin(),matrix.end(),generator);
    std::cout<<matrix<<std::endl;
    /*
     * Create a new file using the default properties.
     */
    file::File file = file::create(FILE,file::AccessFlags::TRUNCATE);

    /*
     * Create dataspace.  Setting maximum size to NULL sets the maximum
     * size to be the current size.
     */
    dataspace::Simple space({DIM0,DIM1});

    /*
     * Create the dataset creation property list, add the Fletcher32 filter
     * and set the chunk size.
     */
    property::LinkCreationList lcpl;
    property::DatasetCreationList dcpl;
    filter::Fletcher32 fletcher32;
    fletcher32(dcpl);
    dcpl.layout(property::DatasetLayout::CHUNKED);
    dcpl.chunk(Dimensions{CHUNK0,CHUNK1});


    /*
     * Create the dataset and write data to disk
     */
    node::Dataset dset(file.root(),DATASET,datatype::create<int32_t>(),space,lcpl,dcpl);
    dset.write(matrix);
}

void read_data()
{

   /*
    * Open file and dataset using the default properties.
    */
   file::File file = file::open(FILE,file::AccessFlags::READONLY);
   node::Dataset dset = file.root()[DATASET];

   /*
    * Retrieve dataset creation property list.
    */
   property::DatasetCreationList dcpl = dset.creation_list();

   /*
    * Retrieve and print the filter type.  Here we only retrieve the
    * first filter because we know that we only added one filter.
    */
   size_t nelmts = 0;
   unsigned int flags = 0, filter_info = 0;
   H5Z_filter_t filter_type = H5Pget_filter (static_cast<hid_t>(dcpl), 0,
                                             &flags, &nelmts, NULL, 0, NULL,
                                             &filter_info);
   printf ("Filter type is: ");
   switch (filter_type) {
       case H5Z_FILTER_DEFLATE:
           printf ("H5Z_FILTER_DEFLATE\n");
           break;
       case H5Z_FILTER_SHUFFLE:
           printf ("H5Z_FILTER_SHUFFLE\n");
           break;
       case H5Z_FILTER_FLETCHER32:
           printf ("H5Z_FILTER_FLETCHER32\n");
           break;
       case H5Z_FILTER_SZIP:
           printf ("H5Z_FILTER_SZIP\n");
           break;
       case H5Z_FILTER_NBIT:
           printf ("H5Z_FILTER_NBIT\n");
           break;
       case H5Z_FILTER_SCALEOFFSET:
           printf ("H5Z_FILTER_SCALEOFFSET\n");
   }

   /*
    * Read the data using the default properties.
    */
   Int32Matrix matrix;
   dset.read(matrix);
   std::cout<<matrix<<std::endl;

   /*
    * Check if the read was successful.  Normally we do not perform
    * error checking in these examples for the sake of clarity, but in
    * this case we will make an exception because this is how the
    * fletcher32 checksum filter reports data errors.
    */
    //We somehow need to introduce some error checking here - at best we
    //could somehow manipulate the data to force some error reporting.

}

int
main (void)
{
    /*
     * Check if the Fletcher32 filter is available and can be used for
     * both encoding and decoding.  Normally we do not perform error
     * checking in these examples for the sake of clarity, but in this
     * case we will make an exception because this filter is an
     * optional part of the hdf5 library.
     */
    htri_t avail = H5Zfilter_avail(H5Z_FILTER_FLETCHER32);
    unsigned int filter_info;
    if (!avail) {
        printf ("Fletcher32 filter not available.\n");
        return 1;
    }
    herr_t status = H5Zget_filter_info (H5Z_FILTER_FLETCHER32, &filter_info);
    if ( !(filter_info & H5Z_FILTER_CONFIG_ENCODE_ENABLED) ||
                !(filter_info & H5Z_FILTER_CONFIG_DECODE_ENABLED) ) {
        printf ("Fletcher32 filter not available for encoding and decoding.\n");
        return 1;
    }

    /*
     * Initialize data.
     */

    write_data();
    /*
     * Now we begin the read section of this example.
     */
    read_data();



    return 0;
}
