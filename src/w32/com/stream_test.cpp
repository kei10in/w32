#include "stream.hpp"

#include <catch/catch.hpp>

#include "../shell.hpp"

namespace w32::com {

namespace {

TEST_CASE("stream") {
  stream s = w32::shell::create_memory_stream();
  REQUIRE(s.get_size() == 0);

  SECTION("write bytes") {
    byte bytes[] = {0, 1, 2, 3, 4};
    s.write(bytes, sizeof(bytes));

    REQUIRE(s.get_size() == 5);

    SECTION("move seek position") {
      s.seek(0, stream_seek::set);

      SECTION("read from new seek position") {
        byte read[5] = {};
        s.read(read, sizeof(read));

        REQUIRE(read[0] == 0);
        REQUIRE(read[1] == 1);
        REQUIRE(read[2] == 2);
        REQUIRE(read[3] == 3);
        REQUIRE(read[4] == 4);
      }
    }
  }

  SECTION("modify size") {
    s.set_size(10);
    REQUIRE(s.get_size() == 10);
  }
}

}  // unnamed namespace

}  // namespace w32
