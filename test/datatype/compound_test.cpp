
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
// Created on: Oct 6, 2017
//
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE testing compound data type
#include <boost/test/unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>
#include <h5cpp/datatype/compound.hpp>
#include <h5cpp/datatype/float.hpp>
#include <h5cpp/datatype/factory.hpp>
#include <h5cpp/file/file.hpp>
#include <h5cpp/file/functions.hpp>
#include <h5cpp/node/group.hpp>
#include <h5cpp/attribute/attribute.hpp>
#include <cstdint>
#include <complex>
#include <vector>
#include "../examples/rgbpixel.hpp"
#include "../examples/rgbpixel_h5.hpp"

using namespace hdf5;

struct complex_struct
{
  double real;
  double imag;

};

class Pixel
{
  private:
   std::uint8_t red_;
   std::uint8_t green_;
   std::uint8_t blue_;
  public:

};

struct Fixture
{
    hdf5::file::File file;
    hdf5::node::Group root_group;

    Fixture():
      file(hdf5::file::create("CompoundTest.h5",file::AccessFlags::TRUNCATE)),
      root_group(file.root())
    {}
};

namespace hdf5 {
namespace datatype {

template<typename BT>
struct complex_t
{
    BT real;
    BT imag;
};

template<typename T>
class TypeTrait<std::complex<T>>
{
  private:
    using complex_type = complex_t<T>;
  public:
    using TypeClass = Compound;

    static TypeClass create()
    {

      datatype::Compound type(sizeof(complex_struct));
      type.insert("real",HOFFSET(complex_type,real),datatype::create<T>());
      type.insert("imag",HOFFSET(complex_type,imag),datatype::create<T>());

      return type;
    }
};

}
}

BOOST_FIXTURE_TEST_SUITE(CompoundTest,Fixture)

BOOST_AUTO_TEST_CASE(test_default_construction)
{
  datatype::Compound type;
  //BOOST_CHECK_THROW(type.field_index("real"),std::runtime_error);
  //BOOST_CHECK_THROW(type.field_index(0),std::runtime_error);

}

BOOST_AUTO_TEST_CASE(test_complex_number)
{
  datatype::Compound type(sizeof(complex_struct));
  BOOST_CHECK_NO_THROW(type.insert("real",HOFFSET(complex_struct,real),datatype::create<double>()));
  BOOST_CHECK_NO_THROW(type.insert("imag",HOFFSET(complex_struct,imag),datatype::create<double>()));

}

BOOST_AUTO_TEST_CASE(test_complex_number_io)
{
  std::complex<double> write_value(1.,3.);
  std::complex<double> read_value(0.,0.);
  attribute::Attribute a = root_group.attributes.create<std::complex<double>>("hello");
  a.write(write_value);
  a.read(read_value);
  BOOST_CHECK_CLOSE(write_value.real(),read_value.real(),0.0001);
  BOOST_CHECK_CLOSE(write_value.imag(),read_value.imag(),0.0001);

}

BOOST_AUTO_TEST_CASE(test_pixel_type)
{
  RGBPixel write_pixel(1,2,3);
  RGBPixel read_pixel(0,0,0);

  attribute::Attribute a = root_group.attributes.create<RGBPixel>("pixel");
  a.write(write_pixel);
  a.read(read_pixel);

  BOOST_CHECK_EQUAL(write_pixel.red(),read_pixel.red());
  BOOST_CHECK_EQUAL(write_pixel.green(),read_pixel.green());
  BOOST_CHECK_EQUAL(write_pixel.blue(),read_pixel.blue());
}

BOOST_AUTO_TEST_SUITE_END()



