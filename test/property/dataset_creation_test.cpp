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
// Authors:
//   Eugen Wintersberger <eugen.wintersberger@gmail.com>
//   Martin Shetty <martin.shetty@esss.se>
// Created on: Aug 28, 2017
//

#include <catch2/catch.hpp>
#include <h5cpp/datatype/factory.hpp>
#include <h5cpp/property/dataset_creation.hpp>
#include <tuple>
#include "../utilities.hpp"

namespace prop = hdf5::property;
namespace type = hdf5::datatype;

template <typename T>
using stream_record = std::tuple<T, std::string>;
using FillValueStatus = prop::DatasetFillValueStatus;
using FillTime = prop::DatasetFillTime;
using AllocationTime = prop::DatasetAllocTime;
using Layout = prop::DatasetLayout;

SCENARIO("stream output of dataset property list related enumeration types") {
  std::stringstream stream;
  WHEN("writing DatasetFillValueStatus to a stream") {
    using rtype = stream_record<FillValueStatus>;
    auto records = GENERATE(table<FillValueStatus, std::string>(
        {rtype{FillValueStatus::Undefined, "UNDEFINED"},
         rtype{FillValueStatus::Default, "DEFAULT"},
         rtype{FillValueStatus::UserDefined, "USER_DEFINED"}}));
    stream << std::get<0>(records);
    THEN("the content of the stream will be") {
      REQUIRE(std::get<1>(records) == stream.str());
    }
  }

  WHEN("writing DatasetFillTime to the stream") {
    using rtype = stream_record<FillTime>;
    auto records = GENERATE(table<prop::DatasetFillTime, std::string>(
        {rtype{FillTime::IfSet, "IFSET"}, rtype{FillTime::Alloc, "ALLOC"},
         rtype{FillTime::Never, "NEVER"}}));
    stream << std::get<0>(records);
    THEN("the content of the stream will be") {
      REQUIRE(std::get<1>(records) == stream.str());
    }
  }

  WHEN("writing the AllocationTime enumeration to a stream") {
    using r = stream_record<AllocationTime>;
    auto params = GENERATE(table<AllocationTime, std::string>(
        {r{AllocationTime::Default, "DEFAULT"},
         r{AllocationTime::Early, "EARLY"}, r{AllocationTime::Incr, "INCR"},
         r{AllocationTime::Late, "LATE"}}));
    stream << std::get<0>(params);
    THEN("the content of the stream will be") {
      REQUIRE(std::get<1>(params) == stream.str());
    }
  }

  WHEN("writing the DatasetLayout enumeration to a stream") {
    using r = stream_record<Layout>;
#if H5_VERSION_GE(1, 10, 0)
    auto params = GENERATE(table<Layout, std::string>({
      r{Layout::Compact, "COMPACT"}, r{Layout::Contiguous, "CONTIGUOUS"}, r {
        Layout::Chunked, "CHUNKED"
      }
      , r { Layout::Virtual, "VIRTUAL" }
    }));
#else
	auto params = GENERATE(table<Layout, std::string>({
  r{Layout::Compact, "COMPACT"}, r{Layout::Contiguous, "CONTIGUOUS"}, r {
	Layout::Chunked, "CHUNKED"
  } }));
#endif
	
    stream << std::get<0>(params);
    THEN("the content of the stream will be") {
      REQUIRE(std::get<1>(params) == stream.str());
    }
  }
}

SCENARIO("construction of a DatasetCreationList") {
  GIVEN("a default constructed list") {
    prop::DatasetCreationList pl;
    THEN("the list will he the following properties") {
      REQUIRE(pl.get_class() == prop::kDatasetCreate);
      REQUIRE(pl.layout() == prop::DatasetLayout::Contiguous);
      REQUIRE(pl.fill_time() == prop::DatasetFillTime::IfSet);
      REQUIRE(pl.allocation_time() == prop::DatasetAllocTime::Late);
      REQUIRE(pl.fill_value_status() == prop::DatasetFillValueStatus::Default);
    }
    WHEN("we close the actual creation list") {
      close(pl);
      THEN("all requests to the methods will raise an exception") {
        REQUIRE_THROWS_AS(pl.layout(prop::DatasetLayout::Chunked),
                          std::runtime_error);
        REQUIRE_THROWS_AS(pl.layout(), std::runtime_error);
        REQUIRE_THROWS_AS(pl.chunk({1}), std::runtime_error);
        REQUIRE_THROWS_AS(pl.chunk(), std::runtime_error);
        REQUIRE_THROWS_AS(pl.fill_time(prop::DatasetFillTime::IfSet),
                          std::runtime_error);
        REQUIRE_THROWS_AS(pl.fill_time(), std::runtime_error);
        REQUIRE_THROWS_AS(pl.allocation_time(prop::DatasetAllocTime::Late),
                          std::runtime_error);
        REQUIRE_THROWS_AS(pl.allocation_time(), std::runtime_error);
        REQUIRE_THROWS_AS(pl.fill_value(1024), std::runtime_error);
        REQUIRE_THROWS_AS(pl.fill_value_status(), std::runtime_error);
      }
    }
  }
  GIVEN("a constant of a creation property list class") {
    hdf5::ObjectHandle handle{H5Pcreate(to_hid(prop::kDatasetCreate))};
    THEN("we can construct a dataset creation property list from it") {
      REQUIRE_NOTHROW(prop::DatasetCreationList(std::move(handle)));
    }
  }
  GIVEN("a handle to a to a group creation property list") {
    hdf5::ObjectHandle handle{H5Pcreate(to_hid(prop::kGroupCreate))};
    THEN("the attempt to construct a DatasetCreation list from it will fail") {
      REQUIRE_THROWS_AS(prop::DatasetCreationList(std::move(handle)),
                        std::runtime_error);
    }
  }
}

SCENARIO("setting the layout on a DatasetCreation property list") {
  prop::DatasetCreationList pl;
#if H5_VERSION_GE(1, 10, 0)
  auto layouts = GENERATE(Layout::Contiguous, Layout::Chunked, Layout::Compact,
                          Layout::Virtual);
#else
  auto layouts = GENERATE(Layout::Contiguous, Layout::Chunked, Layout::Compact);
#endif
  
  WHEN("setting the layout") {
    pl.layout(layouts);
    THEN("the layout is given as") { REQUIRE(pl.layout() == layouts); }
  }
}

SCENARIO("setting the fill time on a DatasetCreation property list") {
  prop::DatasetCreationList pl;
  auto times = GENERATE(FillTime::Alloc, FillTime::IfSet, FillTime::Never);
  WHEN("setting the fill time to") {
    pl.fill_time(times);
    THEN("the fill time is") { REQUIRE(pl.fill_time() == times); }
  }
}

SCENARIO("setting the allocation time on a DatasetCreation property list") {
  prop::DatasetCreationList pl;
  using r = std::tuple<AllocationTime, AllocationTime>;
  auto times = GENERATE(table<AllocationTime, AllocationTime>(
      {r{AllocationTime::Late, AllocationTime::Late},
       r{AllocationTime::Default, AllocationTime::Late},
       r{AllocationTime::Early, AllocationTime::Early},
       r{AllocationTime::Incr, AllocationTime::Incr}}));
  WHEN("setting the allocation time") {
    pl.allocation_time(std::get<0>(times));
    THEN("the allocation time will be") {
      REQUIRE(pl.allocation_time() == std::get<1>(times));
    }
  }
}

SCENARIO("setting the chunk shape on a DatasetCreation property list") {
  prop::DatasetCreationList pl;
  GIVEN("dimensions of the chunk") {
    hdf5::Dimensions chunk_shape{10, 100};
    THEN("we can set the chunk dimensions") {
      pl.chunk(chunk_shape);
      AND_THEN("we can read this back") {
        REQUIRE_THAT(pl.chunk(), Catch::Matchers::Equals(chunk_shape));
      }
    }
  }
}

SCENARIO("setting the fill value on a DatasetCreation property list") {
  prop::DatasetCreationList pl;
  GIVEN("an integer value of 1024") {
    int fill_value{1024};
    WHEN("setting the fill value to the property list") {
      pl.fill_value(fill_value);
      THEN("we can read back the fill value") {
        REQUIRE(fill_value == pl.fill_value<int>());
      }
      THEN("the fill value status is user defined") {
        REQUIRE(FillValueStatus::UserDefined == pl.fill_value_status());
      }
    }
    GIVEN("an integer HDF5 datatype") {
      auto set_type = type::create<int>();
      THEN("we can use this to set the fill value") { 
        pl.fill_value(fill_value, set_type);
        AND_GIVEN("a custom HDF5 type for floats") { 
          auto get_type = type::create<float>();
          AND_GIVEN("a float buffer") { 
            float buffer{0.0};
            THEN("we can read the fill vlaue back as a float") { 
              buffer = pl.fill_value<float>(get_type);
              REQUIRE(buffer == float(fill_value));
            }
          }
        }
      }
    }
  }
}
