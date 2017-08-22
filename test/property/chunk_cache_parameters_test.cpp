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
// Created on: Aug 22, 2017
//
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE testing ChunkCacheParameters class
#include <boost/test/unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>
#include <h5cpp/property/dataset_access_list.hpp>
#include <h5cpp/property/class.hpp>

namespace pl = hdf5::property;

BOOST_AUTO_TEST_SUITE(ChunkCacheParameters_test)

BOOST_AUTO_TEST_CASE(default_construction)
{
  pl::ChunkCacheParameters params;

  BOOST_CHECK_EQUAL(params.chunk_slots(),0);
  BOOST_CHECK_EQUAL(params.chunk_cache_size(),0);
  BOOST_CHECK_CLOSE(params.preemption_policy(),0.0,0.0001);
}

BOOST_AUTO_TEST_CASE(test_construction)
{
  pl::ChunkCacheParameters params(100,200,0.2);
  BOOST_CHECK_EQUAL(params.chunk_slots(),100);
  BOOST_CHECK_EQUAL(params.chunk_cache_size(),200);
  BOOST_CHECK_CLOSE(params.preemption_policy(),0.2,0.0001);
}

BOOST_AUTO_TEST_CASE(test_copy_construction)
{
  pl::ChunkCacheParameters params1(100,200,0.2);
  pl::ChunkCacheParameters params2(params1);
  BOOST_CHECK_EQUAL(params2.chunk_slots(),100);
  BOOST_CHECK_EQUAL(params2.chunk_cache_size(),200);
  BOOST_CHECK_CLOSE(params2.preemption_policy(),0.2,0.0001);
}

BOOST_AUTO_TEST_CASE(test_chunk_slots)
{
  pl::ChunkCacheParameters p;
  p.chunk_slots(20);
  BOOST_CHECK_EQUAL(p.chunk_slots(),20);
}

BOOST_AUTO_TEST_CASE(test_chunk_cache_size)
{
  pl::ChunkCacheParameters p;
  p.chunk_cache_size(200);
  BOOST_CHECK_EQUAL(p.chunk_cache_size(),200);
}

BOOST_AUTO_TEST_CASE(test_preemption_policy)
{
  pl::ChunkCacheParameters p;
  p.preemption_policy(0.2);
  BOOST_CHECK_CLOSE(p.preemption_policy(),0.2,0.0001);
}

BOOST_AUTO_TEST_SUITE_END()
