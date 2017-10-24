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
template<typename T,typename CharT>
struct VarLengthStringTrait
{
    //!
    //! \brief copy data from T to the string buffer
    //!
    //! The function will do the allocation of space in the string buffer.
    //!
    static void to_buffer(const T &,VarLengthStringBuffer<CharT> &)
    {}

    //!
    //! \brief copy data from string buffer to T
    //!
    //! Copies the data from a string buffer to an instance of T.
    //! Space in T will be allocated by this function.
    //!
    static void from_buffer(const VarLengthStringBuffer<CharT> &,T &)
    {}
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

    static BufferType allocate_buffer(const dataspace::Dataspace &,const datatype::String &)
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

    static BufferType allocate_buffer(const dataspace::Dataspace &,const datatype::String &file_type)
    {
      return BufferType(file_type.size());
    }

    static DataType from_buffer(const BufferType &buffer,const datatype::String &)
    {
      DataType data;
      std::copy(buffer.begin(),buffer.end(),std::back_inserter(data));
      return data;
    }
};

template<typename CharT>
using StringBuffer = std::vector<CharT*>;

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

   static BufferType allocate_buffer(const dataspace::Dataspace &file_space,
                                     const datatype::String &file_type)
   {
     return BufferType(file_type.size()*file_space.size());
   }

   static DataType from_buffer(const BufferType &buffer,const datatype::String &file_type)
   {
     DataType data;
     std::stringstream ss(std::string(buffer.begin(),buffer.end()));
     while(!ss.eof())
     {
       std::string string_buffer;
       ss>>string_buffer;
       data.push_back(string_buffer);
     }
     return data;
   }
};



} // namespace hdf5
