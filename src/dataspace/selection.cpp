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


namespace hdf5 {
namespace dataspace {

Selection::Selection()
{}

Selection::~Selection()
{}

Hyperslab::Hyperslab():
        Selection()
{}

Hyperslab::~Hyperslab()
{}

Hyperslab::Hyperslab(size_t rank):
        start_(rank),
        stride_(rank),
        count_(rank),
        block_(rank)
{}

Hyperslab::Hyperslab(const Dimensions &start,
                     const Dimensions &stride,
                     const Dimensions &count,
                     const Dimensions &block):
                         Selection(),
                         start_(start),
                         stride_(stride),
                         count_(count),
                         block_(block)
{}

Dimensions &Hyperslab::start()
{
  return start_;
}

const Dimensions &Hyperslab::start() const
{
  return start_;
}

Dimensions &Hyperslab::stride()
{
  return stride_;
}

const Dimensions &Hyperslab::stride() const
{
  return stride_;
}

Dimensions &Hyperslab::count()
{
  return count_;
}

const Dimensions &Hyperslab::count() const
{
  return count_;
}

Dimensions &Hyperslab::block()
{
  return block_;
}

const Dimensions &Hyperslab::block() const
{
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

Points::Points(size_t rank):
    Selection()
{}

void Points::apply(const Dataspace &space,
                   SelectionOperation ops) const
{
}

} // namespace dataspace
} // namespace hdf5
