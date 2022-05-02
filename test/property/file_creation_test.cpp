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
// Created on: Aug 21, 2017
//

#include <catch2/catch.hpp>
#include <h5cpp/property/file_creation.hpp>
#include <h5cpp/core/utilities.hpp>
#include <tuple>
#include "../utilities.hpp"

namespace pl = hdf5::property;

SCENARIO("FileCreationList construction") {
  GIVEN("a default constructed list") {
    pl::FileCreationList fcpl;
    THEN("then we get the following default behavior") {
      REQUIRE(fcpl.get_class() == pl::kFileCreate);
      REQUIRE(fcpl.user_block() == 0);
      REQUIRE(fcpl.object_offset_size() == sizeof(hsize_t));
      REQUIRE(fcpl.object_length_size() == sizeof(hsize_t));
      REQUIRE(fcpl.btree_rank() == 16u);
      REQUIRE(fcpl.btree_symbols() == 4u);
      REQUIRE(fcpl.chunk_tree_rank() == 32u);
      REQUIRE(fcpl.chunk_tree_rank() == 32u);
#if H5_VERSION_GE(1, 10, 1)
      REQUIRE(fcpl.page_size() == 4096lu);
#endif
    }
    AND_WHEN("we close the instance") {
      close(fcpl);
      THEN("accessing the member methods will produce exceptions") {
        REQUIRE_THROWS_AS(fcpl.user_block(), std::runtime_error);
        REQUIRE_THROWS_AS(fcpl.object_offset_size(), std::runtime_error);
        REQUIRE_THROWS_AS(fcpl.object_length_size(), std::runtime_error);
        REQUIRE_THROWS_AS(fcpl.btree_rank(), std::runtime_error);
        REQUIRE_THROWS_AS(fcpl.btree_symbols(), std::runtime_error);
        REQUIRE_THROWS_AS(fcpl.btree_symbols(7), std::runtime_error);
        REQUIRE_THROWS_AS(fcpl.chunk_tree_rank(), std::runtime_error);
        REQUIRE_THROWS_AS(fcpl.page_size(), std::runtime_error);
      }
    }
  }
  GIVEN("A handle to a file creation list") {
    hdf5::ObjectHandle handle{H5Pcreate(to_hid(pl::kFileCreate))};
    THEN("we can create a new FileCreationList instance from it") {
      REQUIRE_NOTHROW(pl::FileCreationList{std::move(handle)});
    }
  }
  GIVEN("a handle to a group creation list") {
    hdf5::ObjectHandle handle{H5Pcreate(to_hid(pl::kGroupCreate))};
    THEN("the FileCreationList instantiation will fail") {
      REQUIRE_THROWS_AS(pl::FileCreationList{std::move(handle)},
                        std::runtime_error);
    }
  }
}

SCENARIO("setting the user block sice on a FileCreationList") {
  GIVEN("a default constructed list instnace") {
    pl::FileCreationList fcpl;
    AND_GIVEN("a block size of 1024") {
      size_t block_size = 1024;
      WHEN("setting the user block size") {
        fcpl.user_block(block_size);
        AND_THEN("read it back") { REQUIRE(fcpl.user_block() == block_size); }
      }
    }
    AND_GIVEN("a too small block size of 256") {
      size_t block_size = 256;
      THEN("setting the block size will fail") {
        REQUIRE_THROWS_AS(fcpl.user_block(block_size), std::runtime_error);
      }
    }
    AND_GIVEN("a  block size not a power of 2") {
      size_t block_size = 513;
      THEN("setting the block size with it will fail") {
        REQUIRE_THROWS_AS(fcpl.user_block(block_size), std::runtime_error);
      }
    }
  }
}

SCENARIO("setting the object offset size on a FileCreationList") {
  pl::FileCreationList fcpl;
  GIVEN("an object length size to 2") {
    REQUIRE_NOTHROW(fcpl.object_length_size(2));
    AND_GIVEN("valid values forthe offset size") {
      auto size = GENERATE(size_t(2), size_t(4), size_t(8), size_t(16));
      THEN("we can set the object offset") {
        REQUIRE_NOTHROW(fcpl.object_offset_size(size));
        AND_THEN("read it back and get") {
          REQUIRE(fcpl.object_offset_size() == size);
          REQUIRE(fcpl.object_length_size() == 2);
        }
      }
    }
    AND_GIVEN("invalid values for the offset size") {
      auto size = GENERATE(size_t(15), size_t(25));
      THEN("setting the offset will fail") {
        REQUIRE_THROWS_AS(fcpl.object_offset_size(size), std::runtime_error);
      }
    }
  }
}

SCENARIO("setting the object length size on a FileCreationList") {
  pl::FileCreationList fcpl;
  GIVEN("an object offset size of 2") {
    REQUIRE_NOTHROW(fcpl.object_offset_size(2));
    AND_GIVEN("valid values for the lenght size") {
      auto size = GENERATE(size_t(2), size_t(4), size_t(8), size_t(16));
      THEN("we can set the object length size") {
        REQUIRE_NOTHROW(fcpl.object_length_size(size));
        AND_THEN("read it back and get") {
          REQUIRE(fcpl.object_length_size() == size);
          REQUIRE(fcpl.object_offset_size() == 2);
        }
      }
    }
    AND_GIVEN("invalid values for the length size") {
      auto size = GENERATE(size_t(15), size_t(25));
      REQUIRE_THROWS_AS(fcpl.object_length_size(size), std::runtime_error);
    }
  }
}

SCENARIO("setting the btree rank on a FileCreationList") {
  pl::FileCreationList fcpl;
  using r = std::tuple<size_t, size_t>;
  auto p = GENERATE(table<size_t, size_t>({r{0, 16}, r{2, 2}, r{32767, 32767}}));
  WHEN("setting the btree rank") {
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wshorten-64-to-32"
#endif
    REQUIRE_NOTHROW(fcpl.btree_rank(static_cast<unsigned int>(std::get<0>(p))));
#ifdef __clang__
#pragma clang diagnostic pop
#endif 
    THEN("the value should be") {
      REQUIRE(fcpl.btree_rank() == std::get<1>(p));
    }
  }

#if H5_VERSION_GE(1, 10, 0)
  WHEN("trying to set the rank to a too large value") {
    THEN("the operation must fail") {
      REQUIRE_THROWS_AS(fcpl.btree_rank(32768), std::runtime_error);
    }
  }
#endif
}

SCENARIO("setting the btree symbols on a FileCreationList") {
  pl::FileCreationList fcpl;
  using r = std::tuple<size_t, size_t>;
  auto p = GENERATE(table<size_t, size_t>({r{0, 4}, r{7, 7}, r{42, 42}}));
  WHEN("setting the btree symbols to 0") {
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wshorten-64-to-32"
#endif
    REQUIRE_NOTHROW(fcpl.btree_symbols(static_cast<unsigned int>(std::get<0>(p))));
#ifdef __clang__
#pragma clang diagnostic pop
#endif 
    THEN("the value will be 4") {
      REQUIRE(fcpl.btree_symbols() == std::get<1>(p));
    }
  }
}

SCENARIO("setting the chunk tree rank on a FileCreationList") {
  pl::FileCreationList fcpl;
  WHEN("using valid rank values") {
    auto rank = GENERATE(1u, 2u, 32767u);
    THEN("we can set these values") {
      REQUIRE_NOTHROW(fcpl.chunk_tree_rank(rank));
      AND_THEN("read it back") { REQUIRE(fcpl.chunk_tree_rank() == rank); }
    }
  }
  WHEN("when trying to set the rank to 0") {
    THEN("the operation fails") {
      REQUIRE_THROWS_AS(fcpl.chunk_tree_rank(0), std::runtime_error);
    }
  }

#if H5_VERSION_GE(1, 10, 0)
  WHEN("trying to set the rank to a too high value") {
    THEN("the operation will fail") {
      REQUIRE_THROWS_AS(fcpl.chunk_tree_rank(32768), std::runtime_error);
    }
  }
#endif
}

#if H5_VERSION_GE(1, 10, 1)
SCENARIO("setting the page size on a FileCreationList") {
  pl::FileCreationList fcpl;

  WHEN("setting the page size to reasonable values") {
    auto page_size = GENERATE(hsize_t(512), hsize_t(513));
    THEN("we can set the page size") {
      REQUIRE_NOTHROW(fcpl.page_size(page_size));
      AND_THEN("read it back") { REQUIRE(fcpl.page_size() == page_size); }
    }
  }
  WHEN("using invalid values") {
    REQUIRE_THROWS_AS(fcpl.page_size(0), std::runtime_error);
    REQUIRE_THROWS_AS(fcpl.page_size(1), std::runtime_error);
    REQUIRE_THROWS_AS(fcpl.page_size(511), std::runtime_error);
  }
}
#endif
