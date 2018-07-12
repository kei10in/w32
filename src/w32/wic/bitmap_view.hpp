#pragma once

#include <cstddef>

#include "../fundamentals.hpp"
#include "wic_guids.hpp"

namespace w32::wic {

struct bitmap_view {
  size<std::uint32_t> size;
  std::size_t stride;
  pixel_format_id pixel_format;
  std::size_t buffer_size;
  byte* data;
};

}  // namespace w32::wic
