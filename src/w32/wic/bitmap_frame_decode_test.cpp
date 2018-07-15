#include <catch/catch.hpp>

#include "bitmap_frame_decode.hpp"
#include "imaging_factory.hpp"

namespace w32::wic {
namespace {

TEST_CASE("w32::wic::bitmap_frame_decode") {
  imaging_factory f;

  bitmap_decoder decoder = f.create_decoder_from_filename(
      "./test_data/image1.png", nullptr, generic_access_right::read,
      decode_options::cache_on_load);

  bitmap_frame_decode frame_decoder = decoder.get_frame(0);

  SECTION("get_metadata_query_reader") {
    metadata_query_reader query_reader =
        frame_decoder.get_metadata_query_reader();
    REQUIRE(query_reader.get() != nullptr);
  }

  SECTION("get_color_contexts") {
    std::vector<color_context> color_contexts =
        frame_decoder.get_color_contexts();
    REQUIRE(color_contexts.size() == 0);
  }

  SECTION("get_thumbnail") {
    // The png decoder does not support the thumbnail.
    REQUIRE_THROWS(frame_decoder.get_thumbnail());
  }
}

}  // namespace
}  // namespace w32::wic
