#include <catch/catch.hpp>

#include <vector>

#include "bitmap_decoder_info.hpp"
#include "imaging_factory.hpp"

namespace w32::wic {
namespace {

using Catch::Matchers::Equals;

TEST_CASE("w32::bitmap_codec_info") {
  imaging_factory f;

  bitmap_decoder decoder = f.create_decoder_from_filename(
      "./test_data/image1.png", nullptr, generic_access_right::read,
      decode_options::cache_on_load);
  bitmap_codec_info info = decoder.get_decoder_info();

  SECTION("get_pixel_formats") {
    std::vector<pixel_format_id> pixel_formats = info.get_pixel_formats();
    REQUIRE(pixel_formats.size() == 13);
  }

  SECTION("get_color_management_version") {
    std::wstring version = info.get_color_management_version();
    REQUIRE(version == L"1.0.0.0");
  }

  SECTION("get_device_manufacturer") {
    std::wstring device_manufacturer = info.get_device_manufacturer();
    REQUIRE(device_manufacturer == L"");
  }

  SECTION("get_device_models") {
    std::wstring device_models = info.get_device_models();
    REQUIRE(device_models == L"");
  }

  SECTION("get_mime_types") {
    std::wstring mime_types = info.get_mime_types();
    REQUIRE(mime_types == L"image/png");
  }

  SECTION("get_file_extensions") {
    std::wstring file_extensions = info.get_file_extensions();
    REQUIRE(file_extensions == L".png");
  }

  SECTION("does_support_animation") {
    bool v = info.does_support_animation();
    REQUIRE(v == false);
  }

  SECTION("does_support_chromakey") {
    bool v = info.does_support_chromakey();
    REQUIRE(v == true);
  }

  SECTION("does_support_lossless") {
    bool v = info.does_support_lossless();
    REQUIRE(v == true);
  }

  SECTION("does_support_multiframe") {
    bool v = info.does_support_multiframe();
    REQUIRE(v == false);
  }

  SECTION("matches_mime_type") {
    REQUIRE_THROWS(info.matches_mime_type(L"images/png"));
  }
}

}  // namespace
}  // namespace w32::wic
