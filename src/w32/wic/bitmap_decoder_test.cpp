#include <catch/catch.hpp>

#include <array>

#include "../shell.hpp"
#include "bitmap_decoder.hpp"
#include "imaging_factory.hpp"

namespace w32::wic {
namespace {

TEST_CASE("w32::wic::bitmap_decodr") {
  imaging_factory f;

  bitmap_decoder decoder = f.create_decoder(container_format_png, nullptr);
  auto png_stream = f.create_stream();
  png_stream.initialize_from_filename("./test_data/image1.png",
                                      generic_access_right::read);

  SECTION("query_capability") {
    bitmap_decoder_capabilities caps = decoder.query_capability(png_stream);
    REQUIRE(static_cast<bool>(
        caps & bitmap_decoder_capabilities::can_decode_all_images));
    REQUIRE(static_cast<bool>(
        caps & bitmap_decoder_capabilities::can_enumerate_metadata));
  }

  SECTION("initialize") {
    decoder.initialize(png_stream, decode_options::cache_on_demand);

    SECTION("get_container_format") {
      container_format_id container_format = decoder.get_container_format();
      REQUIRE(container_format == container_format_png);
    }

    SECTION("get_decoder_info") {
      bitmap_decoder_info decoder_info = decoder.get_decoder_info();
      REQUIRE(decoder_info.get() != nullptr);
    }

    SECTION("copy_palette") {
      palette p = f.create_palette();
      // The test image file is the 32 bpp image.
      REQUIRE_THROWS(decoder.copy_palette(p));
    }

    SECTION("get_meatadata_query_reader") {
      // The png decoder does not support container-level metadata.
      REQUIRE_THROWS(decoder.get_metadata_query_reader());
    }

    SECTION("get_preview") {
      // The png decoder does not support preview.
      REQUIRE_THROWS(decoder.get_preview());
    }

    SECTION("get_color_contexts") {
      std::array<color_context, 5> contexts;
      // The png decoder does not support color context.
      REQUIRE_THROWS(
          decoder.get_color_contexts(contexts.size(), contexts.data()));
    }

    SECTION("get_thumbnail") {
      // The png decoder does not support thumbnail.
      REQUIRE_THROWS(decoder.get_thumbnail());
    }

    SECTION("get_frame_count") {
      std::size_t count = decoder.get_frame_count();
      REQUIRE(count == 1);
    }

    SECTION("get_frame") {
      bitmap_frame_decode frame_decoder = decoder.get_frame(0);
      REQUIRE(frame_decoder.get() != nullptr);
    }
  }
}

}  // Namespace
}  // namespace w32::wic
