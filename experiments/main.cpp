#include <hdf5.h>

#define BOOST_TEST_MODULE MyTest
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#define FILE "file.h5"

// single file, multiple paths to same node
// copy file, see if id's are the same
// external link vs. native path
// file & symbolic link

BOOST_AUTO_TEST_CASE( hard_link )
{
//  herr_t status;

  hid_t file_id =
      H5Fcreate(FILE, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);

  hid_t group1 = H5Gcreate(file_id, "/group1",
                           H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);

  hsize_t dims[2];
  dims[0] = 4;
  dims[1] = 6;
  hid_t dataspace = H5Screate_simple(2, dims, NULL);

  hid_t dset1 = H5Dcreate(group1, "dset1", H5T_NATIVE_DOUBLE, dataspace,
                         H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);


  hid_t group2 = H5Gcreate(file_id, "/group2",
                           H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);

  herr_t lstatus = H5Lcreate_hard(group1, "dset1", group2, "dset2",
                                 H5P_DEFAULT, H5P_DEFAULT);
  BOOST_CHECK_GE(lstatus, 0);

  hid_t dset2 = H5Dopen2(group2, "dset2", H5P_DEFAULT);

  H5O_info_t info1;
  herr_t istatus1 = H5Oget_info(dset1, &info1);
  BOOST_CHECK_GE(istatus1, 0);
  ssize_t size1 = H5Fget_name(dset1, NULL, 0);
  std::vector<char> name1c;
  name1c.resize(size1 + 2, '\0');
  size1 = H5Fget_name(dset1, name1c.data(), size1);
  std::string name1(name1c.data());

  H5O_info_t info2;
  herr_t istatus2 = H5Oget_info(dset2, &info2);
  BOOST_CHECK_GE(istatus2, 0);
  ssize_t size2 = H5Fget_name(dset2, NULL, 0);
  std::vector<char> name2c;
  name2c.resize(size2 + 2, '\0');
  size2 = H5Fget_name(dset2, name2c.data(), size2);
  std::string name2(name2c.data());

  BOOST_CHECK_NE(dset1, dset2);
  BOOST_CHECK_EQUAL(info1.addr, info2.addr);
  BOOST_CHECK_EQUAL(name1, name2);

  BOOST_CHECK_GE(H5Dclose(dset2), 0);
  BOOST_CHECK_GE(H5Gclose(group2), 0);

  BOOST_CHECK_GE(H5Dclose(dset1), 0);
  BOOST_CHECK_GE(H5Gclose(group1), 0);

  BOOST_CHECK_GE(H5Fclose(file_id), 0);
//  boost::filesystem::remove(FILE);
}
