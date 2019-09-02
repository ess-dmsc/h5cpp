//
// (c) Copyright 2019 Eugen Wintersberger <eugen.wintersberger@gmail.com>
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
// Created on: Sep 1, 2019
//
#pragma once

#include <string>


namespace hdf5 {
namespace type {

/**
 * @brief fixed UTF8 string type
 */
class FixedUTF8String : public std::string
{
  public:
    using std::string::string;
    FixedUTF8String(const std::string &string) : std::string(string) {}
    FixedUTF8String(std::string &&string) : std::string(std::move(string)) {}
};

/**
 * @brief fixed ASCII string type
 */
class FixedASCIIString : public std::string
{
  public:
    using std::string::string;
    FixedASCIIString(const std::string &string) : std::string(string) {}
    FixedASCIIString(std::string &&string) : std::string(std::move(string)) {}
};

/**
 * @brief variable UTF8 string type
 */
class VariableUTF8String : public std::string
{
  public:
    using std::string::string;
    VariableUTF8String(const std::string &string) : std::string(string) {}
    VariableUTF8String(std::string &&string) : std::string(std::move(string)) {}
};


/**
 * @brief variable ASCII string type
 */
class VariableASCIIString : public std::string
{
  public:
    using std::string::string;
    VariableASCIIString(const std::string &string) : std::string(string) {}
    VariableASCIIString(std::string &&string) : std::string(std::move(string)) {}
};


} // end of namespace type


namespace datatype {

/**
 * @brief type trait for a fixed size UTF8 string
 */
template<>
class Trait<type::FixedUTF8String>
{
  public:
    using Type = type::FixedUTF8String;
    using TypeClass = datatype::String;

    static datatype::String create(const Type &value)
    {
      datatype::String type = String::fixed(value.size());
      type.encoding(datatype::CharacterEncoding::UTF8);
      return type;
    }
};

/**
 * @brief type trait for a fixed size ASCII string
 */
template<>
class Trait<type::FixedASCIIString>
{
  public:
    using Type = type::FixedASCIIString;
    using TypeClass = datatype::String;

    static datatype::String create(const Type &value)
    {
      auto type = String::fixed(value.size());
      type.encoding(datatype::CharacterEncoding::ASCII);
      return type;
    }
};

/**
 * @brief type trait for a variable size UTF8 string
 */
template<>
class Trait<type::VariableUTF8String>
{
  public:
    using Type = type::VariableUTF8String;
    using TypeClass = datatype::String;

    static datatype::String create(const Type & = Type())
    {
      auto type = String::variable();
      type.encoding(datatype::CharacterEncoding::UTF8);
      return type;
    }
};

/**
 * @brief type trait for a variable ASCII string
 */
template<>
class Trait<type::VariableASCIIString>
{
  public:
    using Type = type::VariableASCIIString;
    using TypeClass = datatype::String;

    static datatype::String create(const Type & = Type())
    {
      auto type = String::variable();
      type.encoding(datatype::CharacterEncoding::ASCII);
      return type;
    }
};


} // end of namespace datatype
} // end of namespace hdf5
