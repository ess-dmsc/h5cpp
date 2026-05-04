//
// (c) Copyright 2017 DESY,ESS
//               2018 Eugen Wintersberger
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
// Author: Eugen Wintersberger <eugen.wintersberger@gmail.com>
// Created on: Apr 4, 2019
//
#pragma once

#include <algorithm>
#include <vector>
#include <string>
#include <h5cpp/dataspace/dataspace.hpp>
#include <h5cpp/datatype/string.hpp>
#include <h5cpp/core/utilities.hpp>

namespace hdf5 {

template<typename CharT>
class FixedLengthStringBuffer : public  std::vector<CharT>
{
  public:

    using std::vector<CharT>::vector;

    static FixedLengthStringBuffer<CharT> create(const datatype::String &datatype,
                                                 const dataspace::Dataspace &dataspace)
    {
      FixedLengthStringBuffer<CharT> buffer;
      if(dataspace.selection.type() == dataspace::SelectionType::All)
        buffer =  FixedLengthStringBuffer<CharT>(datatype.size()*static_cast<size_t>(dataspace.size()));
      else
        buffer = FixedLengthStringBuffer<CharT>(datatype.size()*dataspace.selection.size());

      return buffer;
    }
};

template<typename T>
struct FixedLengthStringTrait
{
    using DataType = T;
    using BufferType = FixedLengthStringBuffer<char>;

    static BufferType create_buffer(const datatype::String &datatype,
                                    const dataspace::Dataspace &dataspace)
    {
      return BufferType::create(datatype,dataspace);
    }

    static BufferType to_buffer(const DataType &,const datatype::String &,
                                const dataspace::Dataspace &)
    {
      return BufferType();
    }

    static DataType from_buffer(const BufferType &,const datatype::String &,
                                const dataspace::Dataspace &)
    {
      return DataType();
    }
};

template<>
struct FixedLengthStringTrait<std::string>
{
    using DataType = std::string;
    using BufferType = FixedLengthStringBuffer<char>;

    //!
    //! @brief create fixed length string buffer from data
    //!
    //! Returns an IO buffer for fixed length strings for data in memory.
    //!
    //! @param data reference to the original data
    //! @param memory_type HDF5 data type for the data in memory
    //! @param memory_space HDF5 dataspace for the data in memory
    //! @return buffer instance with data
    //!
    static BufferType to_buffer(const DataType &data,
                                const datatype::String &memory_type,
                                const dataspace::Dataspace &memory_space)
    {
      BufferType buffer = BufferType::create(memory_type,memory_space);

      auto buffer_iter = buffer.begin();
      auto buffer_end  = buffer.end();
      auto data_iter   = data.begin();
      auto data_end    = data.end();

      for(;buffer_iter!=buffer_end && data_iter != data_end; ++buffer_iter,++data_iter)
        *buffer_iter = *data_iter;

      return buffer;
    }

    //!
    //! @brief store data from buffer in target memory
    //!
    //! @param buffer reference to the IO buffer
    //! @return new data instance
    static DataType from_buffer(const BufferType &buffer,
                                const datatype::String &,
                                const dataspace::Dataspace &)
    {
      return DataType(buffer.begin(), buffer.end());
    }

    //!
    //! @brief store data from buffer in target memory and trim any tailing null-terminating characters
    //!
    //! @param buffer reference to the IO buffer
    //! @param memory_type the datatype describing how the string is stored in the file
    //! @return new data instance
    static DataType from_buffer_trimmed(const BufferType &buffer,
                                        const datatype::String &memory_type,
                                        const dataspace::Dataspace &)
    {
      const auto padding = memory_type.padding();
      auto end_it = buffer.end();
      switch (padding)
      {
      case datatype::StringPad::NullTerm:
        end_it = std::find(buffer.begin(), buffer.end(), '\0');
        break;
      case datatype::StringPad::NullPad:
        // get iterator to last padding \0 character
        end_it = std::find_if_not(buffer.rbegin(), buffer.rend(), [](const BufferType::value_type &c)
                                  { return c == '\0'; })
                     .base();
        break;
      case datatype::StringPad::SpacePad:
        // get iterator to last padding space character
        end_it = std::find_if_not(buffer.rbegin(), buffer.rend(), [](const BufferType::value_type &c)
                                  { return c == ' '; })
                     .base();
        break;
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wcovered-switch-default"
#endif
      default:
        break;
#ifdef __clang__
#pragma clang diagnostic pop
#endif
      }
      return DataType(buffer.begin(), end_it);
    }
};

template<>
struct FixedLengthStringTrait<std::vector<std::string>>
{
   using DataType = std::vector<std::string>;
   using BufferType = FixedLengthStringBuffer<char>;

   static BufferType to_buffer(const DataType &data,
                               const datatype::String &memory_type,
                               const dataspace::Dataspace &memory_space)
   {
     BufferType buffer = BufferType::create(memory_type,memory_space);

     auto iter = buffer.begin();
     for(const auto &str: data)
     {
       std::copy(str.begin(),str.end(),iter);
       std::advance(iter,unsigned2signed<ssize_t>(memory_type.size())); //move iterator to the next position
     }

     return buffer;
   }

   static DataType from_buffer(const BufferType &buffer,
                               const datatype::String &memory_type,
                               const dataspace::Dataspace &)
   {
     DataType data;

     auto start=buffer.begin();
     while(start!=buffer.end())
     {
       auto end = start+unsigned2signed<std::string::difference_type>(memory_type.size());
       data.push_back(std::string(start,end));
       start=end;
     }
     return data;
   }
};


}
