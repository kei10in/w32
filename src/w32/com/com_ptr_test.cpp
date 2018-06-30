#include <catch/catch.hpp>

#include <Shlwapi.h>

#include "com_ptr.hpp"

namespace w32::com {

namespace {

TEST_CASE("w32::com::com_ptr<T>") {
  SECTION("copy construct and assign") {
    com_ptr<IStream> s = SHCreateMemStream(nullptr, 0);
    REQUIRE(s.get() != nullptr);

    SECTION("copy construct") {
      com_ptr<IStream> ss{s};
      REQUIRE(ss.get() == s.get());
      REQUIRE(s.get() != nullptr);
    }

    SECTION("copy assign") {
      com_ptr<IStream> ss;
      ss = s;
      REQUIRE(ss.get() == s.get());
      REQUIRE(s.get() != nullptr);
    }

    SECTION("move construct") {
      com_ptr<IStream> ss{std::move(s)};
      REQUIRE(ss.get() != s.get());
      REQUIRE(s.get() == nullptr);
    }

    SECTION("move assign") {
      com_ptr<IStream> ss;
      ss = std::move(s);
      REQUIRE(ss.get() != s.get());
      REQUIRE(s.get() == nullptr);
    }
  }

  SECTION("from com_ptr of subclass") {
    com_ptr<IStream> s = SHCreateMemStream(nullptr, 0);
    REQUIRE(s.get() != nullptr);

    SECTION("copy construct") {
      com_ptr<ISequentialStream> ss{s};
      REQUIRE(ss.get() == s.get());
      REQUIRE(s.get() != nullptr);
    }

    SECTION("copy assign") {
      com_ptr<ISequentialStream> ss;
      ss = s;
      REQUIRE(ss.get() == s.get());
      REQUIRE(s.get() != nullptr);
    }

    SECTION("move construct") {
      com_ptr<ISequentialStream> ss{std::move(s)};
      REQUIRE(ss.get() != s.get());
      REQUIRE(s.get() == nullptr);
    }

    SECTION("move assign") {
      com_ptr<ISequentialStream> ss;
      ss = std::move(s);
      REQUIRE(ss.get() != s.get());
      REQUIRE(s.get() == nullptr);
    }
  }

  SECTION("from raw pointer of subclass") {
    IStream* p = nullptr;

    SECTION("construct") {
      com_ptr<ISequentialStream> ss{p};
      REQUIRE(ss.get() == p);
    }

    SECTION("assign") {
      com_ptr<ISequentialStream> ss;
      ss = p;
      REQUIRE(ss.get() == p);
    }
  }
}

}  // unnamed namespace

}  // namespace w32::com
