//
// (c) Copyright 2017 DESY,ESS
//               2021 Eugen Wintersberger <eugen.wintersberger@gmail.com>
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
// Created on: Nov 17, 2017
//
#include <algorithm>
#include <catch2/catch.hpp>
#include <h5cpp/hdf5.hpp>

using namespace hdf5;

using Paths = std::vector<Path>;

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wexit-time-destructors"
#pragma clang diagnostic ignored "-Wglobal-constructors"
#endif
namespace { 
const Paths paths_increasing{Path("/standard/a_group"),
                             Path("/standard/a_group/a_a_group"),
                             Path("/standard/a_group/b_a_group"),
                             Path("/standard/a_group/c_a_group"),
                             Path("/standard/a_group/d_a_dataset"),
                             Path("/standard/a_group/e_a_dataset"),
                             Path("/standard/b_group"),
                             Path("/standard/b_group/a_b_group"),
                             Path("/standard/b_group/a_b_group/data"),
                             Path("/standard/b_group/b_b_group"),
                             Path("/standard/b_group/c_b_group"),
                             Path("/standard/b_group/c_b_group/data"),
                             Path("/standard/c_group")};

const Paths paths_decreasing{Path("/standard/c_group"),
                             Path("/standard/b_group"),
                             Path("/standard/b_group/c_b_group"),
                             Path("/standard/b_group/c_b_group/data"),
                             Path("/standard/b_group/b_b_group"),
                             Path("/standard/b_group/a_b_group"),
                             Path("/standard/b_group/a_b_group/data"),
                             Path("/standard/a_group"),
                             Path("/standard/a_group/e_a_dataset"),
                             Path("/standard/a_group/d_a_dataset"),
                             Path("/standard/a_group/c_a_group"),
                             Path("/standard/a_group/b_a_group"),
                             Path("/standard/a_group/a_a_group")};
}
#ifdef __clang__
#pragma clang diagnostic pop
#endif

SCENARIO("testing recursive node iteration") {
  auto f = file::create("recursive_node_iterator_test.h5",
                        file::AccessFlags::TRUNCATE);
  auto r = node::Group(f.root(), "standard");
  node::Group(r, "c_group");
  node::Group b_group(r, "b_group");
  node::Group a_group(r, "a_group");

  node::Group(a_group, "c_a_group");
  node::Group(a_group, "b_a_group");
  node::Group(a_group, "a_a_group");
  node::Dataset dset_d(a_group, "d_a_dataset", datatype::create<int>());
  node::Dataset dset_e(a_group, "e_a_dataset", datatype::create<int>());

  node::Group(b_group, "c_b_group");
  node::Group(b_group, "b_b_group");
  node::Group(b_group, "a_b_group");

  node::link(dset_d, b_group, "c_b_group/data");
  node::link(dset_e, b_group, "a_b_group/data");

  using node::RecursiveLinkIterator;
  using node::RecursiveNodeIterator;
  REQUIRE(RecursiveNodeIterator::begin(r) == RecursiveNodeIterator::begin(r));
  REQUIRE(RecursiveNodeIterator::end(r) == RecursiveNodeIterator::end(r));
  REQUIRE(RecursiveLinkIterator::begin(r) == RecursiveLinkIterator::begin(r));
  REQUIRE(RecursiveLinkIterator::end(r) == RecursiveLinkIterator::end(r));

  GIVEN("the standard group as base") {
    node::Group base = node::get_node(f.root(), Path("standard"));
    AND_WHEN("configured to iterate by name index") {
      base.iterator_config().index(IterationIndex::NAME);
      AND_WHEN("configured for iteration in increasing order") {
        base.iterator_config().order(IterationOrder::INCREASING);
        THEN("we can iterate all child nodes") {
          Paths p;
          std::transform(RecursiveNodeIterator::begin(base),
                         RecursiveNodeIterator::end(base),
                         std::back_inserter(p),
                         [](const node::Node& n) { return n.link().path(); });
          REQUIRE_THAT(p, Catch::Matchers::Equals(paths_increasing));
        }
        THEN("iterating over all links") {
          Paths p;
          std::transform(RecursiveLinkIterator::begin(base),
                         RecursiveLinkIterator::end(base),
                         std::back_inserter(p),
                         [](const node::Link& l) { return l.path(); });
          REQUIRE_THAT(p, Catch::Matchers::Equals(paths_increasing));
        }
      }
      AND_WHEN("configured for iteration in decreasing order") {
        base.iterator_config().order(IterationOrder::DECREASING);
        THEN("we can iterate over all subgroups") {
          Paths p;
          std::transform(RecursiveNodeIterator::begin(base),
                         RecursiveNodeIterator::end(base),
                         std::back_inserter(p),
                         [](const node::Node& n) { return n.link().path(); });
          REQUIRE_THAT(p, Catch::Matchers::Equals(paths_decreasing));
        }
        THEN("iterating over all links") {
          Paths p;
          std::transform(RecursiveLinkIterator::begin(base),
                         RecursiveLinkIterator::end(base),
                         std::back_inserter(p),
                         [](const node::Link& l) { return l.path(); });
          REQUIRE_THAT(p, Catch::Matchers::Equals(paths_decreasing));
        }
      }
    }
  }
}
