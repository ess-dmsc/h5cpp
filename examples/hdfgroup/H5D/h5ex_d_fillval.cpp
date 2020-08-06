/************************************************************

  This example shows how to set the fill value for a
  dataset.  The program first sets the fill value to
  FILLVAL, creates a dataset with dimensions of DIM0xDIM1,
  reads from the uninitialized dataset, and outputs the
  contents to the screen.  Next, it writes integers to the
  dataset, reads the data back, and outputs it to the
  screen.  Finally it extends the dataset, reads from it,
  and outputs the result to the screen.

  This file is intended for use with HDF5 Library version 1.8

 ************************************************************/

#include <h5cpp/hdf5.hpp>
#include "matrix_hdf5.hpp"

#define FILE            "h5ex_d_fillval.h5"
#define DATASET         "DS1"
#define DIM0            4
#define DIM1            7
#define EDIM0           6
#define EDIM1           10
#define CHUNK0          4
#define CHUNK1          4
#define FILLVAL         99

using namespace hdf5;
using Int32Matrix = Matrix<int32_t,DIM0,DIM1>;

int
main (void)
{
    Int32Matrix rdata,wdata;
    Matrix<int32_t,EDIM0,EDIM1> rdata2;
    /*
     * Initialize data.
     */
    for (size_t i=0; i<DIM0; i++)
        for (size_t j=0; j<DIM1; j++)
            wdata(i,j) = i * j - j;

    /*
     * Create a new file using the default properties.
     */
    file::File file = file::create(FILE, file::AccessFlags::TRUNCATE);

    /*
     * Create dataspace with unlimited dimensions.
     */
    dataspace::Simple space({DIM0,DIM1},
                            {dataspace::Simple::UNLIMITED,
                             dataspace::Simple::UNLIMITED});

    /*
     * Create the dataset creation property list, and set the chunk
     * size.
     */
    property::LinkCreationList lcpl;
    property::DatasetCreationList dcpl;
    dcpl.layout(property::DatasetLayout::CHUNKED);
    dcpl.chunk({CHUNK0,CHUNK1});

    /*
     * Set the fill value for the dataset.
     */
    dcpl.fill_value(int32_t(FILLVAL),datatype::create<int32_t>());

    /*
     * Set the allocation time to "early".  This way we can be sure
     * that reading from the dataset immediately after creation will
     * return the fill value.
     */
    dcpl.allocation_time(property::DatasetAllocTime::EARLY);

    /*
     * Create the dataset using the dataset creation property list.
     */
    node::Dataset dset(file.root(),DATASET,datatype::create<int32_t>(),space,lcpl,dcpl);
    /*
     * Read values from the dataset, which has not been written to yet.
     */
    dset.read(rdata);
    std::cout<<"Dataset before being written to:"<<std::endl;
    std::cout<<rdata<<std::endl;

    /*
     * Write the data to the dataset.
     */
    dset.write(wdata);

    /*
     * Read the data back.
     */
    dset.read(rdata);

    /*
     * Output the data to the screen.
     */
    std::cout<<std::endl<<"Dataset after being written to:"<<std::endl;
    std::cout<<rdata<<std::endl;


    /*
     * Extend the dataset.
     */
    dset.extent({EDIM0,EDIM1});


    /*
     * Read from the extended dataset.
     */
    dset.read(rdata2);

    /*
     * Output the data to the screen.
     */
    std::cout<<std::endl<<"Dataset after extension:"<<std::endl;
    std::cout<<rdata2<<std::endl;


    return 0;
}
