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
// Authors:
//   Eugen Wintersberger <eugen.wintersberger@desy.de>
//   Martin Shetty <martin.shetty@esss.se>
// Created on: Aug 14, 2017
//
#pragma once

#include <h5cpp/core/object_handle.hpp>

#include <h5cpp/core/hdf5_capi.hpp>
#include <h5cpp/property/property_list.hpp>

class TestEnvironment
{
  std::string filename_{};
  hdf5::ObjectHandle file_handle_;
 public:
  TestEnvironment(const std::string &filename);
  void close();

  const hdf5::ObjectHandle &file_handle() const;

};

class ObjectHandleTest
{
 private:
  hdf5::ObjectHandle::Type type_;
 public:
  ObjectHandleTest(hdf5::ObjectHandle::Type type);

  virtual ~ObjectHandleTest();

  virtual hid_t create_object() = 0;

  virtual void test_copy_construction();

  virtual void test_move_construction();

  virtual void test_copy_assignment();

  virtual void test_move_assignment();

  virtual void test_close_pathology();

  virtual void test_equality();

  hdf5::ObjectHandle::Type get_type() const { return type_; }

};

class FileObjectHandleTest : public ObjectHandleTest
{
 private:
  std::string filename_{};
 public:
  FileObjectHandleTest(const std::string &filename);
  ~FileObjectHandleTest() override;

  virtual hid_t create_object() override;
};

class DatatypeObjectHandleTest : public ObjectHandleTest
{
 public:
  DatatypeObjectHandleTest();

  virtual hid_t create_object() override;
};

class DataspaceObjectHandleTest : public ObjectHandleTest
{
 public:
  DataspaceObjectHandleTest();

  virtual hid_t create_object() override;
};

class GroupObjectHandleTest : public ObjectHandleTest
{
 private:
  TestEnvironment environment_;
 public:
  GroupObjectHandleTest(const std::string &filename);

  virtual hid_t create_object() override;
};

class DatasetObjectHandleTest : public ObjectHandleTest
{
 private:
  std::string filename_{};
  TestEnvironment environment_;
  hdf5::ObjectHandle dtype_;
  hdf5::ObjectHandle dspace_;
 public:
  DatasetObjectHandleTest(const std::string &filename);
  ~DatasetObjectHandleTest() override;

  virtual hid_t create_object() override;
};

class AttributeObjectHandleTest : public ObjectHandleTest
{
 private:
  std::string filename_{};
  TestEnvironment environment_;
  hdf5::ObjectHandle group_;
 public:
  AttributeObjectHandleTest(const std::string &filename);
  ~AttributeObjectHandleTest() override;

  virtual hid_t create_object() override;
};

class PropertyListObjectHandleTest : public ObjectHandleTest
{
 public:
  PropertyListObjectHandleTest();

  virtual hid_t create_object() override;
};

class PropertyListClassObjectHandleTest : public ObjectHandleTest
{
 public:
  PropertyListClassObjectHandleTest();

  virtual hid_t create_object();
};

class ErrorMessageObjectHandleTest : public ObjectHandleTest
{
 public:
  ErrorMessageObjectHandleTest();
  virtual hid_t create_object() override;
};

class ErrorStackObjectHandleTest : public ObjectHandleTest
{
 public:
  ErrorStackObjectHandleTest();
  virtual hid_t create_object() override;
};

class ErrorClassObjectHandleTest : public ObjectHandleTest
{
 public:
  ErrorClassObjectHandleTest();
  virtual hid_t create_object() override;
};





