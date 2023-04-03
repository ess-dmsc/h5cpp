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
// Author: Martin Shetty <martin.shetty@esss.se>
//         Eugen Wintersberger <eugen.wintersberger@gmail.com>
// Created on: Oct 25, 2017
//
#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>
#include <h5cpp/hdf5.hpp>
#include <h5cpp/utilities/array_adapter.hpp>

using namespace hdf5;

using IntegerArrayAdapter = ArrayAdapter<int>;
using DoubleArrayAdapter = ArrayAdapter<double>;

SCENARIO("Default construction of an ArrayAdapter") {
  GIVEN("a default constructed adapter") {
    ArrayAdapter<int> adapter;
    THEN("the data will refer to nullptr") {
      REQUIRE(adapter.data() == nullptr);
    }
    THEN("the size will be 0") { REQUIRE(adapter.size() == 0ul); }
    WHEN("we ask for the dimensions") {
      auto dims = get_dimensions(adapter);
      THEN("the size of the dimensions will be 1") {
        REQUIRE(dims.size() == 1ul);
      }
      THEN("the number of dimensions will be 0") { REQUIRE(dims[0] == 0ul); }
    }
  }
}

SCENARIO("A non empty adapter") {
  size_t bufsize = 7ul;
  auto integer_data = new int[bufsize];
  GIVEN("an adapter constructed from a memory buffer") {
    ArrayAdapter<int> adapter(integer_data, bufsize);
    THEN("the data() will point to the original buffer") {
      REQUIRE(adapter.data() == integer_data);
      AND_THEN("the size will be equal to the buffer size") {
        REQUIRE(adapter.size() == bufsize);
      }
    }
    WHEN("we ask for the dimensions") {
      auto dimensions = get_dimensions(adapter);
      THEN("the returned dimensions wille be of size 1") {
        REQUIRE(dimensions.size() == 1ul);
        AND_THEN("the first dimensions will be the number of elements") {
          REQUIRE(dimensions[0] == bufsize);
        }
      }
    }
    WHEN("we copy construct a new adapter from the original one") {
      ArrayAdapter<int> a2(adapter);
      THEN("the sizes must match") { REQUIRE(a2.size() == adapter.size()); }
      THEN("the adapters must refer to the same memory location") {
        REQUIRE(a2.data() == adapter.data());
      }
    }
    WHEN("copy construct a new adapter") {
      ArrayAdapter<int> a2(std::move(adapter));
      THEN("the original datapter referse to nullptr") {
        REQUIRE(adapter.data() == nullptr);
        AND_THEN("its size will be 0") { REQUIRE(adapter.size() == 0ul); }
      }
      AND_THEN("the new adapter must refer to the original memory location") {
        REQUIRE(a2.data() == integer_data);
        AND_THEN("its size must be the equal to that of the buffer") {
          REQUIRE(a2.size() == bufsize);
        }
      }
    }
    AND_GIVEN("a default constructed adapter") {
      ArrayAdapter<int> a3;
      WHEN("copy assigning the original adapter") {
        a3 = adapter;
        THEN("the size will match the original") {
          REQUIRE(a3.size() == adapter.size());
          AND_THEN("both adapters will refer to the same memory") {
            REQUIRE(a3.data() == adapter.data());
          }
        }
      }
      WHEN("move assign the original adapter") {
        a3 = std::move(adapter);
        THEN("the original adapter will be invalidated") {
          REQUIRE(adapter.data() == nullptr);
          REQUIRE(adapter.size() == 0ul);
        }
        THEN("the LHS of the assignment will refer to the original buffer") {
          REQUIRE(a3.data() == integer_data);
          REQUIRE(a3.size() == bufsize);
        }
      }
    }
  }
}

SCENARIO("Constructing datatypes from adapter types") {
  GIVEN("an integer array datapter") {
    using adapter_type = ArrayAdapter<int>;
    WHEN("we construct a datatype using the type trait") {
      auto dtype = datatype::TypeTrait<adapter_type>::create();
      THEN("the resulting type will be an integer type") {
        REQUIRE(dtype.get_class() == datatype::Class::Integer);
        AND_THEN("the resulting integer type would be of size 4") {
          REQUIRE(dtype.size() == sizeof(int));
        }
      }
    }
  }
  GIVEN("an double array adapter") {
    using adapter_type = ArrayAdapter<double>;
    WHEN("we construct a datatype using the type trait") {
      auto dtype = datatype::TypeTrait<adapter_type>::create();
      THEN("the resulting type will be an double type") {
        REQUIRE(dtype.get_class() == datatype::Class::Float);
        AND_THEN("the resulting double type would be of size 8") {
          REQUIRE(dtype.size() == sizeof(double));
        }
      }
    }
  }
}

SCENARIO("writing and reading data using an ArrayAdapter") {
  size_t buffsize = 7;
  int write_buffer[] = {0, 10, 100, -4, 3, 20, 43};
  auto write_adapter = ArrayAdapter<int>(write_buffer, buffsize);

  auto file = file::create("ArrayAdapterTest.h5", file::AccessFlags::Truncate);
  auto root = file.root();
  auto space = dataspace::Simple(Dimensions{buffsize});
  auto type = datatype::create<int>();

  GIVEN("given a dataset in the file") {
    auto dataset = node::Dataset(root, "data", type, space);
    THEN("we write the data to the dataset") {
      dataset.write(write_adapter);
      AND_WHEN("given a read buffer of appropriate size") {
        auto read_buffer = new int[buffsize];
        THEN("we can create a new array adapter to the read buffer") {
          auto read_adapter = ArrayAdapter<int>(read_buffer, buffsize);
          AND_THEN("we can read the data back to the read buffer") {
            dataset.read(read_adapter);
            for (size_t index = 0; index < buffsize; index++)
              REQUIRE(write_buffer[index] == read_buffer[index]);
          }
        }
      }
    }
    THEN("we do multiple writes to the dataset") {
      size_t b_size_2 = 3;
      double w_buffer_2[] = {3.14, 1.2345, 5.4321};
      auto another_dataset = node::Dataset(root, "data2", datatype::create<double>(), dataspace::Simple(Dimensions{b_size_2 + 1}));
      auto write_adapter1 = ArrayAdapter<double>(w_buffer_2, 1);
      auto write_adapter2 = ArrayAdapter<double>(w_buffer_2, b_size_2);
      dataset.write(write_adapter1, hdf5::dataspace::Hyperslab{{0}, {1}});
      dataset.write(write_adapter2, hdf5::dataspace::Hyperslab{{1}, {b_size_2}});
    }
  }
  GIVEN("an attribute in the file") { 
    auto attribute = root.attributes.create("data", type, space);
    THEN("we can write the data to the attribute") { 
      attribute.write(write_adapter); 
      AND_WHEN("we are provided with a read buffer of appropriate size") { 
        auto read_buffer  = new int[buffsize];
        THEN("we can create a new array adapter to the read buffer") {
          auto read_adapter = ArrayAdapter<int>(read_buffer, buffsize);
          AND_THEN("we can read the data back to the read buffer") {
            attribute.read(read_adapter);
            for (size_t index = 0; index < buffsize; index++)
              REQUIRE(write_buffer[index] == read_buffer[index]);
          }
        }
      }
    }
  }
}

/*


TEST_F(ArrayAdapterTest, attribute_io) {
  file::File file =
      file::create("ArrayAdapterTest.h5", file::AccessFlags::Truncate);
  node::Group root = file.root();
  attribute::Attribute attribute = root.attributes.create(
      "iattr", datatype::create<int>(), dataspace::Simple(Dimensions{bufsize}));
  attribute.write(IntegerArrayAdapter(integer_data, bufsize));

  int read_data[bufsize];
  IntegerArrayAdapter adapter(read_data, bufsize);
  attribute.read(adapter);
  EXPECT_EQ(read_data[0], 0);
  EXPECT_EQ(read_data[1], 1);
  EXPECT_EQ(read_data[2], 2);
  EXPECT_EQ(read_data[3], 3);
  EXPECT_EQ(read_data[4], 4);
  EXPECT_EQ(read_data[5], 5);
  EXPECT_EQ(read_data[6], 6);
}
*/
