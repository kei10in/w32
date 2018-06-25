#include <catch/catch.hpp>

#include "imaging_factory.hpp"

namespace w32::wic {
namespace {

TEST_CASE("imaging_factory") {
  imaging_factory f;
}

TEST_CASE("imaging_factory::create_bitmap") {
  imaging_factory f;
  bitmap bmp = f.create_bitmap(1, 1, pixel_format_32bpp_rgba,
                               bitmap_create_cache_option::cache_on_demand);
}
}
// unnamed namespace
}  // namespace w32::wic
