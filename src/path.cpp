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
// Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
// Created on: Aug 24, 2017
//

#include <h5cpp/path.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>

namespace hdf5 {

//
// private functions used for path construction - they are not exported to the
// ABI of the library
namespace {

bool is_absolute_path_string(const std::string &str)
{
  if(str[0] == '/')
    return true;
  else
    return false;
}

std::list<std::string> str_to_list(const std::string &str)
{
  auto string_start = str.begin();
  auto string_end = str.end();

  //ignore a leading / in the input string
  if(is_absolute_path_string(str)) string_start++;


  //ignore a trailing / from the input string
  if(str.back()=='/') string_end--;

  std::string buffer(string_start,string_end);
  std::list<std::string> result;
  boost::split(result,buffer,
               boost::is_any_of("/"),boost::token_compress_on);

  return result;
}

} // end of anonymous name space

//=============================================================================
void Path::from_string(const std::string &str)
{
  auto string_start = str.begin();
  auto string_end = str.end();
  if(str[0]=='/')
  {
    string_start++;
    absolute_ = true;
  }
  else
  {
    absolute_ = false;
  }

  //check if we are already at the end
  if(string_start == string_end)
    return;

  //remove a trailing / from the input string
  if(str.back()=='/') string_end--;

  std::string buffer(string_start,string_end);
  boost::split(link_names_,buffer,
               boost::is_any_of("/"),boost::token_compress_on);
}

std::string Path::to_string() const
{
  std::string result;
  if(is_absolute_path())
    result = "/";

  for(auto iter = link_names_.begin();iter!=link_names_.end();iter++)
  {
    result += *iter;
    if(iter!=(--link_names_.end()))
      result += "/";
  }

  return result;
}

Path::Path():
    absolute_(false),
    link_names_()
{}

Path::Path(const std::string &str):
    absolute_(false),
    link_names_()
{
  from_string(str);
}

size_t Path::size() const
{
  return link_names_.size();
}

Path::const_iterator Path::begin() const
{
  return link_names_.begin();
}

Path::const_iterator Path::end() const
{
  return link_names_.end();
}

Path::iterator Path::begin()
{
  return link_names_.begin();
}

Path::iterator Path::end()
{
  return link_names_.end();
}

Path::reverse_iterator Path::rbegin()
{
  return link_names_.rbegin();
}

Path::reverse_iterator Path::rend()
{
  return link_names_.rend();
}

Path::const_reverse_iterator Path::rbegin() const
{
  return link_names_.rbegin();
}

Path::const_reverse_iterator Path::rend() const
{
  return link_names_.rend();
}

void Path::push_front(const value_type &link_name)
{
  link_names_.push_front(link_name);
}

Path::value_type Path::pop_front()
{
  value_type result = link_names_.front();
  link_names_.pop_front();
  return result;
}

void Path::push_back(const Path::value_type &link_name)
{
  link_names_.push_back(link_name);
}

Path::value_type Path::pop_back()
{
  value_type result = link_names_.back();
  link_names_.pop_back();
  return result;
}

bool Path::is_absolute_path() const noexcept
{
  return absolute_;
}

void Path::is_absolute_path(bool v) noexcept
{
  absolute_ = v;
}

bool Path::is_root() const
{
  if(is_absolute_path() && link_names_.empty())
    return true;
  else
    return false;
}

Path operator+(const std::string &link_name,const Path &path)
{
  Path result(path);

  if(link_name.empty())
    return result;

  if(is_absolute_path_string(link_name))
      result.is_absolute_path(true);

  if(link_name.size()==1) return result;

  std::list<std::string> str_list = str_to_list(link_name);
  std::copy(str_list.rbegin(),str_list.rend(),std::front_inserter(result));

  return result;
}

Path operator+(const Path &path,const std::string &link_name)
{
  Path result(path);

  if(link_name.empty()) return result;

  std::list<std::string> str_list = str_to_list(link_name);
  std::copy(str_list.begin(),str_list.end(),std::back_inserter(result));
  return result;
}

Path operator+(const Path &lhs,const Path &rhs)
{
  Path result(lhs);
  std::copy(rhs.begin(),rhs.end(),std::back_inserter(result));
  return result;
}

std::ostream &operator<<(std::ostream &stream,const Path &path)
{
  return stream<<static_cast<std::string>(path);
}

Path::value_type Path::front() const
{
  if(is_root())
    return "/";

  return link_names_.front();
}

Path::value_type Path::back() const
{
  if(is_root())
    return "/";

  return link_names_.back();
}

std::string Path::object_name(const Path &path)
{
  if(path.is_root())
    return "/";

  return path.back();
}

Path Path::parent_path(const Path &path)
{
  if(path.is_root())
    return path;

  Path p(path);

  p.pop_back();
  return p;
}

bool operator==(const Path &lhs, const Path &rhs)
{
  return (lhs.absolute_ == rhs.absolute_) && (lhs.link_names_ == rhs.link_names_);
}

bool operator!=(const Path &lhs, const Path &rhs)
{
  return !(lhs == rhs);
}


} // namespace hdf5
