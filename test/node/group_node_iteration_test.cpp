//
// (c) Copyright 2017 DESY,ESS
//               2020 Eugen Wintersberger <eugen.wintersberger@gmail.com>
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
// Author: Eugen Wintersberger <eugen.wintersberger@gmail.com>
// Created on: Sep 13, 2017
//
#include <algorithm>
#include <catch2/catch.hpp>
#include <h5cpp/hdf5.hpp>
#include <vector>

using namespace hdf5;

using Nodes = std::vector<hdf5::node::Node>;

/**
 * @brief utility function producing node vectors
 *
 * Basically all this function does is to copy all the nodes below a group
 * to a vector.
 *
 * @param parent
 * @return Nodes
 */
Nodes to_nodes(const node::Group& parent) {
  Nodes nodes;
  std::copy(std::begin(parent.nodes), std::end(parent.nodes),
            std::back_inserter(nodes));
  return nodes;
}

SCENARIO("testing node iteration over a group") {
  dataspace::Scalar ds;
  property::LinkCreationList lcpl;
  property::FileCreationList fcpl;
  property::FileAccessList fapl;
  fapl.library_version_bounds(property::LibVersion::LATEST,
                              property::LibVersion::LATEST);

  property::GroupCreationList gcpl;
  gcpl.link_creation_order(property::CreationOrder().enable_indexed());
  fcpl.link_creation_order(property::CreationOrder().enable_indexed());
  auto f = file::create("group_node_iteration_test.h5",
                        file::AccessFlags::TRUNCATE, fcpl, fapl);
  auto r = f.root();
  auto g1 = r.create_group("g1", lcpl, gcpl);
  auto g2 = r.create_group("g2", lcpl, gcpl);
  auto g3 = r.create_group("g3", lcpl, gcpl);
  auto d1 = r.create_dataset("d1", datatype::create<float>(), ds);
  auto d2 = r.create_dataset("d2", datatype::create<int>(), ds);
  node::link(g1, r, "g1_soft_link");
  node::link(g2, r, "g2_soft_link");
  node::link(g3, r, "g3_soft_link");
  node::link(d1, r, "d1_soft_link");
  node::link(d2, r, "d2_soft_link");

  THEN("the total number of elements below the root group must be 10") {
    REQUIRE(r.nodes.size() == 10ul);
  }

  using node::LinkType;
  using node::Type;
  using tr = std::tuple<Type, LinkType, std::string>;

  auto node_type = [](const tr& n) { return std::get<0>(n); };
  auto link_type = [](const tr& l) { return std::get<1>(l); };
  auto name = [](const tr& l) { return std::get<2>(l); };
  auto path = [&name](const tr& l) { return "/" + name(l); };

  WHEN("access by index in decreasing order using the name as key") {
    r.iterator_config().index(hdf5::IterationIndex::NAME);
    r.iterator_config().order(hdf5::IterationOrder::DECREASING);
    std::vector<tr> values{tr{Type::GROUP, LinkType::SOFT, "g3_soft_link"},
                      tr{Type::GROUP, LinkType::HARD, "g3"},
                      tr{Type::GROUP, LinkType::SOFT, "g2_soft_link"},
                      tr{Type::GROUP, LinkType::HARD, "g2"},
                      tr{Type::GROUP, LinkType::SOFT, "g1_soft_link"},
                      tr{Type::GROUP, LinkType::HARD, "g1"},
                      tr{Type::DATASET, LinkType::SOFT, "d2_soft_link"},
                      tr{Type::DATASET, LinkType::HARD, "d2"},
                      tr{Type::DATASET, LinkType::SOFT, "d1_soft_link"},
                      tr{Type::DATASET, LinkType::HARD, "d1"}};
    THEN("we can access the nodes by their numeric index") {
      for (size_t index = 0; index < r.nodes.size(); ++index) {
        REQUIRE(r.nodes[index].type() == node_type(values[index]));
        REQUIRE(r.nodes[index].link().path() == path(values[index]));
        REQUIRE(r.links[index].type() == link_type(values[index]));
        REQUIRE(r.links[index].path() == path(values[index]));
      }
    }
    THEN("we can access names and links by name") { 
      for(auto v: values) { 
        auto n = name(v);
        REQUIRE(r.nodes[n].type() == node_type(v));
        REQUIRE(r.nodes[n].link().path() == path(v));
        REQUIRE(r.links[n].type() == link_type(v));
        REQUIRE(r.links[n].path() == path(v));
      }
    }
    THEN("we can access the elements by iterator") {
      auto eiter = values.begin();
      auto niter = r.nodes.begin();
      auto liter = r.links.begin();
      for (; niter != r.nodes.end(); ++niter, ++eiter, ++liter) {
        REQUIRE(niter->type() == node_type(*eiter));
        REQUIRE(niter->link().path() == path(*eiter));
        REQUIRE(liter->type() == link_type(*eiter));
        REQUIRE(liter->path() == path(*eiter));
      }
    }
    THEN("we can access the nodes via foreach") {
      auto eiter = values.begin();
      for (auto n : r.nodes) {
        auto e = eiter++;
        REQUIRE(n.type() == node_type(*e));
        REQUIRE(n.link().path() == path(*e));
      }
    }
    THEN("we can iterate the links via foreach") { 
      auto eiter = values.begin();
      for (auto l : r.links) {
        auto e = eiter++;
        REQUIRE(l.type() == link_type(*e));
        REQUIRE(l.path() == path(*e));
      }
    }
  }

  WHEN("access by index in increasing order using the creation order as key") {
    r.iterator_config().index(hdf5::IterationIndex::CREATION_ORDER);
    r.iterator_config().order(hdf5::IterationOrder::INCREASING);
    std::vector<tr> values{tr{Type::GROUP, LinkType::HARD, "g1"},
                           tr{Type::GROUP, LinkType::HARD, "g2"},
                           tr{Type::GROUP, LinkType::HARD, "g3"},
                           tr{Type::DATASET, LinkType::HARD, "d1"},
                           tr{Type::DATASET, LinkType::HARD, "d2"},
                           tr{Type::GROUP, LinkType::SOFT, "g1_soft_link"},
                           tr{Type::GROUP, LinkType::SOFT, "g2_soft_link"},
                           tr{Type::GROUP, LinkType::SOFT, "g3_soft_link"},
                           tr{Type::DATASET, LinkType::SOFT, "d1_soft_link"},
                           tr{Type::DATASET, LinkType::SOFT, "d2_soft_link"}};
    THEN("we can access the element by numeric index") {
      for (size_t index = 0; index < r.nodes.size(); ++index) {
        REQUIRE(r.nodes[index].type() == node_type(values[index]));
        REQUIRE(r.nodes[index].link().path() == path(values[index]));
        REQUIRE(r.links[index].type() == link_type(values[index]));
        REQUIRE(r.links[index].path() == path(values[index]));
      }
    }
    THEN("we can access names and links by name") { 
      for(auto v: values) { 
        auto n = name(v);
        REQUIRE(r.nodes[n].type() == node_type(v));
        REQUIRE(r.nodes[n].link().path() == path(v));
        REQUIRE(r.links[n].type() == link_type(v));
        REQUIRE(r.links[n].path() == path(v));
      }
    }
    THEN("we can access the elements by iterator") {
      auto eiter = values.begin();
      for (auto niter = r.nodes.begin(); niter != r.nodes.end();
           ++niter, ++eiter) {
        REQUIRE(niter->type() == node_type(*eiter));
        REQUIRE(niter->link().path() == path(*eiter));
      }
    }
    THEN("we can access the nodes via foreach") {
      auto eiter = values.begin();
      for (auto n : r.nodes) {
        auto e = eiter++;
        REQUIRE(n.type() == node_type(*e));
        REQUIRE(n.link().path() == path(*e));
      }
    }
    THEN("we can iterate the links via foreach") { 
      auto eiter = values.begin();
      for (auto l : r.links) {
        auto e = eiter++;
        REQUIRE(l.type() == link_type(*e));
        REQUIRE(l.path() == path(*e));
      }
    }
  }
}
