#include <catch/catch.hpp>

#include "bitmap_frame_encode.hpp"
#include "imaging_factory.hpp"

namespace w32::wic {
namespace {

TEST_CASE("w32::wic::bitmap_frame_encode") {
  imaging_factory f;

  bitmap_encoder encoder = f.create_encoder(container_format_tiff, nullptr);
  stream s = f.create_stream();
  s.initialize_from_filename("./test_data/image.tiff",
                             generic_access_right::write);
  encoder.initialize(s, bitmap_encoder_cache_option::no_cache);

  bitmap_frame_encode frame = encoder.create_new_frame(nullptr);
  REQUIRE(frame.get() != nullptr);

  SECTION("initalize") {
    REQUIRE_NOTHROW(frame.initialize(nullptr));

    SECTION("write_pixels") {
      frame.set_size(2, 3);
      frame.set_resolution(72, 72);
      frame.set_pixel_format(pixel_format_8bpp_gray);
      std::byte pixels[] = {
          std::byte{0}, std::byte{1}, std::byte{0}, std::byte{0},
          std::byte{2}, std::byte{3}, std::byte{0}, std::byte{0},
          std::byte{4}, std::byte{5}, std::byte{0}, std::byte{0},
      };

      frame.write_pixels(3, 4, sizeof(pixels) / sizeof(pixels[0]), pixels);
      frame.commit();
    }

    SECTION("write_source") {
      bitmap_decoder decoder = f.create_decoder_from_filename(
          "./test_data/image1.png", nullptr, generic_access_right::read,
          decode_options::cache_on_load);
      bitmap_frame_decode frame_decoder = decoder.get_frame(0);

      SECTION("with rect") {
        frame.write_source(frame_decoder, {0, 0, 10, 20});
        frame.commit();
      }

      SECTION("without rect") {
        frame.write_source(frame_decoder);
        frame.commit();
      }
    }

    SECTION("set_palette") {
      palette p = f.create_palette();
      p.initialize_predefined(bitmap_palette_type::fixed_web_palette, false);
      REQUIRE_NOTHROW(frame.set_palette(p));
    }

    SECTION("set_thumbnail") {
      bitmap_decoder decoder = f.create_decoder_from_filename(
          "./test_data/image1.png", nullptr, generic_access_right::read,
          decode_options::cache_on_load);
      bitmap_frame_decode frame_decoder = decoder.get_frame(0);
      frame.set_thumbnail(frame_decoder);
    }
  }

  SECTION("get_metadata_query_writer") {
    REQUIRE_THROWS(frame.get_metadata_query_writer());
  }
}

}  // namespace
}  // namespace w32::wic
