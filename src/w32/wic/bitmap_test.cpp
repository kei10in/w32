#include <catch/catch.hpp>

#include <vector>

#include "../wic.hpp"

namespace w32::wic {
namespace {

TEST_CASE("wic bitmap") {
  imaging_factory factory;
  bitmap bmp =
      factory.create_bitmap(2, 2, pixel_format_8bpp_gray,
                            bitmap_create_cache_option::cache_on_demand);

  SECTION("bitmap::set_resolution / bitmap_source::get_resolution") {
    bmp.set_resolution(300.0, 300.0);
    resolution<double> res1 = bmp.get_resolution();
    REQUIRE(res1.dpi_x == Approx(300.0));
    REQUIRE(res1.dpi_y == Approx(300.0));

    bmp.set_resolution(600.0, 600.0);
    resolution<double> res2 = bmp.get_resolution();
    REQUIRE(res2.dpi_x == Approx(600.0));
    REQUIRE(res2.dpi_y == Approx(600.0));
  }

  SECTION("bitmap_source::get_size") {
    size<std::uint32_t> s = bmp.get_size();
    REQUIRE(s.width == 2);
    REQUIRE(s.height == 2);
  }

  SECTION("bitmap_source::get_pixel_format") {
    pixel_format_id pf = bmp.get_pixel_format();
    REQUIRE(pf == pixel_format_8bpp_gray);
  }

  SECTION("bitmap::lock") {
    SECTION("bitmap_lock::get_view") {
      bitmap_lock lock = bmp.lock(rect<std::int32_t>{0, 0, 2, 2},
                                  bitmap_lock_mode::read_and_write);

      bitmap_view bmp_view = lock.get_view();
      REQUIRE(bmp_view.size.width == 2);
      REQUIRE(bmp_view.size.height == 2);
      REQUIRE(bmp_view.stride >= 2 * 2);
      REQUIRE(bmp_view.pixel_format == pixel_format_8bpp_gray);
      REQUIRE(bmp_view.buffer_size >= 2 * 2);
    }

    SECTION("write through bitmap_lock") {
      {
        bitmap_lock lock = bmp.lock(rect<std::int32_t>{0, 0, 2, 2},
                                    bitmap_lock_mode::read_and_write);
        bitmap_view bmp_view = lock.get_view();

        bmp_view.data[0] = 1;
        bmp_view.data[bmp_view.stride + 1] = 1;
      }

      {
        bitmap_lock new_lock =
            bmp.lock(rect<std::int32_t>{0, 0, 2, 2}, bitmap_lock_mode::read);
        bitmap_view bmp_view = new_lock.get_view();

        REQUIRE(bmp_view.data[0] == 1);
        REQUIRE(bmp_view.data[1] == 0);
        REQUIRE(bmp_view.data[bmp_view.stride] == 0);
        REQUIRE(bmp_view.data[bmp_view.stride + 1] == 1);
      }

      SECTION("bitmap_source::copy_pixels") {
        std::vector<byte> buffer(4);

        bmp.copy_pixels(rect<std::int32_t>{0, 0, 2, 2}, 2, 4, buffer.data());
        REQUIRE(buffer[0] == 1);
        REQUIRE(buffer[1] == 0);
        REQUIRE(buffer[2] == 0);
        REQUIRE(buffer[3] == 1);
      }
    }
  }
}

}  // unnamed namespace
}  // namespace w32::wic
