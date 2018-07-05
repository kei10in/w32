#pragma once

#include <fileapi.h>

namespace w32 {

enum class generic_access_right : std::uint32_t {
  read = GENERIC_READ,
  write = GENERIC_WRITE,
  read_write = GENERIC_READ | GENERIC_WRITE,
};

}  // namespace w32
