
#ifdef H5CPP_CATCH2_V2
#include <catch2/catch.hpp>
#else
#include <catch2/catch_all.hpp>
#endif
#include <h5cpp/hdf5.hpp>

using namespace hdf5;

SCENARIO("testing reading of fixed-size string attributes")
{
  auto h5py_file = file::open("../h5py_test_string_attributes.h5", file::AccessFlags::ReadOnly);
  auto root_group = h5py_file.root();

  SECTION("null-terminated string attribute of size 4")
  {
    SECTION("written string was empty")
    {
      auto attribute = root_group.attributes["fixed_size_string_nullterm_empty"];
      WHEN("reading back the value into a std::string")
      {
        std::string value;
        attribute.read(value);
        THEN("the std::string should be empty (i.e., contain \"\", without trailing \\0)")
        {
          REQUIRE(value == "");
        }
      }
    }
    SECTION("written string was \"1\"")
    {
      auto attribute = root_group.attributes["fixed_size_string_nullterm_part"];
      WHEN("reading back the value into a std::string")
      {
        std::string value;
        attribute.read(value);
        THEN("the std::string should contain the string '1' (without trailing \\0)")
        {
          REQUIRE(value == "1");
        }
      }
    }
    SECTION("written string was \"123\"")
    {
      auto attribute = root_group.attributes["fixed_size_string_nullterm_full"];
      WHEN("reading back the value into a std::string")
      {
        std::string value;
        attribute.read(value);
        THEN("the std::string should contain the entire string '123' (without trailing \\0)")
        {
          REQUIRE(value == "123");
        }
      }
    }
    SECTION("written string was \"1234\"")
    {
      auto attribute = root_group.attributes["fixed_size_string_nullterm_trunc"];
      WHEN("reading back the value into a std::string")
      {
        std::string value;
        attribute.read(value);
        THEN("the std::string should contain the truncated string '123' (without trailing \\0)")
        {
          REQUIRE(value == "123");
        }
      }
    }
  }
  SECTION("null-padded string attribute of size 4")
  {
    SECTION("written string was empty")
    {
      auto attribute = root_group.attributes["fixed_size_string_nullpad_empty"];
      WHEN("reading back the value into a std::string")
      {
        std::string value;
        attribute.read(value);
        THEN("the std::string should be empty (i.e., contain \"\", without any \\0-padding)")
        {
          REQUIRE(value == "");
        }
      }
    }
    SECTION("written string was \"1\"")
    {
      auto attribute = root_group.attributes["fixed_size_string_nullpad_part"];
      WHEN("reading back the value into a std::string")
      {
        std::string value;
        attribute.read(value);
        THEN("the std::string should contain the string '1' (without any \\0-padding)")
        {
          REQUIRE(value == "1");
        }
      }
    }
    SECTION("written string was \"1234\"")
    {
      auto attribute = root_group.attributes["fixed_size_string_nullpad_full"];
      WHEN("reading back the value into a std::string")
      {
        std::string value;
        attribute.read(value);
        THEN("the std::string should contain the entire string '1234' (without any \\0-padding)")
        {
          REQUIRE(value == "1234");
        }
      }
    }
    SECTION("written string was \"12345\"")
    {
      auto attribute = root_group.attributes["fixed_size_string_nullpad_trunc"];
      WHEN("reading back the value into a std::string")
      {
        std::string value;
        attribute.read(value);
        THEN("the std::string should contain the truncated string '1234' (without any \\0-padding)")
        {
          REQUIRE(value == "1234");
        }
      }
    }
  }
  SECTION("space-padded string attribute of size 4")
  {
    SECTION("written string was empty")
    {
      auto attribute = root_group.attributes["fixed_size_string_spacepad_empty"];
      WHEN("reading back the value into a std::string")
      {
        std::string value;
        attribute.read(value);
        THEN("the std::string should be empty (i.e., contain \"\", without any space-padding)")
        {
          REQUIRE(value == "");
        }
      }
    }
    SECTION("written string was \"1\"")
    {
      auto attribute = root_group.attributes["fixed_size_string_spacepad_part"];
      WHEN("reading back the value into a std::string")
      {
        std::string value;
        attribute.read(value);
        THEN("the std::string should contain the string '1' (without any space-padding)")
        {
          REQUIRE(value == "1");
        }
      }
    }
    SECTION("written string was \"1234\"")
    {
      auto attribute = root_group.attributes["fixed_size_string_spacepad_full"];
      WHEN("reading back the value into a std::string")
      {
        std::string value;
        attribute.read(value);
        THEN("the std::string should contain the entire string '1234' (without any space-padding)")
        {
          REQUIRE(value == "1234");
        }
      }
    }
    SECTION("written string was \"12345\"")
    {
      auto attribute = root_group.attributes["fixed_size_string_spacepad_trunc"];
      WHEN("reading back the value into a std::string")
      {
        std::string value;
        attribute.read(value);
        THEN("the std::string should contain the truncated string '1234' (without any space-padding)")
        {
          REQUIRE(value == "1234");
        }
      }
    }
  }
}