//
// (c) Copyright 2017 DESY,ESS
//
// This file is part of h5cpp.
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
// Created on: Oct 25, 2017
//
#pragma once

#include <h5cpp/core/windows.hpp>
#include <h5cpp/core/object_handle.hpp>
#include <list>

namespace hdf5 {
namespace error {

struct Descriptor {
  Descriptor() {}
  Descriptor(const H5E_error2_t& d);

  hid_t         class_id  {0};  // class ID
  hid_t         major_num {0};  // major error ID
  hid_t         minor_num {0};  // minor error number
  unsigned      line      {0};  // line in file where error occurs
  std::string   func_name;      // function in which error occurred
  std::string   file_name;      // file in which error occurred
  std::string   desc;           // optional supplied description
};

DLL_EXPORT std::ostream &operator<<(std::ostream &stream, const Descriptor &desc);

class DLL_EXPORT Singleton
{
 public:
  static Singleton& instance()
  {
    static Singleton singleton_instance;
    return singleton_instance;
  }

  void auto_print(bool enable);
  bool auto_print() const;

  std::string print_stack();
  std::list<std::string> extract_stack();

  void throw_exception(const std::string& message);

 private:
  Singleton() {}
  Singleton(Singleton const&) = delete;
  void operator=(Singleton const&) = delete;

  bool auto_print_ {true};

 private:
  bool auto_print_enabled() const;
  void throw_stack();
  void clear_stack();

  static herr_t to_list(unsigned n,
                        const H5E_error2_t *err_desc,
                        std::list<std::string>* list);
};

// prints the explanatory string of an exception. If the exception is nested,
// recurses to print the explanatory of the exception it holds
std::string DLL_EXPORT print_exception(const std::exception& e, int level =  0);


} // namespace file
} // namespace hdf5
