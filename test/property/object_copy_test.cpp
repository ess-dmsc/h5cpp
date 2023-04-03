//
// (c) Copyright 2017 DESY,ESS
//               2020 Eugen Wintersberger <eugen.wintersberger@gmail.com>
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
// Authors:
//   Eugen Wintersberger <eugen.wintersberger@gmail.com>
//   Martin Shetty <martin.shetty@esss.se>
// Created on: Oct 09, 2017
//

#include <catch2/catch_amalgamated.hpp>
#include <h5cpp/property/object_copy.hpp>
#include "../utilities.hpp"
#include "utilities.hpp"

using namespace hdf5;

SCENARIO("wrting the CopyFlag to a stream")
{
  std::stringstream stream;
  using property::CopyFlag;
  using r = std::tuple<property::CopyFlag, std::string>;
  auto flags = GENERATE(table<property::CopyFlag, std::string>(
      {r{CopyFlag::ShallowHierarchy, "SHALLOW_HIERARCHY"},
       r{CopyFlag::ExpandSoftLinks, "EXPAND_SOFT_LINKS"},
       r{CopyFlag::ExpandExternalLinks, "EXPAND_EXTERNAL_LINKS"},
       r{CopyFlag::ExpandReferences, "EXPAND_REFERENCES"},
       r{CopyFlag::WithoutAttributes, "WITHOUT_ATTRIBUTES"},
       r{CopyFlag::MergeCommittedTypes, "MERGE_COMMITTED_TYPES"}}));
  THEN("we get")
  {
    stream << std::get<0>(flags);
    REQUIRE(stream.str() == std::get<1>(flags));
  }
}

SCENARIO("Copy flags operators")
{
  using property::CopyFlag;
  using property::CopyFlags;
  GIVEN("SHALLOW_HIERARCHY | EXPAND_SOFT_LINKS")
  {
    auto flags = CopyFlag::ShallowHierarchy | CopyFlag::ExpandSoftLinks;
    THEN("we expect")
    {
      REQUIRE(flags.shallow_hierarchy());
      REQUIRE(flags.expand_soft_links());
      REQUIRE_FALSE(flags.expand_external_links());
      REQUIRE_FALSE(flags.expand_references());
      REQUIRE_FALSE(flags.without_attributes());
      REQUIRE_FALSE(flags.merge_committed_types());
    }
  }
  GIVEN("default constructed copy flags")
  {
    CopyFlags flags;
    WHEN("using the unary | operator on such flags")
    {
      flags |= property::CopyFlag::ExpandExternalLinks;
      THEN("the approriate flag will be set")
      {
        REQUIRE(flags.expand_external_links());
      }
    }
  }

  GIVEN("EXPAND_SOFT_LINKS | EXPAND_EXTERNAL_LINKS")
  {
    auto flags = CopyFlag::ExpandSoftLinks | CopyFlag::ExpandExternalLinks;
    THEN("we expect")
    {
      REQUIRE_FALSE(flags.shallow_hierarchy());
      REQUIRE(flags.expand_soft_links());
      REQUIRE(flags.expand_external_links());
      REQUIRE_FALSE(flags.expand_references());
      REQUIRE_FALSE(flags.without_attributes());
      REQUIRE_FALSE(flags.merge_committed_types());
    }
  }
  GIVEN("EXPAND_EXTERNAL_LINKS | EXPAND_REFERENCES")
  {
    auto flags = CopyFlag::ExpandExternalLinks | CopyFlag::ExpandReferences;
    THEN("we expect")
    {
      REQUIRE_FALSE(flags.shallow_hierarchy());
      REQUIRE_FALSE(flags.expand_soft_links());
      REQUIRE(flags.expand_external_links());
      REQUIRE(flags.expand_references());
      REQUIRE_FALSE(flags.without_attributes());
      REQUIRE_FALSE(flags.merge_committed_types());
    }
  }

  GIVEN("EXPAND_REFERENCES | WITHOUT_ATTRIBUTES")
  {
    auto flags = CopyFlag::ExpandReferences | CopyFlag::WithoutAttributes;
    THEN("we expect")
    {
      REQUIRE_FALSE(flags.shallow_hierarchy());
      REQUIRE_FALSE(flags.expand_soft_links());
      REQUIRE_FALSE(flags.expand_external_links());
      REQUIRE(flags.expand_references());
      REQUIRE(flags.without_attributes());
      REQUIRE_FALSE(flags.merge_committed_types());
    }
  }

  GIVEN("WITHOUT_ATTRIBUTES | MERGE_COMMITTED_TYPES")
  {
    auto flags = CopyFlag::WithoutAttributes | CopyFlag::MergeCommittedTypes;

    THEN("we expect")
    {
      REQUIRE_FALSE(flags.shallow_hierarchy());
      REQUIRE_FALSE(flags.expand_soft_links());
      REQUIRE_FALSE(flags.expand_external_links());
      REQUIRE_FALSE(flags.expand_references());
      REQUIRE(flags.without_attributes());
      REQUIRE(flags.merge_committed_types());
    }
  }

  GIVEN("MERGE_COMMITTED_TYPES | SHALLOW_HIERARCHY")
  {
    auto flags = CopyFlag::MergeCommittedTypes | CopyFlag::ShallowHierarchy;

    THEN("we expect")
    {
      REQUIRE(flags.shallow_hierarchy());
      REQUIRE_FALSE(flags.expand_soft_links());
      REQUIRE_FALSE(flags.expand_external_links());
      REQUIRE_FALSE(flags.expand_references());
      REQUIRE_FALSE(flags.without_attributes());
      REQUIRE(flags.merge_committed_types());
    }
  }
  GIVEN("EXPAND_EXTERNAL_LINKS | EXPAND_SOFT_LINKS | WITHOUT_ATTRIBUTES")
  {
    auto flags = CopyFlag::ExpandExternalLinks | CopyFlag::ExpandSoftLinks |
                 CopyFlag::WithoutAttributes;
    REQUIRE(flags.without_attributes());
    REQUIRE(flags.expand_soft_links());
    REQUIRE(flags.expand_external_links());
  }

  GIVEN("(EXPAND_EXTERNAL_LINKS | EXPAND_SOFT_LINKS) & EXPAND_EXTERNAL_LINKS ")
  {
    auto flags = (CopyFlag::ExpandExternalLinks |
                  CopyFlag::ExpandSoftLinks) &
                 CopyFlag::ExpandExternalLinks;
    THEN("we get for the resulting flags")
    {
      REQUIRE_FALSE(flags.expand_soft_links());
      REQUIRE(flags.expand_external_links());
    }
  }
  GIVEN("EXPAND_EXTERNAL_LINKS & EXPAND_EXTERNAL_LINKS | EXPAND_SOFT_LINKS")
  {
    CopyFlags flags =
        CopyFlag::ExpandExternalLinks &
        (CopyFlag::ExpandExternalLinks |
         CopyFlag::ExpandSoftLinks);
    THEN("we get for the result flags")
    {
      REQUIRE_FALSE(flags.expand_soft_links());
      REQUIRE(flags.expand_external_links());
    }
  }

  GIVEN("(EXPAND_EXTERNAL_LINKS | EXPAND_SOFT_LINKS) & WITHOUT_ATTRIBUTES | EXPAND_SOFT_LINKS")
  {
    auto flags =
        (CopyFlag::ExpandExternalLinks |
         CopyFlag::ExpandSoftLinks) &
        (CopyFlag::WithoutAttributes |
         CopyFlag::ExpandSoftLinks);
    THEN("we get for the resulting flags")
    {
      REQUIRE(flags.expand_soft_links());
      REQUIRE_FALSE(flags.expand_external_links());
    }
  }
}

SCENARIO("CopyFlag construction and handling")
{
  GIVEN("default constructed CopyFlag")
  {
    property::CopyFlags flags;
    THEN("we expect the following values")
    {
      REQUIRE_FALSE(flags.shallow_hierarchy());
      REQUIRE_FALSE(flags.expand_soft_links());
      REQUIRE_FALSE(flags.expand_external_links());
      REQUIRE_FALSE(flags.expand_references());
      REQUIRE_FALSE(flags.without_attributes());
      REQUIRE_FALSE(flags.merge_committed_types());
    }
    THEN("we can set the shallow hierarchy flags")
    {
      flags.shallow_hierarchy(true);
      REQUIRE(flags.shallow_hierarchy());

      flags.shallow_hierarchy(false);
      REQUIRE_FALSE(flags.expand_soft_links());
    }
    THEN("we can set/unset the expand soft links flags")
    {
      flags.expand_soft_links(true);
      REQUIRE(flags.expand_soft_links());
      flags.expand_soft_links(false);
      REQUIRE_FALSE(flags.expand_soft_links());
    }
    THEN("we can set/unset the expand external links flags")
    {
      flags.expand_external_links(true);
      REQUIRE(flags.expand_external_links());
      flags.expand_external_links(false);
      REQUIRE_FALSE(flags.expand_external_links());
    }
    THEN("we can set/unset the expand references flag")
    {
      flags.expand_references(true);
      REQUIRE(flags.expand_references());
      flags.expand_references(false);
      REQUIRE_FALSE(flags.expand_references());
    }
    THEN("we can set/unset the without attributes flag")
    {
      flags.without_attributes(true);
      REQUIRE(flags.without_attributes());
      flags.without_attributes(false);
      REQUIRE_FALSE(flags.without_attributes());
    }
    THEN("we can set/unset the merge comitted types flag")
    {
      flags.merge_committed_types(true);
      REQUIRE(flags.merge_committed_types());
      flags.merge_committed_types(false);
      REQUIRE_FALSE(flags.merge_committed_types());
    }
  }
  GIVEN("default constructed flags")
  {
    property::CopyFlags flags;
    flags |= property::CopyFlag::ExpandExternalLinks;
    REQUIRE(flags.expand_external_links());
  }
}

SCENARIO("ObjectCopy property list construction")
{
  using property::CopyFlag;
  GIVEN("default constructed list")
  {
    property::ObjectCopyList ocpl;
    THEN("we expect") { REQUIRE(ocpl.get_class() == property::kObjectCopy); }
    AND_GIVEN("the flags")
    {
      auto flags =
          CopyFlag::ExpandSoftLinks | CopyFlag::ExpandExternalLinks;
      THEN("we can apply the flags to the list")
      {
        REQUIRE_NOTHROW(ocpl.flags(flags));
        AND_THEN("we can read the flags back via the list")
        {
          REQUIRE(ocpl.flags().expand_soft_links());
          REQUIRE_NOTHROW(
              ocpl.flags(property::CopyFlag::ExpandExternalLinks));
          REQUIRE(ocpl.flags().expand_external_links());
        }
      }
      AND_WHEN("closing the list")
      {
        close(ocpl);
        THEN("all operations must fail")
        {
          REQUIRE_THROWS_AS(ocpl.flags(flags), std::runtime_error);
          REQUIRE_THROWS_AS(ocpl.flags(), std::runtime_error);
          REQUIRE_THROWS_AS(
              ocpl.flags(property::CopyFlag::ExpandExternalLinks),
              std::runtime_error);
        }
      }
    }
    WHEN("closing the list instance")
    {
      close(ocpl);
      THEN("we should expect") {}
    }
  }
  GIVEN("a handle to a object copy property list")
  {
    auto handle = handle_from_class(property::kObjectCopy);
    THEN("we can construct an instance of the object copy list")
    {
      REQUIRE_NOTHROW(property::ObjectCopyList{std::move(handle)});
    }
  }
  GIVEN("a handle to a group create property list")
  {
    auto handle = handle_from_class(property::kGroupCreate);
    THEN("any attempt to construct an instance will fail")
    {
      REQUIRE_THROWS_AS(property::ObjectCopyList{std::move(handle)},
                        std::runtime_error);
    }
  }
}
