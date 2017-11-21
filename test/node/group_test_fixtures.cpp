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
  node::Group g1(root_,Path("g1"),lcpl,gcpl);
  node::Group g2(root_,Path("g2"),lcpl,gcpl);
  node::Group g3(root_,Path("g3"),lcpl,gcpl);
  node::Dataset d1(root_,Path("d1"),datatype::create<float>());
  node::Dataset d2(root_,Path("d2"),datatype::create<int>());
  node::link(g1,root_,Path("g1_soft_link"));
  node::link(g2,root_,Path("g2_soft_link"));
  node::link(g3,root_,Path("g3_soft_link"));
  node::link(d1,root_,Path("d1_soft_link"));
  node::link(d2,root_,Path("d2_soft_link"));
}

RecursiveIterationFixture::RecursiveIterationFixture(const boost::filesystem::path &filename):
    fcpl(),
    fapl(),
    file()
{
  using namespace hdf5;
  fapl.library_version_bounds(property::LibVersion::LATEST,
                              property::LibVersion::LATEST);

  using namespace hdf5;
  file = file::create(filename,
                      file::AccessFlags::TRUNCATE,fcpl,fapl);

  create_standard_test(node::Group(file.root(),Path("standard")));
  create_linked_group_test(node::Group(file.root(),Path("linkTest")));

  file.flush(file::Scope::GLOBAL);
}

RecursiveIterationFixture::~RecursiveIterationFixture()
{}

void RecursiveIterationFixture::create_standard_test(const hdf5::node::Group &root)
{
  using namespace hdf5;
  node::Group(root,Path("c_group"));
  node::Group b_group(root,Path("b_group"));
  node::Group a_group(root,Path("a_group"));

  node::Group(a_group,Path("c_a_group"));
  node::Group(a_group,Path("b_a_group"));
  node::Group(a_group,Path("a_a_group"));
  node::Dataset dset_d(a_group,Path("d_a_dataset"),datatype::create<int>());
  node::Dataset dset_e(a_group,Path("e_a_dataset"),datatype::create<int>());

  node::Group(b_group,Path("c_b_group"));
  node::Group(b_group,Path("b_b_group"));
  node::Group(b_group,Path("a_b_group"));

  node::link(dset_d,b_group,Path("c_b_group/data"));
  node::link(dset_e,b_group,Path("a_b_group/data"));
}

void RecursiveIterationFixture::create_linked_group_test(const hdf5::node::Group &root)
{
  using namespace hdf5;
  node::Group orig_group(root,Path("original"));
  node::Group(orig_group,Path("orig_1"));
  node::Group(orig_group,Path("orig_2"));
  node::link(orig_group,root,Path("link"));
}


