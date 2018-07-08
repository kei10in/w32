#include <catch/catch.hpp>

#include <WincodecSdk.h>

#include "imaging_factory.hpp"

#pragma comment(lib, "WindowsCodecs.lib")

namespace w32::wic {
namespace {

TEST_CASE("w32::wic::imaging_factory") {
  imaging_factory f;

  SECTION("create_decoder_from_filename") {
    bitmap_decoder decoder = f.create_decoder_from_filename(
        "./test_data/image1.png", nullptr, generic_access_right::read,
        decode_options::cache_on_load);

    REQUIRE(decoder.get() != nullptr);
  }

  SECTION("create_decoder_from_stream") {
    stream s = f.create_stream();
    s.initialize_from_filename("./test_data/image1.png",
                               generic_access_right::read);
    bitmap_decoder decoder =
        f.create_decoder_from_stream(s, nullptr, decode_options::cache_on_load);

    REQUIRE(decoder.get() != nullptr);
  }

  SECTION("create_component_info") {
    component_info info = f.create_component_info(CLSID_WICPngEncoder);
    REQUIRE(info.get() != nullptr);
  }

  SECTION("create_decoder") {
    bitmap_decoder decoder = f.create_decoder(GUID_ContainerFormatPng, nullptr);
    REQUIRE(decoder.get() != nullptr);
  }

  SECTION("create_encoder") {
    bitmap_encoder encoder = f.create_encoder(GUID_ContainerFormatPng, nullptr);
    REQUIRE(encoder.get() != nullptr);
  }

  SECTION("create_palette") {
    palette p = f.create_palette();
    REQUIRE(p.get() != nullptr);
  }

  SECTION("create_format_converter") {
    format_converter converter = f.create_format_converter();
    REQUIRE(converter.get() != nullptr);
  }

  SECTION("create_bitmap_scaler") {
    bitmap_scaler scaler = f.create_bitmap_scaler();
    REQUIRE(scaler.get() != nullptr);
  }

  SECTION("create_bitmap_clipper") {
    bitmap_clipper clipper = f.create_bitmap_clipper();
    REQUIRE(clipper.get() != nullptr);
  }

  SECTION("create_bitmap_flip_rotator") {
    bitmap_flip_rotator rotator = f.create_bitmap_flip_rotator();
    REQUIRE(rotator.get() != nullptr);
  }

  SECTION("create_stream") {
    stream s = f.create_stream();
    REQUIRE(s.get() != nullptr);
  }

  SECTION("create_color_context") {
    color_context context = f.create_color_context();
    REQUIRE(context.get() != nullptr);
  }

  SECTION("create_color_transformer") {
    color_transform transform = f.create_color_transformer();
    REQUIRE(transform.get() != nullptr);
  }

  SECTION("create_bitmap") {
    bitmap bmp = f.create_bitmap({1, 1}, pixel_format_32bpp_rgba,
                                 bitmap_create_cache_option::cache_on_demand);
    REQUIRE(bmp.get() != nullptr);
  }

  SECTION("create_bitmap_from_source") {
    bitmap bmp = f.create_bitmap({1, 1}, pixel_format_32bpp_rgba,
                                 bitmap_create_cache_option::cache_on_demand);
    bitmap bmp2 = f.create_bitmap_from_source(
        bmp, bitmap_create_cache_option::cache_on_demand);
    REQUIRE(bmp2.get() != nullptr);
  }

  SECTION("create_bitmap_from_source_rect") {
    bitmap bmp = f.create_bitmap({1, 1}, pixel_format_32bpp_rgba,
                                 bitmap_create_cache_option::cache_on_demand);
    bitmap bmp2 = f.create_bitmap_from_source_rect(bmp, 0, 0, 1, 1);
    REQUIRE(bmp2.get() != nullptr);
  }

  SECTION("create_bitmap_from_memory") {
    byte buffer[4] = {};
    bitmap bmp = f.create_bitmap_from_memory(1, 1, pixel_format_32bpp_rgba, 4,
                                             4, buffer);
    REQUIRE(bmp.get() != nullptr);
  }

  // SECTION("create_bitmap_from_hbitmap") {}

  // SECTION("create_bitmap_from_hicon") {}

  SECTION("create_fast_metadata_encoder_from_decoder") {
    bitmap_decoder decoder = f.create_decoder_from_filename(
        "./test_data/image1.png", nullptr, generic_access_right::read,
        decode_options::cache_on_load);

    // The Windows provided decoder is not support fast metadata encoder.
    REQUIRE_THROWS(f.create_fast_metadata_encoder_from_decoder(decoder));
  }

  // SECTION("create_fast_metadata_encoder_from_frame_decode") {}

  SECTION("create_query_writer") {
    metadata_query_writer writer =
        f.create_query_writer(GUID_MetadataFormatExif, nullptr);
    REQUIRE(writer.get() != nullptr);
  }

  // SECTION("create_query_writer_from_reader") {}
}

}  // namespace
}  // namespace w32::wic
