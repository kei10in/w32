#include <catch/catch.hpp>

#include <Shlwapi.h>

#include "unknown.hpp"

namespace w32::com::internal {
namespace {

TEST_CASE("w32::com::unknown_t<T>") {
  SECTION("a") {
    unknown_t<IStream> s = SHCreateMemStream(nullptr, 0);
    com_ptr<IStream> p = SHCreateMemStream(nullptr, 0);
    REQUIRE(s.get() != nullptr);

    SECTION("copy construct") {
      unknown_t<IStream> t{s};
      REQUIRE(s.get() == t.get());
    }

    SECTION("copy assign") {
      unknown_t<IStream> t;
      t = s;
      REQUIRE(s.get() == t.get());
    }

    SECTION("move construct") {
      unknown_t<IStream> t{std::move(s)};
      REQUIRE(s.get() != t.get());
      REQUIRE(s.get() == nullptr);
    }

    SECTION("move assign") {
      unknown_t<IStream> t;
      t = std::move(s);
      REQUIRE(s.get() != t.get());
      REQUIRE(s.get() == nullptr);
    }

    SECTION("construct from pointer") {
      IStream* ps = p.release();
      unknown_t<IStream> t{ps};
      REQUIRE(ps == t.get());
    }

    SECTION("assign pointer") {
      IStream* ps = p.release();
      unknown_t<IStream> t;
      t = ps;
      REQUIRE(ps == t.get());
    }

    SECTION("construct from com_ptr") {
      unknown_t<IStream> t{p};
      REQUIRE(p.get() == t.get());
    }

    SECTION("assign com_ptr") {
      unknown_t<IStream> t;
      t = p;
      REQUIRE(p.get() == t.get());
    }

    SECTION("move construct from com_ptr") {
      unknown_t<IStream> t{std::move(p)};
      REQUIRE(p.get() != t.get());
      REQUIRE(p.get() == nullptr);
    }

    SECTION("move assign com_ptr") {
      unknown_t<IStream> t;
      t = std::move(p);
      REQUIRE(p.get() != t.get());
      REQUIRE(p.get() == nullptr);
    }

    SECTION("copy construct from subclass") {
      unknown_t<ISequentialStream> t{s};
      REQUIRE(s.get() == t.get());
    }

    SECTION("copy assign subclass") {
      unknown_t<ISequentialStream> t;
      t = s;
      REQUIRE(s.get() == t.get());
    }

    SECTION("move construct from subclass") {
      unknown_t<ISequentialStream> t{std::move(s)};
      REQUIRE(s.get() != t.get());
      REQUIRE(s.get() == nullptr);
    }

    SECTION("move assign subclass") {
      unknown_t<ISequentialStream> t;
      t = std::move(s);
      REQUIRE(s.get() != t.get());
      REQUIRE(s.get() == nullptr);
    }

    SECTION("construct from pointer of subclass") {
      IStream* ps = p.release();
      unknown_t<ISequentialStream> t{ps};
      REQUIRE(ps == t.get());
    }

    SECTION("assign pointer of subclass") {
      IStream* ps = p.release();
      unknown_t<ISequentialStream> t;
      t = ps;
      REQUIRE(ps == t.get());
    }

    SECTION("construct from com_ptr of subclass") {
      unknown_t<ISequentialStream> t{p};
      REQUIRE(p.get() == t.get());
    }

    SECTION("assign com_ptr of subclass") {
      unknown_t<ISequentialStream> t;
      t = p;
      REQUIRE(p.get() == t.get());
    }

    SECTION("move construct from com_ptr of subclass") {
      unknown_t<ISequentialStream> t{std::move(p)};
      REQUIRE(p.get() != t.get());
      REQUIRE(p.get() == nullptr);
    }

    SECTION("move assign com_ptr of subclass") {
      unknown_t<ISequentialStream> t;
      t = std::move(p);
      REQUIRE(p.get() != t.get());
      REQUIRE(p.get() == nullptr);
    }
  }
}

}  // unnamed namespace
}  // namespace w32::com
