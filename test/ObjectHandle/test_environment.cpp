//
// (c) Copyright 2017 DESY,ESS
//
// This file is part of h5pp.
//
// h5cpp is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// h5cpp is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  ee the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with h5cpp.  If not, see <http://www.gnu.org/licenses/>.
// ===========================================================================
//
// Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
// Created on: Aug 15, 2017
//

#include "object_handle_test.hpp"


TestEnvironment::TestEnvironment(const std::string &filename):
  file_handle_(H5Fcreate(filename.c_str(),H5F_ACC_TRUNC,H5P_DEFAULT,H5P_DEFAULT))
{

}

void TestEnvironment::close()
{
  file_handle_.close();
}



const hdf5::ObjectHandle &TestEnvironment::file_handle() const
{
  return file_handle_;
}


