//
// (c) Copyright 2017 DESY,ESS
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
// Author: Martin Shetty <martin.shetty@esss.se>
// Created on: May 4, 2018
//

#include <catch2/catch.hpp>
#include <h5cpp/file/functions.hpp>
#include <h5cpp/hdf5.hpp>
#include <h5cpp/node/group.hpp>

using namespace hdf5;

SCENARIO("Construction of a memory driver instance", "[file,h5cpp,driver]") {
  GIVEN("a default constructed instance") {
    file::MemoryDriver m;
    THEN("all parameters should have their default values") {
      REQUIRE(m.id() == file::DriverID::Memory);
      REQUIRE_FALSE(m.backing_store());
      REQUIRE(m.increment() == 1024ul * 1024ul);
    }

    WHEN("setting the backing store") {
      m.backing_store(true);
      THEN("the backing store should return true") {
        REQUIRE(m.backing_store());
      }
    }

    WHEN("setting the increment") {
      m.increment(5000);
      THEN("the appropriate value should also be returned") {
        REQUIRE(m.increment() == 5000ul);
      }
    }
  }

  GIVEN("A driver constructed with the standard constructor") {
    file::MemoryDriver m(7000, true);
    THEN("we would expect an active backing store and an increment") {
      REQUIRE(m.backing_store());
      REQUIRE(m.increment() == 7000ul);
    }
  }
}

SCENARIO("Applying the memory driver") {
  file::MemoryDriver m(7000, true);
  GIVEN("a valid file access list") {
    property::FileAccessList fapl;
    THEN("a file can be constructed") {
      property::FileCreationList fcpl;
      m(fapl);
      file::create("memory_file.h5", file::AccessFlags::Truncate, fcpl, fapl);
    }
  }

  GIVEN("a closed file access list") {
    property::FileAccessList fapl;
    ObjectHandle(static_cast<hid_t>(fapl)).close();
    THEN("the application of the drvier will fail") {
      REQUIRE_THROWS_AS(m(fapl), std::runtime_error);
    }
  }
}

TEST_CASE("Default construction of drivers"){
#ifdef H5_HAVE_DIRECT
    SECTION("the direct driver"){file::DirectDriver m;
REQUIRE(m.id() == file::DriverID::Direct);
}
#endif

SECTION("the posix driver") {
  file::PosixDriver m;
  REQUIRE(m.id() == file::DriverID::Posix);
}

#ifdef H5CPP_WITH_MPI

SECTION("the MPI driver") {
  file::MPIDriver m(MPI_COMM_WORLD, MPI_INFO_NULL);
  REQUIRE(m.id() == file::DriverID::MPI);
}

#endif
}

SCENARIO("Applying a POSIX file driver", "[h5cpp, file]") {
  file::PosixDriver m;
  property::FileCreationList fcpl;
  GIVEN("a valid file access property list") {
    property::FileAccessList fapl;
    THEN("the driver can be applied and a new file be created") {
      m(fapl);
      file::create("posix_file.h5", file::AccessFlags::Truncate, fcpl, fapl);
    }
  }

  GIVEN("an invalid file access property list") {
    property::FileAccessList fapl;
    ObjectHandle(static_cast<hid_t>(fapl)).close();
    THEN("applying the driver will fail") {
      REQUIRE_THROWS_AS(m(fapl), std::runtime_error);
    }
  }
}

#ifdef H5CPP_WITH_MPI

SCENARIO("Applying the MPI file driver", "[h5cpp,file]") {
  int flag;
  MPI_Initialized(&flag);
  if (!flag) {
    MPI_Init(nullptr, nullptr);
  }
  property::FileCreationList fcpl;
  file::MPIDriver m(MPI_COMM_WORLD, MPI_INFO_NULL);

  GIVEN("a valid file access property list") {
    property::FileAccessList fapl;
    THEN("the driver can be applied") {
      m(fapl);
      file::create("posix_file.h5", file::AccessFlags::Truncate, fcpl, fapl);
    }
  }

  GIVEN("an invalid file access property list") {
    property::FileAccessList fapl;
    ObjectHandle(static_cast<hid_t>(fapl)).close();
    THEN("applying the driver will fail") {
      REQUIRE_THROWS_AS(m(fapl), std::runtime_error);
    }
  }
}

#endif
