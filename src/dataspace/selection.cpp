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
// Created on: Aug 25, 2017
//
#include <stdexcept>
#include <h5cpp/dataspace/selection.hpp>
#include <algorithm>
#include <sstream>


namespace hdf5 {
namespace dataspace {

#define THROW_IF_DEFAULT_CONSTRUCTED(msg)\
  if(rank()==0) \
  {\
    throw std::runtime_error(msg);\
  }


Selection::~Selection()
{}

Hyperslab::Hyperslab():
        Selection(),
        start_(),
        stride_(),
        count_(),
        block_()
{}

Hyperslab::~Hyperslab()
{}

Hyperslab::Hyperslab(size_t rank):
            Selection(),
            start_(rank),
            stride_(rank),
            count_(rank),
            block_(rank)
{
  std::fill(start_.begin(),start_.end(),0);
  std::fill(stride_.begin(),stride_.end(),1);
  std::fill(block_.begin(),block_.end(),0);
  std::fill(count_.begin(),count_.end(),0);
}

Hyperslab::Hyperslab(const Dimensions &offset,
                     const Dimensions &block,
                     const Dimensions &count,
                     const Dimensions &stride):
                         Selection(),
                         start_(offset),
                         stride_(stride),
                         count_(count),
                         block_(block)
{}

Hyperslab::Hyperslab(const Dimensions &offset,const Dimensions &block):
    Selection(),
    start_(offset),
    stride_(offset.size()),
    count_(offset.size()),
    block_(block)
{
  std::fill(stride_.begin(),stride_.end(),1ul);
  std::fill(count_.begin(),count_.end(),1ul);
}

Hyperslab::Hyperslab(const Dimensions &offset,const Dimensions &count,
                     const Dimensions &stride):
    Selection(),
    start_(offset),
    stride_(stride),
    count_(count),
    block_(offset.size())
{
  std::fill(block_.begin(),block_.end(),1ul);
}

size_t Hyperslab::rank() const noexcept
{
  return start_.size();
}

void Hyperslab::check_dimension_index(size_t index,const std::string &what) const
{
  if(index>=rank())
  {
    std::stringstream ss;
    ss<<"Cannot set "<<what<<" value at dimension "<<index<<" for a Hyperslab"
        <<" of rank "<<rank()<<"!";
    throw std::runtime_error(ss.str());
  }
}

void Hyperslab::check_container_size(const Dimensions &container,
                                     const std::string &what) const
{
  if(container.size()!=rank())
  {
    std::stringstream ss;
    ss<<"Cannot assign "<<container.size()<<" "<<what<<" values to a Hyperslab"
      <<" of rank "<<rank()<<"!";
    throw std::runtime_error(ss.str());
  }
}

void Hyperslab::start(size_t index,size_t value)
{
  THROW_IF_DEFAULT_CONSTRUCTED("Cannot set start value for a default "
                               "constructed Hyperslab!")
  check_dimension_index(index,"start");

  start_[index] = value;
}

void Hyperslab::start(const Dimensions &values)
{
  THROW_IF_DEFAULT_CONSTRUCTED("Cannot set start values for a default "
                               "constructed Hyperslab!")

  check_container_size(values,"start");
  start_  = values;
}

const Dimensions &Hyperslab::start() const
{
  THROW_IF_DEFAULT_CONSTRUCTED("Cannot get start values for a default "
                               "constructed Hyperslab!")
  return start_;
}

void Hyperslab::stride(size_t index,size_t value)
{
  THROW_IF_DEFAULT_CONSTRUCTED("Cannot set stride value for a default "
                               "constructed Hyperslab!")
  check_dimension_index(index,"stride");

  stride_[index] = value;
}

void Hyperslab::stride(const Dimensions &values)
{
  THROW_IF_DEFAULT_CONSTRUCTED("Cannot set stride values for a default "
                               "constructed Hyperslab!")
  check_container_size(values,"stride");
  stride_ = values;
}

const Dimensions &Hyperslab::stride() const
{
  THROW_IF_DEFAULT_CONSTRUCTED("Cannot get stride values for a default "
                               "constructed Hyperslab!")
  return stride_;
}

void Hyperslab::count(size_t index,size_t value)
{
  THROW_IF_DEFAULT_CONSTRUCTED("Cannot set count value for a default "
                               "constructed Hyperslab!")
  check_dimension_index(index,"count");

  count_[index] = value;
}

void Hyperslab::count(const Dimensions &values)
{
  THROW_IF_DEFAULT_CONSTRUCTED("Cannot set count values for a default "
                               "constructed Hyperslab!")
  check_container_size(values,"count");
  count_ = values;
}

const Dimensions &Hyperslab::count() const
{
  THROW_IF_DEFAULT_CONSTRUCTED("Cannot get count values for a default "
                               "constructed Hyperslab!")
  return count_;
}

void Hyperslab::block(size_t index,size_t value)
{
  THROW_IF_DEFAULT_CONSTRUCTED("Cannot set block value for a default "
                               "constructed Hyperslab!")
  check_dimension_index(index,"block");
  block_[index] = value;
}

void Hyperslab::block(const Dimensions &values)
{
  THROW_IF_DEFAULT_CONSTRUCTED("Cannot set block values for a default "
                               "constructed Hyperslab!")
  check_container_size(values,"block");
  block_ = values;

}

const Dimensions &Hyperslab::block() const
{
  THROW_IF_DEFAULT_CONSTRUCTED("Cannot get block values for a default "
                               "constructed Hyperslab!")
  return block_;
}

void Hyperslab::apply(const Dataspace &space,SelectionOperation ops) const
{
  if(H5Sselect_hyperslab(static_cast<hid_t>(space),
                         static_cast<H5S_seloper_t>(ops),
                         start_.data(),stride_.data(),count_.data(),
                         block_.data())<0)
  {
    throw std::runtime_error("Failure applying hyperslab selection to the "
          "dataspace");
  }
}


Points::Points():
    Selection()
{}

Points::~Points()
{}

#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#endif
Points::Points(size_t rank):
    Selection()
{}
#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif

#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#endif
void Points::apply(const Dataspace &space,
                   SelectionOperation ops) const
{
}
#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif

} // namespace dataspace
} // namespace hdf5
