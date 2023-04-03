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
// Created on: Aug 25, 2017
//
#include <catch2/catch_all.hpp>
#include <h5cpp/dataspace/hyperslab.hpp>
#include <h5cpp/dataspace/simple.hpp>
#include <h5cpp/hdf5.hpp>

using namespace hdf5;

SCENARIO("Hyperslab construction") {
  GIVEN("a default constructed hyperslab") {
    dataspace::Hyperslab h;
    THEN("the rank would be 0") { REQUIRE(h.rank() == 0ul); }
    THEN("the size must be 0") { REQUIRE(h.size() == 0ul); }
    THEN("the type must be Hyperslab") {
      REQUIRE(h.type() == hdf5::dataspace::SelectionType::Hyperslab);
    }
    THEN("dimensions access must fail") {
      REQUIRE_THROWS_AS(h.dimensions(), std::runtime_error);
    }
    THEN("offset access must fail") {
      REQUIRE_THROWS_AS(h.offset(), std::runtime_error);
    }
    THEN("block access must fail") {
      REQUIRE_THROWS_AS(h.block(), std::runtime_error);
    }
    THEN("count access must fail") {
      REQUIRE_THROWS_AS(h.count(), std::runtime_error);
    }
    THEN("stride access must") {
      REQUIRE_THROWS_AS(h.stride(), std::runtime_error);
    }
  }

  GIVEN("a hyperslab constructed from the number of dimensions") {
    dataspace::Hyperslab hyperslab(2);
    THEN("the rank must be 2") { REQUIRE(hyperslab.rank() == 2ul); }
    THEN("the size must be 0") { REQUIRE(hyperslab.size() == 0ul); }
    THEN("the type must be Hyperslab") {
      REQUIRE(hyperslab.type() == hdf5::dataspace::SelectionType::Hyperslab);
    }
    THEN("dimensions access be 0") {
      REQUIRE_THAT(hyperslab.dimensions(),
                   Catch::Matchers::Equals(Dimensions{0, 0}));
    }
    THEN("all offset must be 0") {
      REQUIRE_THAT(hyperslab.offset(),
                   Catch::Matchers::Equals(Dimensions{0, 0}));
    }
    THEN("all strides must be 1") {
      REQUIRE_THAT(hyperslab.stride(),
                   Catch::Matchers::Equals(Dimensions{1, 1}));
    }
    THEN("all counts must be 0") {
      REQUIRE_THAT(hyperslab.count(),
                   Catch::Matchers::Equals(Dimensions{0, 0}));
    }
    THEN("all blocks must be 0") {
      REQUIRE_THAT(hyperslab.block(),
                   Catch::Matchers::Equals(Dimensions{0, 0}));
    }
  }

  GIVEN("given an offset of {1,2}") {
    Dimensions offset{1, 2};
    AND_GIVEN("a block of {3,4}") {
      Dimensions block{3, 4};
      THEN("a hyperslab can be constructed") {
        dataspace::Hyperslab h(offset, block);
        AND_THEN("the rank will be 2") { REQUIRE(h.rank() == 2); }
	AND_THEN("the size must be 12") { REQUIRE(h.size() == 12ul); }
	AND_THEN("the type must be Hyperslab") {
	  REQUIRE(h.type() == hdf5::dataspace::SelectionType::Hyperslab);
	}
	AND_THEN("dimensions access be {3,4}") {
	  REQUIRE_THAT(h.dimensions(),
		       Catch::Matchers::Equals(Dimensions{3, 4}));
        }
        AND_THEN("the offset will be {1,2}") {
          REQUIRE_THAT(h.offset(), Catch::Matchers::Equals(Dimensions{1, 2}));
        }
        AND_THEN("the block will be {3,4}") {
          REQUIRE_THAT(h.block(), Catch::Matchers::Equals(Dimensions{3, 4}));
        }
        AND_THEN("the count will be {1,1}") {
          REQUIRE_THAT(h.count(), Catch::Matchers::Equals(Dimensions{1, 1}));
        }
        AND_THEN("the stride will be {1,1}") {
          REQUIRE_THAT(h.stride(), Catch::Matchers::Equals(Dimensions{1, 1}));
        }
      }
    }
    AND_GIVEN("a count of {3,4}") {
      Dimensions count{3, 4};
      AND_GIVEN("a stride of {5,6}") {
        Dimensions stride{5, 6};
        THEN("a hyperslab can be constructed") {
          dataspace::Hyperslab h(offset, count, stride);
          AND_THEN("the ranke will be 2") { REQUIRE(h.rank() == 2); }
	  AND_THEN("the size must be 12") { REQUIRE(h.size() == 12ul); }
	  AND_THEN("the type must be Hyperslab") {
	    REQUIRE(h.type() == hdf5::dataspace::SelectionType::Hyperslab);
	  }
	  AND_THEN("dimensions access be {3,4} ") {
	    REQUIRE_THAT(h.dimensions(),
			 Catch::Matchers::Equals(Dimensions{3, 4}));
	  }
          AND_THEN("the offset will be {1,2}") {
            REQUIRE_THAT(h.offset(), Catch::Matchers::Equals(Dimensions{1, 2}));
          }
          AND_THEN("the block will be {1,1}") {
            REQUIRE_THAT(h.block(), Catch::Matchers::Equals(Dimensions{1, 1}));
          }
          AND_THEN("the counts will be {3,4}") {
            REQUIRE_THAT(h.count(), Catch::Matchers::Equals(Dimensions{3, 4}));
          }
          AND_THEN("the stride must be {5,6}") {
            REQUIRE_THAT(h.stride(), Catch::Matchers::Equals(Dimensions{5, 6}));
          }
        }
      }
    }
    AND_GIVEN("a block of {3,4}") {
      Dimensions block{3, 4};
      AND_GIVEN("a count of {5,6}") {
        Dimensions count{5, 6};
        AND_GIVEN("a stride of {7,8}") {
          Dimensions stride{7, 8};
          THEN("a hyperslab can be constructed with") {
            dataspace::Hyperslab h(offset, block, count, stride);
            AND_THEN("the rank will be 2") { REQUIRE(h.rank() == 2); }
	    AND_THEN("the size must be 360") { REQUIRE(h.size() == 360ul); }
	    AND_THEN("the type must be Hyperslab") {
	      REQUIRE(h.type() == hdf5::dataspace::SelectionType::Hyperslab);
	    }
	    AND_THEN("dimensions access be {15,24} ") {
	      REQUIRE_THAT(h.dimensions(),
			   Catch::Matchers::Equals(Dimensions{15, 24}));
	    }
            AND_THEN("the offset will be {1,2}") {
              REQUIRE_THAT(h.offset(),
                           Catch::Matchers::Equals(Dimensions{1, 2}));
            }
            AND_THEN("the block will be {3,4}") {
              REQUIRE_THAT(h.block(),
                           Catch::Matchers::Equals(Dimensions{3, 4}));
            }
            AND_THEN("the count will  be {5,6}") {
              REQUIRE_THAT(h.count(),
                           Catch::Matchers::Equals(Dimensions{5, 6}));
            }
            AND_THEN("the stride will be {7,8}") {
              REQUIRE_THAT(h.stride(),
                           Catch::Matchers::Equals(Dimensions{7, 8}));
            }
          }
        }
      }
    }
  }
}

SCENARIO("Hyperslab modifications") {
  GIVEN("as hyperslab constructed from a rank 2") {
    dataspace::Hyperslab h(2);

    WHEN("setting the offset for index 0") {
      REQUIRE_NOTHROW(h.offset(0, 3));
      THEN("the new offset must be 3") { REQUIRE(h.offset()[0] == 3); }
    }
    WHEN("setting the offset for the entire hyperslab to {5,6}") {
      REQUIRE_NOTHROW(h.offset({5, 6}));
      THEN("the new offset must be") {
        REQUIRE_THAT(h.offset(), Catch::Matchers::Equals(Dimensions{5, 6}));
      }
    }
    WHEN("trying to set the offset for index 2") {
      REQUIRE_THROWS_AS(h.offset(2, 0), std::runtime_error);
    }
    WHEN("trying to set an offset to a too small value") {
      REQUIRE_THROWS_AS(h.offset({1}), std::runtime_error);
    }

    WHEN("setting the block for index 0 to 3") {
      REQUIRE_NOTHROW(h.block(0, 3ul));
      THEN("the new offset must be 3") { REQUIRE(h.block()[0] == 3ul); }
    }

    WHEN("setting the block for the entire hyperslab to {3,4}") {
      REQUIRE_NOTHROW(h.block({3, 4}));
      THEN("the new block must be") {
        REQUIRE_THAT(h.block(), Catch::Matchers::Equals(Dimensions{3, 4}));
      }
    }
    WHEN("trying to set the offset for index 2") {
      REQUIRE_THROWS_AS(h.block(2, 0), std::runtime_error);
    }
    WHEN("trying to set the offset to {1") {
      REQUIRE_THROWS_AS(h.block({1}), std::runtime_error);
    }

    WHEN("setting the count for index 1") {
      REQUIRE_NOTHROW(h.count(1, 10));
      THEN("the new count for index 1 must be 10") {
        REQUIRE(h.count()[1] == 10);
      }
    }

    WHEN("setting the count for all dimensions to {10,20}") {
      REQUIRE_NOTHROW(h.count({10, 20}));
      THEN("the new count must be {10,20}") {
        REQUIRE_THAT(h.count(), Catch::Matchers::Equals(Dimensions{10, 20}));
      }
    }

    WHEN("trying to set the count for index 2") {
      REQUIRE_THROWS_AS(h.count(3, 1), std::runtime_error);
    }

    WHEN("trying to set the count to {10,20,30}") {
      REQUIRE_THROWS_AS(h.count({10, 20, 30}), std::runtime_error);
    }

    WHEN("setting the stride for index 1 to 2") {
      REQUIRE_NOTHROW(h.stride(1, 2));
      THEN("the new stride for index 1 must be 2") {
        REQUIRE(h.stride()[1] == 2);
      }
    }

    WHEN("setting the stride to {2,2}") {
      REQUIRE_NOTHROW(h.stride({2, 2}));
      THEN("the new stride must be {2,2") {
        REQUIRE_THAT(h.stride(), Catch::Matchers::Equals(Dimensions{2, 2}));
      }
    }

    WHEN("trying to set the stride for index 5") {
      REQUIRE_THROWS_AS(h.stride(5, 10), std::runtime_error);
    }

    WHEN("trying to set the stride to {3}") {
      REQUIRE_THROWS_AS(h.stride({1}), std::runtime_error);
    }
  }
}

SCENARIO("Testing the hyperslab functionality") {
  GIVEN("a simple dataspace of shape {10,1024}") {
    dataspace::Simple space({10, 1024});
    AND_GIVEN("a selection") {
      dataspace::Hyperslab slice{{0, 0}, {1, 1024}};
      WHEN("applying the selection") {
        space.selection(dataspace::SelectionOperation::Set, slice);
        THEN("the selection size is") {
          REQUIRE(space.selection.size() == 1024ul);
        }
      }
    }
    AND_GIVEN("a scattered selection") {
      dataspace::Hyperslab selection{{1, 1}, {3, 10}, {2, 4}};
      WHEN("applying the selection") {
        space.selection(dataspace::SelectionOperation::Set, selection);
        THEN("the selection size is 30") {
          REQUIRE(space.selection.size() == 30ul);
        }
      }
    }
  }

  GIVEN("a simple dataspace {20,1024}") {
    dataspace::Simple space{{20, 1024}};
    AND_GIVEN("a hpyerslab selection") {
      dataspace::Hyperslab selection{{1, 1}, {3, 10}, {2, 4}};
      WHEN("applying the selection to the dataspace") {
        space.selection(dataspace::SelectionOperation::Set, selection);
        THEN("the selection size is 30") {
          REQUIRE(space.selection.size() == 30ul);
        }
        AND_WHEN("we copy construct from this dataspace") {
          dataspace::Simple new_space(space);
          THEN(
              "the new dataspace inherits the selection from the original "
              "dataspace") {
            REQUIRE(new_space.selection.size() == 30ul);
          }
        }
      }
      WHEN("closing the dataspace") {
        ObjectHandle(static_cast<hid_t>(space)).close();
        THEN("appliying the selection will fail") {
          REQUIRE_THROWS_AS(
              selection.apply(space, dataspace::SelectionOperation::Set),
              std::runtime_error);
        }
      }
    }
  }

  GIVEN("the first hyperslab test case") {
    dataspace::Simple space({10, 20});
    dataspace::Hyperslab slab({1, 1}, {5, 5}, {1, 1}, {1, 1});
    space.selection(dataspace::SelectionOperation::Set, slab);
    REQUIRE(space.selection.size() == 25ul);
    REQUIRE(space.selection.type() == dataspace::SelectionType::Hyperslab);

    REQUIRE_NOTHROW(space.selection.all());
    REQUIRE(space.selection.type() == dataspace::SelectionType::All);
  }

  GIVEN("the second hyperslab test case") {
    dataspace::Simple space({10, 1024, 1024});
    REQUIRE(space.selection.type() == dataspace::SelectionType::All);

    dataspace::Hyperslab frame({0, 0, 0}, {1, 1024, 1024}, {1, 1, 1},
                               {1, 1, 1});
    REQUIRE_NOTHROW(space.selection(dataspace::SelectionOperation::Set, frame));
    frame.offset(0, 9);
    REQUIRE_NOTHROW(space.selection(dataspace::SelectionOperation::Or, frame));
    REQUIRE(space.selection.size() == 2ul * 1024ul * 1024ul);
  }
}
