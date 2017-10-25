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
// Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
// Created on: Aug 21, 2017
//
#pragma once

extern "C" {
#include <hdf5.h>
}
#include <vector>
#include <sstream>
#include <cstring>
#include <algorithm>
#include "datatype/string.hpp"
#include "dataspace/dataspace.hpp"

namespace hdf5 {

using Dimensions = std::vector<hsize_t>;

using VarLengthDataBuffer = std::vector<hvl_t>;

//!
//! \brief variable length buffer trait
//!
//! This trait provides conversion functions from an instance of T to
//! a variable length data buffer and back.
//!
template<typename T>
struct VarLengthBufferTrait
{
    static void to_buffer(const T &,VarLengthDataBuffer &)
    {}

    static void from_buffer(const VarLengthDataBuffer &,T &)
    {}
};

//!
//! \brief buffer for variable length string data
//!
//! Variable length string requires and intermediate data structure to
//! be transfered from and to disk. This template provides the basic
//! buffer type used to transfer data.
//!
//! \tparam CharT the character tyep used for the strings
//!
template<typename CharT>
using VarLengthStringBuffer = std::vector<CharT*>;

//!
//! \brief variable length string buffer trait
//!
//! Trait implementing conversion functions between T and a particular
//! variable length string buffer type.
//!
template<typename T>
struct VarLengthStringTrait
{
    using BufferType = VarLengthStringBuffer<char>;
    using DataType = T;
    //!
    //! \brief copy data from T to the string buffer
    //!
    //! The function will do the allocation of space in the string buffer.
    //!
    static BufferType to_buffer(const T &)
    {}

    //!
    //! \brief copy data from string buffer to T
    //!
    //! Copies the data from a string buffer to an instance of T.
    //! Space in T will be allocated by this function.
    //!
    static void from_buffer(const BufferType &, DataType &data)
    {}
};

template<>
struct VarLengthStringTrait<std::string>
{
  using BufferType = VarLengthStringBuffer<char>;
  using DataType = std::string;

  static BufferType to_buffer(const DataType &data)
  {
    return BufferType{const_cast<char*>(data.c_str())};
  }

  static void from_buffer(const BufferType &buffer,DataType &data)
  {
    data = DataType(buffer[0],std::strlen(buffer[0]));
  }
};

template<>
struct VarLengthStringTrait<std::vector<std::string>>
{
  using BufferType = VarLengthStringBuffer<char>;
  using DataType = std::vector<std::string>;

  static BufferType to_buffer(const DataType &data)
  {
    BufferType buffer;
    std::transform(data.begin(),data.end(),std::back_inserter(buffer),
                   [](const std::string &str)
                   {
                    return const_cast<char*>(str.c_str());
                   });
    return buffer;
  }

  static void from_buffer(const BufferType &buffer,DataType &data)
  {
    std::transform(buffer.begin(),buffer.end(),data.begin(),
                   [](const char *ptr)
                   {
                     return std::string(ptr,std::strlen(ptr));
                   });
  }
};


template<typename CharT>
using FixedLengthStringBuffer = std::vector<CharT>;

template<typename T>
struct FixedLengthStringTrait
{
    using DataType = T;
    using BufferType = FixedLengthStringBuffer<char>;

    static BufferType to_buffer(const DataType &,const datatype::String &)
    {}

    static DataType from_buffer(const BufferType &,const datatype::String &)
    {}
};

template<>
struct FixedLengthStringTrait<std::string>
{
    using DataType = std::string;
    using BufferType = FixedLengthStringBuffer<char>;

    static BufferType to_buffer(const DataType &data,const datatype::String &)
    {
      BufferType buffer;
      std::copy(data.begin(),data.end(),std::back_inserter(buffer));
      return buffer;
    }

    static DataType from_buffer(const BufferType &buffer,const datatype::String &file_type)
    {
      return DataType(buffer.begin(),buffer.end()-1);
    }
};

template<>
struct FixedLengthStringTrait<std::vector<std::string>>
{
   using DataType = std::vector<std::string>;
   using BufferType = FixedLengthStringBuffer<char>;


   static BufferType to_buffer(const DataType &data,const datatype::String &file_type)
   {
     BufferType buffer(data.size()*file_type.size());
     std::fill(buffer.begin(),buffer.end(),'\0');
     auto iter = buffer.begin();
     for(const auto &str: data)
     {
       std::copy(str.begin(),str.end(),iter);
       std::advance(iter,file_type.size()+1);
     }

     return buffer;
   }

   static DataType from_buffer(const BufferType &buffer,const datatype::String &file_type)
   {
     DataType data;

     auto start=buffer.begin();
     while(start!=buffer.end())
     {
       auto end = start+file_type.size();
       data.push_back(std::string(start,end));
       start=end + 1;
     }
     return data;
   }
};



} // namespace hdf5
