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

#include <boost/test/unit_test.hpp>
#include <boost/test/output_test_stream.hpp>
#include <h5cpp/file/functions.hpp>
#include <h5cpp/node/group.hpp>
#include <h5cpp/node/types.hpp>
#include <h5cpp/datatype/factory.hpp>
#include <h5cpp/dataspace/scalar.hpp>
#include <h5cpp/property/link_creation_list.hpp>
#include <h5cpp/property/group_creation_list.hpp>
#include <h5cpp/property/file_creation_list.hpp>
#include <h5cpp/property/file_access_list.hpp>
#include <h5cpp/iterator_config.hpp>
#include <h5cpp/node/node_iterator.hpp>
#include <h5cpp/node/link_iterator.hpp>

struct BasicTestFixture
{
    hdf5::file::File file;

    BasicTestFixture();
};

struct NodeIterationFixture : public BasicTestFixture
{
    hdf5::node::Group root_group;

    NodeIterationFixture();
};

struct LinkIterationFixture : public NodeIterationFixture
{
    LinkIterationFixture();
};
