#include <hdf5.h>

#define BOOST_TEST_MODULE MyTest
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#define FILE1 "file1.h5"
#define FILE2 "file2.h5"

// copy file, see if id's are the same
// external link vs. native path
// file & symbolic link

struct IdInfo
{
  IdInfo(hid_t object)
  {
    std::vector<char> namec;
    H5O_info_t info;
    H5Oget_info(object, &info);
    ssize_t size = H5Fget_name(object, NULL, 0);
    namec.resize(size + 2, '\0');
    size = H5Fget_name(object, namec.data(), size);
    file_name = std::string(namec.data());
    file_num = info.fileno;
    obj_addr = info.addr;
  }

  std::string    file_name;
  unsigned long  file_num;
  haddr_t        obj_addr;
};

struct OneFile
{
  OneFile(std::string fname)
  {
    fname_ = fname;
    file = H5Fcreate(fname.data(), H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    group1 = H5Gcreate(file, "/group1",
                       H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
    group2 = H5Gcreate(file, "/group2",
                       H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);

    hsize_t dims[2];
    dims[0] = 3;
    dims[1] = 3;
    hid_t dataspace = H5Screate_simple(2, dims, NULL);

    dset1 = H5Dcreate(group1, "dset1", H5T_NATIVE_DOUBLE, dataspace,
                      H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
  }

  ~OneFile()
  {
    H5Dclose(dset1);
    H5Gclose(group1);
    H5Gclose(group2);
    H5Fclose(file);
    boost::filesystem::remove(fname_);
  }

  std::string fname_;
  hid_t file, group1, group2, dset1;
};

BOOST_AUTO_TEST_CASE( hard_group )
{
  OneFile file(FILE1);

  H5Lcreate_hard(file.file, "/group1",
                 file.file, "/group3",
                 H5P_DEFAULT, H5P_DEFAULT);
  hid_t group3 = H5Gopen(file.file, "/group3", H5P_DEFAULT);

  IdInfo info1(file.group1);
  IdInfo info2(group3);

  BOOST_CHECK_NE(file.group1, group3);
  BOOST_CHECK_EQUAL(info1.file_name, info2.file_name);
  BOOST_CHECK_EQUAL(info1.file_num, info2.file_num);
  BOOST_CHECK_EQUAL(info1.obj_addr, info1.obj_addr);

  H5Gclose(group3);
}

BOOST_AUTO_TEST_CASE( hard_dset )
{
  OneFile file(FILE1);

  H5Lcreate_hard(file.group1, "dset1",
                 file.group2, "dset2",
                 H5P_DEFAULT, H5P_DEFAULT);
  hid_t dset2 = H5Dopen(file.group2, "dset2", H5P_DEFAULT);

  IdInfo info1(file.dset1);
  IdInfo info2(dset2);

  BOOST_CHECK_NE(file.dset1, dset2);
  BOOST_CHECK_EQUAL(info1.file_name, info2.file_name);
  BOOST_CHECK_EQUAL(info1.file_num, info2.file_num);
  BOOST_CHECK_EQUAL(info1.obj_addr, info1.obj_addr);

  H5Dclose(dset2);
}

BOOST_AUTO_TEST_CASE( soft_group )
{
  OneFile file(FILE1);

  H5Lcreate_soft("/group1", file.file, "/group3",
                 H5P_DEFAULT, H5P_DEFAULT);
  hid_t group3 = H5Gopen(file.file, "/group3", H5P_DEFAULT);

  IdInfo info1(file.group1);
  IdInfo info2(group3);

  BOOST_CHECK_NE(file.group1, group3);
  BOOST_CHECK_EQUAL(info1.file_name, info2.file_name);
  BOOST_CHECK_EQUAL(info1.file_num, info2.file_num);
  BOOST_CHECK_EQUAL(info1.obj_addr, info1.obj_addr);

  H5Gclose(group3);
}

BOOST_AUTO_TEST_CASE( soft_dset )
{
  OneFile file(FILE1);

  H5Lcreate_soft("/group1/dset1", file.file, "/group2/dset2",
                 H5P_DEFAULT, H5P_DEFAULT);
  hid_t dset2 = H5Dopen(file.group2, "dset2", H5P_DEFAULT);

  IdInfo info1(file.dset1);
  IdInfo info2(dset2);

  BOOST_CHECK_NE(file.dset1, dset2);
  BOOST_CHECK_EQUAL(info1.file_name, info2.file_name);
  BOOST_CHECK_EQUAL(info1.file_num, info2.file_num);
  BOOST_CHECK_EQUAL(info1.obj_addr, info1.obj_addr);

  H5Dclose(dset2);
}
