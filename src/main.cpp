#include <iostream>
#include "id.hpp"
#include "context.hpp"


#define BOOST_TEST_MODULE MyTest
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

// path will be absolute in external links, so to compare correctly, all paths should be made absolute
// symlinks should be dereferenced too, though file_num will reflect identity

#define FILE1 boost::filesystem::absolute("file1.h5").string().data()
#define FILE2 boost::filesystem::absolute("file2.h5").string().data()

using namespace h5;

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

  id info1(file.group1);
  id info2(group3);

  BOOST_CHECK_NE(file.group1, group3);
  BOOST_CHECK_EQUAL(info1.file_name(), info2.file_name());
  BOOST_CHECK_EQUAL(info1.file_num(), info2.file_num());
  BOOST_CHECK_EQUAL(info1.obj_addr(), info1.obj_addr());

  H5Gclose(group3);
  boost::filesystem::remove(FILE1);
}

BOOST_AUTO_TEST_CASE( hard_dset )
{
  OneFile file(FILE1);

  H5Lcreate_hard(file.group1, "dset1",
                 file.group2, "dset2",
                 H5P_DEFAULT, H5P_DEFAULT);
  hid_t dset2 = H5Dopen(file.group2, "dset2", H5P_DEFAULT);

  id info1(file.dset1);
  id info2(dset2);

  BOOST_CHECK_NE(file.dset1, dset2);
  BOOST_CHECK_EQUAL(info1.file_name(), info2.file_name());
  BOOST_CHECK_EQUAL(info1.file_num(), info2.file_num());
  BOOST_CHECK_EQUAL(info1.obj_addr(), info1.obj_addr());

  H5Dclose(dset2);
  boost::filesystem::remove(FILE1);
}

BOOST_AUTO_TEST_CASE( soft_group )
{
  OneFile file(FILE1);

  H5Lcreate_soft("/group1", file.file, "/group3",
                 H5P_DEFAULT, H5P_DEFAULT);
  hid_t group3 = H5Gopen(file.file, "/group3", H5P_DEFAULT);

  id info1(file.group1);
  id info2(group3);

  BOOST_CHECK_NE(file.group1, group3);
  BOOST_CHECK_EQUAL(info1.file_name(), info2.file_name());
  BOOST_CHECK_EQUAL(info1.file_num(), info2.file_num());
  BOOST_CHECK_EQUAL(info1.obj_addr(), info1.obj_addr());

  H5Gclose(group3);
  boost::filesystem::remove(FILE1);
}

BOOST_AUTO_TEST_CASE( soft_dset )
{
  OneFile file(FILE1);

  H5Lcreate_soft("/group1/dset1", file.file, "/group2/dset2",
                 H5P_DEFAULT, H5P_DEFAULT);
  hid_t dset2 = H5Dopen(file.group2, "dset2", H5P_DEFAULT);

  id info1(file.dset1);
  id info2(dset2);

  BOOST_CHECK_NE(file.dset1, dset2);
  BOOST_CHECK_EQUAL(info1.file_name(), info2.file_name());
  BOOST_CHECK_EQUAL(info1.file_num(), info2.file_num());
  BOOST_CHECK_EQUAL(info1.obj_addr(), info1.obj_addr());

  H5Dclose(dset2);
  boost::filesystem::remove(FILE1);
}

BOOST_AUTO_TEST_CASE( file_copy )
{
  OneFile* file = new OneFile(FILE1);
  delete file;

  boost::filesystem::copy_file(FILE1, FILE2,
                               boost::filesystem::copy_option::overwrite_if_exists);

  hid_t file1 = H5Fopen(FILE1, H5F_ACC_RDONLY, H5P_DEFAULT);
  hid_t file2 = H5Fopen(FILE2, H5F_ACC_RDONLY, H5P_DEFAULT);
  hid_t group1 = H5Gopen(file1, "/group1", H5P_DEFAULT);
  hid_t group2 = H5Gopen(file2, "/group1", H5P_DEFAULT);

  id info1(group1);
  id info2(group2);

  BOOST_CHECK_NE(group1, group2);
  BOOST_CHECK_NE(info1.file_name(), info2.file_name());
  BOOST_CHECK_NE(info1.file_num(), info2.file_num());
  BOOST_CHECK_EQUAL(info1.obj_addr(), info1.obj_addr());

  H5Gclose(group1);
  H5Gclose(group2);
  H5Fclose(file1);
  H5Fclose(file2);
  boost::filesystem::remove(FILE1);
  boost::filesystem::remove(FILE2);
}

BOOST_AUTO_TEST_CASE( file_copy2 )
{
  OneFile* file;
  file = new OneFile(FILE1);
  delete file;

  file = new OneFile(FILE2);
  delete file;

  hid_t file1 = H5Fopen(FILE1, H5F_ACC_RDONLY, H5P_DEFAULT);
  hid_t file2 = H5Fopen(FILE2, H5F_ACC_RDONLY, H5P_DEFAULT);
  hid_t group1 = H5Gopen(file1, "/group1", H5P_DEFAULT);
  hid_t group2 = H5Gopen(file2, "/group1", H5P_DEFAULT);

  id info1(group1);
  id info2(group2);

  BOOST_CHECK_NE(group1, group2);
  BOOST_CHECK_NE(info1.file_name(), info2.file_name());
  BOOST_CHECK_NE(info1.file_num(), info2.file_num());
  BOOST_CHECK_EQUAL(info1.obj_addr(), info1.obj_addr());

  H5Gclose(group1);
  H5Gclose(group2);
  H5Fclose(file1);
  H5Fclose(file2);
  boost::filesystem::remove(FILE1);
  boost::filesystem::remove(FILE2);
}

BOOST_AUTO_TEST_CASE( symlink_id )
{
  OneFile* file = new OneFile(FILE1);
  delete file;

  boost::filesystem::create_symlink(FILE1, FILE2);

  hid_t file1 = H5Fopen(FILE1, H5F_ACC_RDONLY, H5P_DEFAULT);
  hid_t file2 = H5Fopen(FILE2, H5F_ACC_RDONLY, H5P_DEFAULT);
  hid_t group1 = H5Gopen(file1, "/group1", H5P_DEFAULT);
  hid_t group2 = H5Gopen(file2, "/group1", H5P_DEFAULT);

  id info1(group1);
  id info2(group2);

  BOOST_CHECK_NE(group1, group2);
  BOOST_CHECK_NE(info1.file_name(), info2.file_name());
  BOOST_CHECK_EQUAL(info1.file_num(), info2.file_num());
  BOOST_CHECK_EQUAL(info1.obj_addr(), info1.obj_addr());

  BOOST_CHECK_EQUAL(boost::filesystem::canonical(FILE1),
                    boost::filesystem::canonical(FILE2));

  H5Gclose(group1);
  H5Gclose(group2);
  H5Fclose(file1);
  H5Fclose(file2);
  boost::filesystem::remove(FILE1);
  boost::filesystem::remove(FILE2);
}

BOOST_AUTO_TEST_CASE( file_external_group )
{
  OneFile* file1 = new OneFile(FILE1);
  OneFile* file2 = new OneFile(FILE2);

  H5Lcreate_external(FILE1, "/group1",
                     file2->file, "/group3",
                     H5P_DEFAULT, H5P_DEFAULT);

  hid_t group11 = H5Gopen(file1->file, "/group1", H5P_DEFAULT);
  hid_t group12 = H5Gopen(file1->file, "/group2", H5P_DEFAULT);
  hid_t group21 = H5Gopen(file2->file, "/group1", H5P_DEFAULT);
  hid_t group23 = H5Gopen(file2->file, "/group3", H5P_DEFAULT);

  id info11(group11);
  id info12(group12);
  id info21(group21);
  id info23(group23);

//  info11.print("f1/g1");
//  info12.print("f1/g2");
//  info21.print("f2/g1");
//  info23.print("f2/LL");

  BOOST_CHECK_NE(group11, group12);
  BOOST_CHECK_NE(group11, group21);
  BOOST_CHECK_NE(group11, group23);
  BOOST_CHECK_NE(group12, group21);
  BOOST_CHECK_NE(group12, group23);
  BOOST_CHECK_NE(group21, group23);

  BOOST_CHECK_EQUAL(info11.file_name(), info12.file_name());
  BOOST_CHECK_NE(info11.file_name(), info21.file_name());
  BOOST_CHECK_EQUAL(info11.file_name(), info23.file_name());
  BOOST_CHECK_NE(info12.file_name(), info21.file_name());
  BOOST_CHECK_EQUAL(info12.file_name(), info23.file_name());
  BOOST_CHECK_NE(info21.file_name(), info23.file_name());

  BOOST_CHECK_EQUAL(info11.file_num(), info12.file_num());
  BOOST_CHECK_EQUAL(info11.file_num(), info23.file_num());
  BOOST_CHECK_EQUAL(info12.file_num(), info23.file_num());
  BOOST_CHECK_NE(info21.file_num(), info23.file_num());

  BOOST_CHECK_EQUAL(info11.obj_addr(), info23.obj_addr());
  BOOST_CHECK_NE(info11.obj_addr(), info12.obj_addr());
  BOOST_CHECK_EQUAL(info11.obj_addr(), info21.obj_addr());
  BOOST_CHECK_NE(info12.obj_addr(), info21.obj_addr());
  BOOST_CHECK_NE(info12.obj_addr(), info23.obj_addr());
  BOOST_CHECK_EQUAL(info21.obj_addr(), info23.obj_addr());

  H5Gclose(group11);
  H5Gclose(group12);
  H5Gclose(group21);
  H5Gclose(group23);

  delete file1;
  delete file2;

  boost::filesystem::remove(FILE1);
  boost::filesystem::remove(FILE2);
}

BOOST_AUTO_TEST_CASE( repeated_open )
{
  OneFile* file = new OneFile(FILE1);
  id i1(file->file);
  delete file;

  file = new OneFile(FILE1);
  id i2(file->file);
  delete file;

  BOOST_CHECK_EQUAL(i1.file_name(), i2.file_name());
  BOOST_CHECK_NE(i1.file_num(), i2.file_num());
  std::cout << i1 << "   ??   " << i2 << std::endl;
}
