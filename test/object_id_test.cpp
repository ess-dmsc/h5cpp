//
// (c) Copyright 2017 DESY,ESS
//
// This file is part of h5pp.
//
// This library is free software; you can redistribute it and/or modify it
// under the terms of the GNU Lesser General Public License as published
// by the Free Software Foundation; either version 2.1 of the License, or
// (at your option) any later version.
//
// This library is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty ofMERCHANTABILITY
// or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
// License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this library; if not, write to the
// Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor
// Boston, MA  02110-1301 USA
// ===========================================================================
//
// Author: Martin Shetty <martin.shetty@esss.se>
// Created on: Sep 13, 2017
//


/*

 Summary of test results

  hid does not uniquely identify an h5 node

  object_address is stable across all scenarios

  file_number:
     not equal if same file closed and reopened
     identifies the file that owns object, not owner of link (in case of ext link)

  file_name:
     not equal if file opened via symbolic link (h5 allows opening same file twice)
     not equal if object opened via external link vs. original node


  Conclusions:
    file_number adequately reflects identity, unless file has been closed and reopened.
    file_name does not adequately reflect identity. Resolving symbolic link would solve
    part of the problem, but would also need to somehow dereference external links to
    identify the name of the object-owning file.

*/


#include <gtest/gtest.h>

#include <boost/filesystem.hpp>

#include <h5cpp/object_id.hpp>
#include <iostream>

namespace fs = boost::filesystem;

#define FILE1 fs::absolute("file1.h5").string().data()
#define FILE2 fs::absolute("file2.h5").string().data()
#define FILE3 fs::absolute("file3.h5").string().data()

using namespace hdf5;

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

// For h5 hard links (to group):
//   file_name, file_number and address are all equal
TEST(ObjectId,  hard_group )
{
  OneFile file(FILE1);

  H5Lcreate_hard(file.file, "/group1",
                 file.file, "/group3",
                 H5P_DEFAULT, H5P_DEFAULT);
  hid_t group3 = H5Gopen(file.file, "/group3", H5P_DEFAULT);

  ObjectId info1(file.group1);
  ObjectId info2(group3);

  EXPECT_NE(file.group1, group3);
  EXPECT_EQ(info1.file_name(), info2.file_name());
  EXPECT_EQ(info1.file_number(), info2.file_number());
  EXPECT_EQ(info1.object_address(), info1.object_address());

  H5Gclose(group3);
  fs::remove(FILE1);
}

// For h5 hard links (to dataset):
//   file_name, file_number and address are all equal
TEST(ObjectId,  hard_dset )
{
  OneFile file(FILE1);

  H5Lcreate_hard(file.group1, "dset1",
                 file.group2, "dset2",
                 H5P_DEFAULT, H5P_DEFAULT);
  hid_t dset2 = H5Dopen(file.group2, "dset2", H5P_DEFAULT);

  ObjectId info1(file.dset1);
  ObjectId info2(dset2);

  EXPECT_NE(file.dset1, dset2);
  EXPECT_EQ(info1.file_name(), info2.file_name());
  EXPECT_EQ(info1.file_number(), info2.file_number());
  EXPECT_EQ(info1.object_address(), info1.object_address());

  H5Dclose(dset2);
  fs::remove(FILE1);
}

// For h5 soft links (to group):
//   file_name, file_number and address are all equal
TEST(ObjectId,  soft_group )
{
  OneFile file(FILE1);

  H5Lcreate_soft("/group1", file.file, "/group3",
                 H5P_DEFAULT, H5P_DEFAULT);
  hid_t group3 = H5Gopen(file.file, "/group3", H5P_DEFAULT);

  ObjectId info1(file.group1);
  ObjectId info2(group3);

  EXPECT_NE(file.group1, group3);
  EXPECT_EQ(info1.file_name(), info2.file_name());
  EXPECT_EQ(info1.file_number(), info2.file_number());
  EXPECT_EQ(info1.object_address(), info1.object_address());

  H5Gclose(group3);
  fs::remove(FILE1);
}

// For h5 soft links (to dataset):
//   file_name, file_number and address are all equal
TEST(ObjectId,  soft_dset )
{
  OneFile file(FILE1);

  H5Lcreate_soft("/group1/dset1", file.file, "/group2/dset2",
                 H5P_DEFAULT, H5P_DEFAULT);
  hid_t dset2 = H5Dopen(file.group2, "dset2", H5P_DEFAULT);

  ObjectId info1(file.dset1);
  ObjectId info2(dset2);

  EXPECT_NE(file.dset1, dset2);
  EXPECT_EQ(info1.file_name(), info2.file_name());
  EXPECT_EQ(info1.file_number(), info2.file_number());
  EXPECT_EQ(info1.object_address(), info1.object_address());

  H5Dclose(dset2);
  fs::remove(FILE1);
}

// If file copy is made:
//   only object addresses are equal
TEST(ObjectId,  file_copy )
{
  OneFile* file = new OneFile(FILE1);
  delete file;

  fs::copy_file(FILE1, FILE2,
                               fs::copy_option::overwrite_if_exists);

  hid_t file1 = H5Fopen(FILE1, H5F_ACC_RDONLY, H5P_DEFAULT);
  hid_t file2 = H5Fopen(FILE2, H5F_ACC_RDONLY, H5P_DEFAULT);
  hid_t group1 = H5Gopen(file1, "/group1", H5P_DEFAULT);
  hid_t group2 = H5Gopen(file2, "/group1", H5P_DEFAULT);

  ObjectId info1(group1);
  ObjectId info2(group2);

  EXPECT_NE(group1, group2);
  EXPECT_NE(info1.file_name(), info2.file_name());
  EXPECT_NE(info1.file_number(), info2.file_number());
  EXPECT_EQ(info1.object_address(), info1.object_address());

  H5Gclose(group1);
  H5Gclose(group2);
  H5Fclose(file1);
  H5Fclose(file2);
  fs::remove(FILE1);
  fs::remove(FILE2);
}

// If 2 files are created with identical structure:
//   only object addresses are equal
TEST(ObjectId,  file_copy2 )
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

  ObjectId info1(group1);
  ObjectId info2(group2);

  EXPECT_NE(group1, group2);
  EXPECT_NE(info1.file_name(), info2.file_name());
  EXPECT_NE(info1.file_number(), info2.file_number());
  EXPECT_EQ(info1.object_address(), info1.object_address());

  H5Gclose(group1);
  H5Gclose(group2);
  H5Fclose(file1);
  H5Fclose(file2);
  fs::remove(FILE1);
  fs::remove(FILE2);
}

// Symbolic link (in OS) is made FILE2 -> FILE1
//   only file_number and object_address are equal
//   file_name is not equal
TEST(ObjectId,  symlink_id )
{
  OneFile* file = new OneFile(FILE1);
  delete file;

  // Symlink FILE2 -> FILE1
  fs::create_symlink(FILE1, FILE2);

  hid_t file1 = H5Fopen(FILE1, H5F_ACC_RDONLY, H5P_DEFAULT);
  hid_t file2 = H5Fopen(FILE2, H5F_ACC_RDONLY, H5P_DEFAULT);
  hid_t group1 = H5Gopen(file1, "/group1", H5P_DEFAULT);
  hid_t group2 = H5Gopen(file2, "/group1", H5P_DEFAULT);

  ObjectId info1(group1);
  ObjectId info2(group2);

  EXPECT_NE(group1, group2);
  EXPECT_NE(info1.file_name(), info2.file_name());
  EXPECT_EQ(info1.file_number(), info2.file_number());
  EXPECT_EQ(info1.object_address(), info1.object_address());

  EXPECT_EQ(fs::canonical(FILE1),
                    fs::canonical(FILE2));

  H5Gclose(group1);
  H5Gclose(group2);
  H5Fclose(file1);
  H5Fclose(file2);
  fs::remove(FILE1);
  fs::remove(FILE2);
}

// If external link is made file2/group3 -> File1/group1
// All three parameters are equal
TEST(ObjectId,  file_external_group )
{
  OneFile* file = new OneFile(FILE1);
  delete file;

  OneFile* fileb = new OneFile(FILE2);
  delete fileb;

  // Extlink file2/group3 -> file1/group1
  hid_t file2 = H5Fopen(FILE2, H5F_ACC_RDONLY, H5P_DEFAULT);
  H5Lcreate_external(FILE1, "/group1", file2, "/group3", H5P_DEFAULT, H5P_DEFAULT);
  hid_t group23 = H5Gopen(file2, "/group3", H5P_DEFAULT);

  // Original node
  hid_t file1 = H5Fopen(FILE1, H5F_ACC_RDONLY, H5P_DEFAULT);
  hid_t group11 = H5Gopen(file1, "/group1", H5P_DEFAULT);

  ObjectId info11(group11);
  ObjectId info23(group23);

  EXPECT_NE(group11, group23);
  EXPECT_NE(info11.file_name(), info23.file_name());
  EXPECT_EQ(info11.file_number(), info23.file_number());
  EXPECT_EQ(info11.object_address(), info23.object_address());

  H5Gclose(group11);
  H5Gclose(group23);

  fs::remove(FILE1);
  fs::remove(FILE2);
}

// Symbolic link (in OS) is made FILE3 -> FILE1
// External link is made file2/group3 -> File3/group1
//   only file_number and object_address are equal
//   file_name is not equal
TEST(ObjectId,  file_external_symlink )
{
  OneFile* file = new OneFile(FILE1);
  delete file;

  OneFile* fileb = new OneFile(FILE2);
  delete fileb;


  // Symlink FILE3 -> FILE1
  fs::create_symlink(FILE1, FILE3);

  // Extlink file2/group3 -> file3/group1
  hid_t file2 = H5Fopen(FILE2, H5F_ACC_RDONLY, H5P_DEFAULT);
  H5Lcreate_external(FILE3, "/group1", file2, "/group3", H5P_DEFAULT, H5P_DEFAULT);
  hid_t group23 = H5Gopen(file2, "/group3", H5P_DEFAULT);

  // Original node
  hid_t file1 = H5Fopen(FILE1, H5F_ACC_RDONLY, H5P_DEFAULT);
  hid_t group11 = H5Gopen(file1, "/group1", H5P_DEFAULT);

  // Node in symlinked file
  hid_t file3 = H5Fopen(FILE3, H5F_ACC_RDONLY, H5P_DEFAULT);
  hid_t group31 = H5Gopen(file3, "/group1", H5P_DEFAULT);

  ObjectId info11(group11);
  ObjectId info31(group31);
  ObjectId info23(group23);

  EXPECT_NE(group11, group31);
  EXPECT_NE(group11, group23);
  EXPECT_NE(group23, group31);

  EXPECT_NE(info11.file_name(), info31.file_name());
  EXPECT_NE(info31.file_name(), info23.file_name());
  EXPECT_NE(info11.file_name(), info23.file_name());

  EXPECT_EQ(info11.file_number(), info31.file_number());
  EXPECT_EQ(info11.file_number(), info23.file_number());
  EXPECT_EQ(info31.file_number(), info23.file_number());

  EXPECT_EQ(info11.object_address(), info31.object_address());
  EXPECT_EQ(info11.object_address(), info23.object_address());
  EXPECT_EQ(info31.object_address(), info23.object_address());

  H5Gclose(group11);
  H5Gclose(group31);
  H5Gclose(group23);

  fs::remove(FILE1);
  fs::remove(FILE2);
  fs::remove(FILE3);
}

// If the same file is opened repeatedly:
//   file_name and object_address are equal
//   file_number is not equal
TEST(ObjectId,  repeated_open )
{
  OneFile* file = new OneFile(FILE1);
  ObjectId i1(file->file);
  delete file;

  file = new OneFile(FILE1);
  ObjectId i2(file->file);
  delete file;

  EXPECT_EQ(i1.file_name(), i2.file_name());
  EXPECT_NE(i1.file_number(), i2.file_number());
  EXPECT_EQ(i1.object_address(), i2.object_address());
  std::cout << i1 << "   ??   " << i2 << std::endl;
}
