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

#include <h5cpp/hdf5_capi.hpp>
#include <vector>
#include <sstream>
#include <cstring>
#include <algorithm>
#include <iterator>
#include <h5cpp/datatype/string.hpp>
#include <h5cpp/dataspace/dataspace.hpp>

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
    //! \brief create buffer with write data
    //!
    //! This function creates a buffer instance which can be used for
    //! writing data to disk. The buffer must be allocated within this
    //! function to ensure that all the input data fits into it.
    //!
    //! \param data the input data
    //! \return an instance of the variable length string buffer
    //!
    static BufferType to_buffer(const T &)
    {
      return BufferType();
    }

    //!
    //! \brief copy data to output
    //!
    //! Copies data from the buffer to the user data structure.
    //! It assumes that data is allocated and all data fits into
    //! it. We usually do not have to care about this as during the
    //! reading procedure a dataspace for the data sturcture is
    //! created and H5Dread checks whether or not the data fits
    //! into the structure.
    //!
    static void from_buffer(const BufferType &, DataType &)
    { }
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
    {
      return BufferType();    
    }

    static DataType from_buffer(const BufferType &,const datatype::String &)
    {
      return DataType();    
    }
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

    static DataType from_buffer(const BufferType &buffer,const datatype::String &)
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
     BufferType buffer(data.size()*file_type.size()+data.size()+1,'\0');
     
     auto iter = buffer.begin();
     for(const auto &str: data)
     {
       iter = std::copy(str.begin(),str.end(),iter);
	   iter++;
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
