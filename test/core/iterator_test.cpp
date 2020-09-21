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
// Created on: Sep 11, 2017
//

#include <h5cpp/core/iterator.hpp>
#include <catch2/catch.hpp>

using namespace hdf5;

TEST_CASE("Testing the iterator constructor")
{
  Iterator a;
  Iterator b(3);
  SECTION("default construction")
  {
    REQUIRE(a.index() == 0);
  }

  SECTION("constructor with index")
  {
    REQUIRE(b.index() == 3);
  }

  SECTION("implicit copy constructor")
  {
    Iterator c = b;
    REQUIRE(c.index() == 3);
  }

  SECTION("explicit copy constructor")
  {
    Iterator d(b);
    REQUIRE(d.index() == 3);
  }
}

SCENARIO("Testing the iterator comparators")
{
  GIVEN("Iterator at 2")
  {
    Iterator a(2);
    THEN("is equal to 2") { REQUIRE(a == Iterator(2)); }
    THEN("is smaller than 3") { REQUIRE(a < Iterator(3)); }
    THEN("is <= than 3") { REQUIRE(a <= Iterator(3)); }
    THEN("is <= than 2") { REQUIRE(a <= Iterator(2)); }
  }
  GIVEN("Iterator at 4")
  {
    Iterator a(4);
    THEN("is > than 3") { REQUIRE(a > Iterator(3)); }
    THEN("is >= 4") { REQUIRE(a >= Iterator(3)); }
    THEN("is >= 2") { REQUIRE(a >= Iterator(2)); }
  }
}

SCENARIO("Testing iterator increment")
{
  Iterator a(2);
  GIVEN("increment += 2")
  {
    a += 2;
    THEN("it must be at 3") { REQUIRE(a.index() == 4); }
  }
  GIVEN("postifix a++")
  {
    a++;
    THEN("it must be at 3") { REQUIRE(a.index() == 3); }
  }
  GIVEN("prefix ++a")
  {
    ++a;
    THEN("it must be at 3") { REQUIRE(a.index() == 3); }
  }

  GIVEN("a+ssize_t(1)")
  {
    a = a + ssize_t(1);
    THEN(" it must be at 3") { REQUIRE(a.index() == 3); }
  }
  GIVEN("ssize_t(1) + a")
  {
    a = ssize_t(1) + a;
    THEN("it must be at 3") { REQUIRE(a.index() == 3); }
  }
}

SCENARIO("Testing interator decrement")
{
  Iterator i(7);
  GIVEN("i -= 2")
  {
    i -= 2;
    THEN("it must be at 5") { REQUIRE(5 == i.index()); }
  }
  GIVEN("i--")
  {
    THEN("it must be at 7")
    {
      REQUIRE(7 == (i--).index());
      AND_THEN("it must be at 6") { REQUIRE(6 == i.index()); }
    }
  }

  GIVEN("--i")
  {
    THEN("it must be at 6")
    {
      REQUIRE(6 == (--i).index());
      AND_THEN("it must be at 6") { REQUIRE(6 == i.index()); }
    }
  }

  GIVEN("i - Iterator(2)") { 
    THEN("it must be at 5") { REQUIRE(5 == i - Iterator(2)); }
  }
  GIVEN("i - ssize_t(1)") { 
    THEN("it must be at 6") { REQUIRE(6 == (i - ssize_t(1)).index()); }
  }
}
