#include <catch/catch.hpp>

#include "bitmap_encoder.hpp"
#include "imaging_factory.hpp"

namespace w32::wic {
namespace {

TEST_CASE("w32::wic::bitmap_encoder") {
  imaging_factory f;

  bitmap_encoder encoder = f.create_encoder(container_format_png, nullptr);

  SECTION("initialize") {
    stream s = f.create_stream();
    s.initialize_from_filename("./test_data/output.png",
                               generic_access_right::read_write);

    REQUIRE_NOTHROW(
        encoder.initialize(s, bitmap_encoder_cache_option::no_cache));

    SECTION("get_container_format") {
      container_format_id container_format = encoder.get_container_format();
      REQUIRE(container_format == container_format_png);
    }

    SECTION("get_encoder_info") {
      bitmap_encoder_info encoder_info = encoder.get_encoder_info();
      REQUIRE(encoder_info.get() != nullptr);
    }

    SECTION("set_color_contexts") {
      REQUIRE_THROWS(encoder.set_color_contexts(0, nullptr));
    }

    SECTION("set_palette") {
      palette p = f.create_palette();
      p.initialize_predefined(bitmap_palette_type::fixed_black_white, false);
      REQUIRE_THROWS(encoder.set_palette(p));
    }

    SECTION("set_thumbnail") {
      bitmap bmp = f.create_bitmap(1, 2, pixel_format_8bpp_gray,
                                   bitmap_create_cache_option::cache_on_load);
      REQUIRE_THROWS(encoder.set_thumbnail(bmp));
    }

    SECTION("set_preview") {
      bitmap bmp = f.create_bitmap(1, 2, pixel_format_8bpp_gray,
                                   bitmap_create_cache_option::cache_on_load);
      REQUIRE_THROWS(encoder.set_preview(bmp));
    }

    SECTION("create_new_frame") {
      bitmap_frame_encode frame_encode = encoder.create_new_frame(nullptr);
      REQUIRE(frame_encode.get() != nullptr);
    }

    SECTION("commit") {
      // No frame commit is invalid.
      REQUIRE_THROWS(encoder.commit());
    }

    SECTION("get_metadata_query_writer") {
      // The png encoder is not support metadata query writer.
      REQUIRE_THROWS(encoder.get_metadata_query_writer());
    }
  }
}

TEST_CASE("w32::wic::bitmap_encoder_info") {
  imaging_factory f;

  bitmap_encoder encoder = f.create_encoder(container_format_png, nullptr);
  bitmap_encoder_info encoder_info = encoder.get_encoder_info();
  REQUIRE(encoder_info.get() != nullptr);

  SECTION("create_instance") {
    bitmap_encoder be = encoder_info.create_instance();
    REQUIRE(be.get() != nullptr);
  }
}

}  // namespace
}  // namespace w32::wic
