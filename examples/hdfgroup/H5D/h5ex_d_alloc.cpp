/************************************************************

  This example shows how to set the space allocation time
  for a dataset.  The program first creates two datasets,
  one with the default allocation time (late) and one with
  early allocation time, and displays whether each has been
  allocated and their allocation size.  Next, it writes data
  to the datasets, and again displays whether each has been
  allocated and their allocation size.

  This file is intended for use with HDF5 Library version 1.8

 ************************************************************/

#include <h5cpp/hdf5.hpp>
#include <array>
#include <algorithm>


#define FILE            "h5ex_d_alloc.h5"
#define DATASET1        "DS1"
#define DATASET2        "DS2"
#define DIM0            4
#define DIM1            7
#define FILLVAL         99

int32_t generate()
{
  static int32_t value = 0;
  return value++;
}

using namespace hdf5;

int
main (void)
{
    std::array<int32_t,DIM0*DIM1> buffer;
    std::generate(buffer.begin(),buffer.end(),generate);

    /*
     * Create a new file using the default properties.
     */
    file::File file = file::create(FILE, file::AccessFlags::TRUNCATE);

    /*
     * Create dataspace.  Setting maximum size to NULL sets the maximum
     * size to be the current size.
     */
    dataspace::Simple space({DIM0,DIM1});

    /*
     * Create the dataset creation property list, and set the chunk
     * size.
     */
    property::DatasetCreationList dcpl;
    property::LinkCreationList lcpl;

    /*
     * Set the allocation time to "early".  This way we can be sure
     * that reading from the dataset immediately after creation will
     * return the fill value.
     */
    dcpl.allocation_time(property::DatasetAllocTime::EARLY);

    printf ("Creating datasets...\n");
    printf ("%s has allocation time H5D_ALLOC_TIME_LATE\n", DATASET1);
    printf ("%s has allocation time H5D_ALLOC_TIME_EARLY\n\n", DATASET2);

    /*
     * Create the dataset using the dataset creation property list.
     */
    node::Dataset dset1(file.root(),DATASET1,datatype::create<int32_t>(),space);
    node::Dataset dset2(file.root(),DATASET2,datatype::create<int32_t>(),space,lcpl,dcpl);

    /*
     * Retrieve and print space status and storage size for dset1.
     */
    H5D_space_status_t space_status;
    H5Dget_space_status (static_cast<hid_t>(dset1), &space_status);
    hsize_t storage_size = H5Dget_storage_size (static_cast<hid_t>(dset1));
    printf ("Space for %s has%sbeen allocated.\n", DATASET1,
                space_status == H5D_SPACE_STATUS_ALLOCATED ? " " : " not ");
    printf ("Storage size for %s is: %ld bytes.\n", DATASET1,
                (long) storage_size);

    /*
     * Retrieve and print space status and storage size for dset2.
     */
    H5Dget_space_status (static_cast<hid_t>(dset2), &space_status);
    storage_size = H5Dget_storage_size (static_cast<hid_t>(dset2));
    printf ("Space for %s has%sbeen allocated.\n", DATASET2,
                space_status == H5D_SPACE_STATUS_ALLOCATED ? " " : " not ");
    printf ("Storage size for %s is: %ld bytes.\n", DATASET2,
                (long) storage_size);

    printf ("\nWriting data...\n\n");

    /*
     * Write the data to the datasets.
     */
    dset1.write(buffer);
    dset2.write(buffer);

    /*
     * Retrieve and print space status and storage size for dset1.
     */
    H5Dget_space_status (static_cast<hid_t>(dset1), &space_status);
    storage_size = H5Dget_storage_size (static_cast<hid_t>(dset1));
    printf ("Space for %s has%sbeen allocated.\n", DATASET1,
                space_status == H5D_SPACE_STATUS_ALLOCATED ? " " : " not ");
    printf ("Storage size for %s is: %ld bytes.\n", DATASET1,
                (long) storage_size);

    /*
     * Retrieve and print space status and storage size for dset2.
     */
    H5Dget_space_status (static_cast<hid_t>(dset2), &space_status);
    storage_size = H5Dget_storage_size (static_cast<hid_t>(dset2));
    printf ("Space for %s has%sbeen allocated.\n", DATASET2,
                space_status == H5D_SPACE_STATUS_ALLOCATED ? " " : " not ");
    printf ("Storage size for %s is: %ld bytes.\n", DATASET2,
                (long) storage_size);

    return 0;
}
