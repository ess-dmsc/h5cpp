#include <hdf5.h>
#include <gtest/gtest.h>

#define FILE "file.h5"

TEST(UniqueID, Test1)
{
   hid_t       file_id;   /* file identifier */
   herr_t      status;

   /* Create a new file using default properties. */
   file_id = H5Fcreate(FILE, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);

   /* Terminate access to the file. */
   status = H5Fclose(file_id); 
}
