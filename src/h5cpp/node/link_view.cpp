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
// Created on: Sep 11, 2017
//

#include <sstream>
#include <h5cpp/node/link_view.hpp>
#include <h5cpp/node/group.hpp>
#include <h5cpp/node/link_iterator.hpp>
#include <h5cpp/core/utilities.hpp>

namespace hdf5 {
namespace node {

LinkView::LinkView(Group &group):
    GroupView(group)
{}

Link LinkView::operator[](size_t index) const
{
  const IteratorConfig &config = group().iterator_config();


  //------------------------------------------------------------------------
  // determine the size of the link name
  //------------------------------------------------------------------------
  ssize_t size = H5Lget_name_by_idx(static_cast<hid_t>(group()),
                                    ".",
                                    static_cast<H5_index_t>(config.index()),
                                    static_cast<H5_iter_order_t>(config.order()),
                                    index,
                                    nullptr,
                                    0,
                                    static_cast<hid_t>(config.link_access_list()));
  if(size<0)
  {
    std::stringstream ss;
    ss<<"Could not determine the size of link "<<index<<" on group ["
      <<group().link().path()<<"]!";
    error::Singleton::instance().throw_with_stack(ss.str());
  }

  //setting up the string where to store the name
  std::string name(signed2unsigned<size_t>(size),' ');

  //------------------------------------------------------------------------
  // load the link name
  //------------------------------------------------------------------------
  size = H5Lget_name_by_idx(static_cast<hid_t>(group()),
                            ".",
                            static_cast<H5_index_t>(config.index()),
                            static_cast<H5_iter_order_t>(config.order()),
                            index,
                            const_cast<char*>(name.data()),
                            signed2unsigned<size_t>(size+1),
                            static_cast<hid_t>(config.link_access_list()));
  if(size<0)
  {
    std::stringstream ss;
    ss<<"Could not load name for link "<<index<<" on group ["
        <<group().link().path()<<"]!";
    error::Singleton::instance().throw_with_stack(ss.str());
  }

  return Link(group().link().file(),group().link().path(),name);

}

Link LinkView::operator[](const std::string &name) const
{
  if(!Path(name).is_name())
  {
    std::stringstream ss;
    ss<<"["<<name<<"] is not a valid link name!";
    throw std::runtime_error(ss.str());
  }
  return Link(group().link().file(),group().link().path(),name);
}

bool LinkView::exists(const std::string &name, const property::LinkAccessList &lapl) const
{
  if(!Path(name).is_name())
  {
    std::stringstream ss;
    ss<<"["<<name<<"] is not a valid link name!";
    throw std::runtime_error(ss.str());
  }

  htri_t result = H5Lexists(static_cast<hid_t>(group()),
                            name.c_str(),
                            static_cast<hid_t>(lapl));

  if(result>0)
  {
    return true;
  }
  else if(result == 0)
  {
    return false;
  }
  else
  {
    std::stringstream ss;
    ss<<"Failure checking for link ["<<name<<"] on group ["
      <<group().link().path()<<"]!";
    error::Singleton::instance().throw_with_stack(ss.str());
  }
  return false;
}

LinkView::const_iterator LinkView::begin() const
{
  return LinkIterator::begin(group());
}

LinkView::const_iterator LinkView::end() const
{
  return LinkIterator::end(group());
}

} // namespace node
} // namespace hdf5
