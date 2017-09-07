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
// Created on: Aug 25, 2017
//
#pragma once

#include "type.hpp"
#include "dataspace.hpp"
#include "../types.hpp"

namespace hdf5 {
namespace dataspace {

class Selection
{
  public:
    Selection();
    Selection(const Selection &) = default;
    virtual ~Selection();

    virtual void apply(const Dataspace &space,
                       SelectionOperation ops) const = 0;
};

class Hyperslab : public Selection
{
  public:
    Hyperslab();
    ~Hyperslab();
    Hyperslab(const Hyperslab &) = default;
    Hyperslab(size_t rank);
    Hyperslab(const Dimensions &start,
              const Dimensions &stride,
              const Dimensions &count,
              const Dimensions &block);

    Dimensions &start();
    const Dimensions &start() const;
    Dimensions &stride();
    const Dimensions &stride() const;
    Dimensions &count();
    const Dimensions &count() const;
    Dimensions &block();
    const Dimensions &block() const;

    virtual void apply(const Dataspace &space,
                       SelectionOperation ops) const;

  private:
    Dimensions start_;
    Dimensions stride_;
    Dimensions count_;
    Dimensions block_;


};

class Points : public Selection
{
  public:
    Points();
    Points(size_t rank);
    ~Points();

    virtual void apply(const Dataspace &space,
                       SelectionOperation ops) const;

};

} // namespace dataspace
} // namespace hdf5
