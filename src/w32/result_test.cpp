#include <catch/catch.hpp>

#include "result.hpp"

namespace w32 {

namespace {

TEST_CASE("result type test") {
  SECTION("ok") {
    result<int, int> r = ok(10);

    REQUIRE(r.is_ok() == true);
    REQUIRE(r.is_err() == false);

    REQUIRE_NOTHROW(r.ok());
    REQUIRE_THROWS(r.err());
  }

  SECTION("err") {
    result<int, int> r = err(10);

    REQUIRE(r.is_ok() == false);
    REQUIRE(r.is_err() == true);

    REQUIRE_THROWS(r.ok());
    REQUIRE_NOTHROW(r.err());
  }
}

}  // unnamed namespace

}  // namespace w32
