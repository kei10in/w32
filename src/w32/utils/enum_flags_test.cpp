#include <catch/catch.hpp>

#include "enum_flags.hpp"

namespace {
enum class test_enum : int {
  v1 = 0b01,
  v2 = 0b10,
};

W32_DEFINE_ENUM_FLAG_OPERATORS(test_enum)

TEST_CASE("W32_DEFINE_ENUM_FLAG_OPERATORS") {
  test_enum v = test_enum::v1;

  SECTION("operator|") {
    test_enum actual = v | test_enum::v2;
    REQUIRE(static_cast<int>(actual) == 0b11);
  }

  SECTION("operator&") {
    test_enum actual = v & test_enum::v1;
    REQUIRE(static_cast<int>(actual) == 0b01);
  }

  SECTION("operator^") {
    test_enum actual = v ^ test_enum::v1;
    REQUIRE(static_cast<int>(actual) == 0b00);
  }

  SECTION("operator|=") {
    v |= test_enum::v2;
    REQUIRE(static_cast<int>(v) == 0b11);
  }

  SECTION("operator&=") {
    v &= test_enum::v1;
    REQUIRE(static_cast<int>(v) == 0b01);
  }

  SECTION("operator^=") {
    v ^= test_enum::v1;
    REQUIRE(static_cast<int>(v) == 0b00);
  }

  SECTION("operator~") {
    test_enum actual = ~v;
    REQUIRE(static_cast<int>(actual) == 0xFFFFFFFE);
  }
}  // namespace

}  // namespace
