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
// Created on: Sep 13, 2017
//

#include "group_test_fixtures.hpp"
#include <h5cpp/hdf5.hpp>

void NodeIterationFixture::SetUp()
{
  BasicFixture::SetUp();

  using namespace hdf5;
  property::LinkCreationList lcpl;
  property::GroupCreationList gcpl;
  gcpl.link_creation_order(property::CreationOrder().enable_indexed());
  node::Group(root_,Path("g1"),lcpl,gcpl);
  node::Group(root_,Path("g2"),lcpl,gcpl);
  node::Group(root_,Path("g3"),lcpl,gcpl);
  node::Dataset(root_,Path("d1"),datatype::create<float>());
  node::Dataset(root_,Path("d2"),datatype::create<int>());
}

