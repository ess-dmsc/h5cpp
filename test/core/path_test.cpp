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
// Authors:
//    Eugen Wintersberger <eugen.wintersberger@desy.de>
//    Martin Shetty <martin.shetty@esss.se>
// Created on: Aug 24, 2017
//
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <h5cpp/core/path.hpp>

using namespace hdf5;

namespace { 
static std::string to_string(const Path& p) {
  return static_cast<std::string>(p);
}
}

SCENARIO("Path construction", "[h5cpp, path]") {
  WHEN("default constructed") {
    Path p;
    THEN("we get") {
      REQUIRE(p.size() == 0);
      REQUIRE_FALSE(p.absolute());
    }
  }

  WHEN("constructed from a string") {
    GIVEN("/hello/world/data") {
      Path p("/hello/world/data");
      THEN("we") {
        REQUIRE(p.size() == 3ul);
        REQUIRE(p.absolute());
        REQUIRE_FALSE(p.is_root());
      }
    }

    GIVEN("hello/world") {
      Path p("hello/world");
      THEN("we") {
        REQUIRE(p.size() == 2ul);
        REQUIRE_FALSE(p.absolute());
        REQUIRE_FALSE(p.is_root());
      }
    }

    GIVEN("hello/world/instrument/data/") {
      Path p("hello/world/instrument/data/");
      THEN("we") {
        REQUIRE(p.size() == 4ul);
        REQUIRE_FALSE(p.absolute());
        REQUIRE_FALSE(p.is_root());
      }
    }

    GIVEN(".") {
      Path p(".");
      THEN("we") {
        REQUIRE(p.size() == 0ul);
        REQUIRE_FALSE(p.absolute());
        REQUIRE_FALSE(p.is_root());
      }
    }

    GIVEN("./") {
      Path p("./");
      THEN("we") {
        REQUIRE(p.size() == 0ul);
        REQUIRE_FALSE(p.absolute());
        REQUIRE_FALSE(p.is_root());
      }
    }

    GIVEN("/.") {
      Path p("/.");
      THEN("we") {
        REQUIRE(p.size() == 0ul);
        REQUIRE(p.absolute());
        REQUIRE(p.is_root());
      }
    }

    GIVEN("/") {
      Path p("/");
      THEN("we") {
        REQUIRE(p.size() == 0ul);
        REQUIRE(p.absolute());
        REQUIRE(p.is_root());
      }
    }

    GIVEN(".///") {
      Path p(".///");
      THEN("we") {
        REQUIRE(p.size() == 0ul);
        REQUIRE_FALSE(p.absolute());
        REQUIRE_FALSE(p.is_root());
      }
    }
  }
}

SCENARIO("path to string conversion") {
  WHEN("using static_cast<std::string>") {
    GIVEN("constructed from /hello/world/data") {
      Path p("/hello/world/data");
      THEN("we") { REQUIRE(to_string(p) == "/hello/world/data"); }
    }

    GIVEN("path is hello/world") {
      Path p("hello/world");
      THEN("we") { REQUIRE(to_string(p) == "hello/world"); }
    }

    GIVEN("path is hello/world/instrument/data/") {
      Path p("hello/world/instrument/data/");
      THEN("we") { REQUIRE(to_string(p) == "hello/world/instrument/data"); }
    }

    GIVEN("path is .") {
      Path p(".");
      THEN("we") { REQUIRE(to_string(p) == "."); }
    }

    GIVEN("path is empty") {
      Path p("");
      THEN("we") { REQUIRE(to_string(p) == "."); }
    }
  }

  WHEN("sanatizing the input path") {
    GIVEN("a path with ./hello") {
      Path p("./hello");
      THEN("we") { REQUIRE(to_string(p) == "hello"); }
    }

    GIVEN("a path hello/world/.") {
      Path p("hello/world/.");
      THEN("we") { REQUIRE(to_string(p) == "hello/world"); }
    }

    GIVEN("a path reading hello/./world") {
      Path p("hello/./world");
      THEN("we") { REQUIRE(to_string(p) == "hello/world"); }
    }

    GIVEN("a path hello///world") {
      Path p("hello///world");
      THEN("we") { REQUIRE(to_string(p) == "hello/world"); }
    }
  }
}

SCENARIO("Determining the common path base", "[h5cpp, path]") {
  GIVEN("a relative path ab/b/c") {
    Path p1("a/b/c");

    WHEN("second path is a/b/z/") {
      auto common = common_base(p1, Path("a/b/z"));
      THEN("the common part is a/b") { REQUIRE(to_string(common) == "a/b"); }
    }

    WHEN("second path is a/b/c") {
      auto common = common_base(p1, Path("a/b/c"));
      THEN("the common part is a/b/c") {
        REQUIRE(to_string(common) == "a/b/c");
      }
    }

    WHEN("second path is .") {
      auto common = common_base(p1, Path("."));
      THEN("the common part is .") { REQUIRE(to_string(common) == "."); }
    }
  }

  GIVEN("an absolute path /a/b/c") {
    Path p1("/a/b/c");
    WHEN("second path is /a/b/z") {
      auto common = common_base(p1, Path("/a/b/z"));
      THEN("the common part is /a/b") { REQUIRE(to_string(common) == "/a/b"); }
    }

    WHEN("second path is /a/b/c") {
      auto common = common_base(p1, Path("/a/b/c"));
      THEN("the common part is /a/b/c") {
        REQUIRE(to_string(common) == "/a/b/c");
      }
    }

    WHEN("second path is /a/b/c") {
      auto common = common_base(p1, Path("/x/y"));
      THEN("the common part is /") { REQUIRE(to_string(common) == "/"); }
    }

    WHEN("second path is d/e") {
      THEN("an exception will be thrown") {
        REQUIRE_THROWS_AS(common_base(p1, Path("d/e")), std::runtime_error);
      }
    }
  }
}

TEST_CASE("test relative_to") {
  SECTION("a/b/c with a/b") {
    auto p = Path("a/b/c").relative_to(Path("a/b"));
    REQUIRE(to_string(p) == "c");
  }

  SECTION("/a/b/c with /a/b") {
    auto p = Path("/a/b/c").relative_to(Path("/a/b"));
    REQUIRE(to_string(p) == "c");
  }

  SECTION("/a/b with  /") {
    auto p = Path("/a/b").relative_to(Path("/"));
    REQUIRE(to_string(p) == "a/b");
  }

  SECTION("/ with /") {
    auto p = Path("/").relative_to(Path("/"));
    REQUIRE(to_string(p) == ".");
  }

  REQUIRE_THROWS_AS(Path("c/d").relative_to(Path("/a/b")), std::runtime_error);

  REQUIRE_THROWS_AS(Path("a/b").relative_to(Path("a/b/c")), std::runtime_error);

  REQUIRE_THROWS_AS(Path("/a/b/c").relative_to(Path("a/b")),
                    std::runtime_error);

  REQUIRE_THROWS_AS(Path("/a/b/c").relative_to(Path("/x/y/z")),
                    std::runtime_error);
}

SCENARIO("inplace append") {
  GIVEN("/entry/instrument") {
    Path p("/entry/instrument");
    WHEN("appended detector/data") {
      p.append(Path("detector/data"));
      THEN("/entry/instrument/detector/data") {
        REQUIRE(to_string(p) == "/entry/instrument/detector/data");
      }
    }
  }
}

SCENARIO("appending with + operator") {
  GIVEN("/entry/instrument/detector") {
    Path p("/entry/instrument/detector");
    WHEN("p+\"data\"") {
      p = p + "data";
      THEN("/entry/instrument/detector/data") {
        REQUIRE(to_string(p) == "/entry/instrument/detector/data");
        REQUIRE(p.size() == 4ul);
        REQUIRE(p.absolute());
      }
    }
  }

  GIVEN("instrument/detector") {
    Path p("instrument/detector");
    WHEN("p + \"metadata/data\"") {
      p = p + "metadata/date";
      THEN("instrument/detector/metdata/date") {
        REQUIRE(to_string(p) == "instrument/detector/metadata/date");
        REQUIRE(p.size() == 4ul);
        REQUIRE_FALSE(p.absolute());
      }
    }
  }
}

SCENARIO("prepending names") {
  GIVEN("instrument/detector") {
    Path p("instrument/detector");
    WHEN("\"/entry\" + p") {
      p = "/entry" + p;
      THEN("/entry/instrument/detector") {
        REQUIRE(to_string(p) == "/entry/instrument/detector");
        REQUIRE(p.absolute());
      }
    }
  }

  GIVEN("detect/data") {
    Path p("detector/data");
    WHEN("\"entry/instrument\" + p") {
      p = "/entry/instrument/" + p;
      THEN("/entry/instrument/detector/data") {
        REQUIRE(to_string(p) == "/entry/instrument/detector/data");
        REQUIRE(p.absolute());
      }
    }
  }

  GIVEN("entry/instrument") {
    Path p("entry/instrument");
    WHEN("\"/\"+p") {
      p = "/" + p;
      THEN("/entry/instrument") {
        REQUIRE(p.size() == 2ul);
        REQUIRE(p.absolute());
      }
    }
  }
}

TEST_CASE("adding two paths", "[h5cpp,file]") {
  Path p1("/entry/instrument"), p2("detector/data");
  SECTION("addition with infix operator") {
    auto p = p1 + p2;
    REQUIRE(p.size() == 4ul);
    REQUIRE(p.absolute());
    REQUIRE(to_string(p) == "/entry/instrument/detector/data");
  }

  SECTION("using the increment assignment") {
    auto p = p1 + p2;
    p += Path("item");
    REQUIRE(to_string(p) == "/entry/instrument/detector/data/item");
  }
}

SCENARIO("testing the root path") {
  GIVEN("/") {
    Path p("/");
    REQUIRE(p.is_root());
    REQUIRE(p.absolute());
    REQUIRE(to_string(p) == "/");
  }
}

SCENARIO("Using the reverse path iterator") {
  GIVEN("a path") {
    Path p("/hello/world");
    WHEN("creating an iterator") {
      auto ri = p.rbegin();
      THEN("last element") { REQUIRE(*ri == "world"); }
      ++ri;
      THEN("first element") { REQUIRE(*ri == "hello"); }
      ++ri;
      THEN("at the end") { REQUIRE(ri == p.rend()); }
    }
  }
}

SCENARIO("the last element of a path is the name", "[h5cpp]") {
  GIVEN("hello/world") {
    Path p("hello/world");
    THEN("the name is world") {
      REQUIRE(p.name() == "world");
      REQUIRE_FALSE(p.is_name());
    }
  }

  GIVEN("/") {
    Path p("/");
    THEN("the path references the root") { REQUIRE(p.is_root()); }
    THEN("the name is .") { REQUIRE(p.name() == "."); }
    THEN("the path is not only a name") { REQUIRE_FALSE(p.is_name()); }
  }

  GIVEN("/temperature") {
    Path p("/temperature");
    THEN("the name is temperature") { REQUIRE(p.name() == "temperature"); }
    THEN("the path is not only a name") { REQUIRE_FALSE(p.is_name()); }
  }

  GIVEN("name") {
    Path p("name");
    THEN("the name is name") { REQUIRE(p.name() == "name"); }
    THEN("the path is merely a name") { REQUIRE(p.is_name()); }
  }
}

SCENARIO("everything but the name is the parent of a path", "[h5cpp]") {
  GIVEN("hello/world") {
    Path p("hello/world");
    THEN("hello is the parent") { REQUIRE(to_string(p.parent()) == "hello"); }
  }

  GIVEN("/hello/world") {
    Path p("/hello/world");
    THEN("/hello is the parent") { REQUIRE(to_string(p.parent()) == "/hello"); }
  }

  GIVEN("/") {
    Path p("/");
    THEN("the path references the root node") { REQUIRE(p.is_root()); }
    AND_THEN("the parent is /") { REQUIRE(to_string(p.parent()) == "/"); }
  }
}

SCENARIO("test equality") {
  Path p1("hello/world");
  Path p2("/hello/world");
  Path p3("/hello");
  THEN("hello/world == hello/world") { REQUIRE(p1 == p1); }
  THEN("hello/world != /hello/world") { REQUIRE(p1 != p2); }
  THEN("hello/world != /hello") { REQUIRE(p2 != p3); }
}
