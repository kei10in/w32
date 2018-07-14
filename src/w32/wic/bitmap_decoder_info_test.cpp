#include <catch/catch.hpp>

#include <vector>

#include "bitmap_decoder_info.hpp"
#include "imaging_factory.hpp"

namespace w32::wic {
namespace {

using Catch::Matchers::Equals;

TEST_CASE("w32::bitmap_decoder_info") {
  imaging_factory f;

  bitmap_decoder decoder = f.create_decoder_from_filename(
      "./test_data/image1.png", nullptr, generic_access_right::read,
      decode_options::cache_on_load);
  bitmap_decoder_info info = decoder.get_decoder_info();

  SECTION("get_patterns") {
    bitmap_patterns_collection patterns = info.get_patterns();

    REQUIRE(patterns.size() == 1);

    bitmap_pattern const& pattern = patterns[0];

    REQUIRE(pattern.position() == 0);
    REQUIRE(pattern.length() == 8);

    std::vector<std::byte> actual_pattern{pattern.pattern(),
                                          pattern.pattern() + pattern.length()};
    std::vector<std::byte> expected_pattern{
        std::byte{0x89}, std::byte{0x50}, std::byte{0x4E}, std::byte{0x47},
        std::byte{0x0D}, std::byte{0x0A}, std::byte{0x1A}, std::byte{0x0A}};

    REQUIRE(actual_pattern == expected_pattern);

    std::vector<std::byte> actual_mask{pattern.mask(),
                                       pattern.mask() + pattern.length()};
    std::vector<std::byte> expected_mask{
        std::byte{0xFF}, std::byte{0xFF}, std::byte{0xFF}, std::byte{0xFF},
        std::byte{0xFF}, std::byte{0xFF}, std::byte{0xFF}, std::byte{0xFF}};

    REQUIRE(actual_pattern == expected_pattern);

    REQUIRE(pattern.end_of_stream() == false);
  }

  SECTION("matches_pattern") {
    stream s = f.create_stream();
    s.initialize_from_filename("./test_data/image1.png",
                               generic_access_right::read);
    REQUIRE(info.matches_pattern(s) == true);
  }

  SECTION("create_instance") {
    bitmap_decoder bd = info.create_instance();
    REQUIRE(bd.get() != nullptr);
  }
}

}  // namespace
}  // namespace w32::wic
