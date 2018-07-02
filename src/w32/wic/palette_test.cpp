#include <catch/catch.hpp>

#include <array>

#include "imaging_factory.hpp"
#include "palette.hpp"

namespace w32::wic {

namespace {

TEST_CASE("w32::wic::palette") {
  imaging_factory factory;

  SECTION("palette::initialize_predefined") {
    palette p = factory.create_palette();
    p.initialize_predefined(bitmap_palette_type::fixed_black_white, false);

    REQUIRE(p.get_type() == bitmap_palette_type::fixed_black_white);
    REQUIRE(p.is_black_white());
    REQUIRE(p.is_grayscale());
    REQUIRE(!p.has_alpha());
  }

  SECTION("palette::initialize_custom") {
    std::array<color_t, 3> palette_colors = {1, 2, 3};

    palette p = factory.create_palette();
    p.initialize_custom(palette_colors.data(), palette_colors.size());

    REQUIRE(p.get_type() == bitmap_palette_type::custom);
    REQUIRE(p.get_color_count() == 3);

    std::array<color_t, 3> colors1;
    REQUIRE(p.get_colors(3, colors1.data()) == 3);
    REQUIRE(colors1 == std::array<color_t, 3>{1, 2, 3});
  }

  SECTION("palette::initialize_from_bitmap") {
    bitmap bmp =
        factory.create_bitmap(1, 2, pixel_format_8bpp_gray,
                              bitmap_create_cache_option::cache_on_load);

    palette p = factory.create_palette();
    p.initialize_from_bitmap(bmp, 2, false);

    REQUIRE(p.get_type() == bitmap_palette_type::custom);
    REQUIRE(p.get_color_count() == 1);
  }

  SECTION("palette::initialize_from_palette") {
    palette base_palette = factory.create_palette();
    base_palette.initialize_predefined(bitmap_palette_type::fixed_halftone_8,
                                       false);

    palette p = factory.create_palette();
    p.initialize_from_palette(base_palette);

    REQUIRE(p.get_type() == bitmap_palette_type::fixed_halftone_8);
    REQUIRE(p.get_color_count() == base_palette.get_color_count());
  }
}

}  // unnamed namespace

}  // namespace w32::wic
