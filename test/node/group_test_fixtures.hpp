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
// Created on: Sep 13, 2017
//
#pragma once 

#include <gtest/gtest.h>
#include "../fixture.hpp"

class NodeIterationFixture : public BasicFixture
{
  protected:
    virtual void SetUp();
};

class RecursiveIterationFixture : public testing::Test
{
  private:
    static void create_standard_test(const hdf5::node::Group &root);
    static void create_linked_group_test(const hdf5::node::Group &root);
  public:
    hdf5::property::FileCreationList fcpl;
    hdf5::property::FileAccessList fapl;
    hdf5::file::File file;

    RecursiveIterationFixture(const fs::path &filename);
    virtual ~RecursiveIterationFixture();
};

