#include <cstdlib>
#include <hdf5.h>

#define BOOST_TEST_MODULE MyTest
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#define FILE "file.h5"

// single file, multiple paths to same node
// copy file, see if id's are the same
// external link vs. native path
// file & symbolic link

BOOST_AUTO_TEST_CASE( my_test )
{
  hid_t file_id =
      H5Fcreate(FILE, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);

  herr_t status = H5Fclose(file_id);

  BOOST_CHECK_GE(status, 0);

  boost::filesystem::remove(FILE);
}
