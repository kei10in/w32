#pragma once

#include <Shlwapi.h>

#include "../com.hpp"

namespace w32::shell {

inline com::stream create_memory_stream() {
  return SHCreateMemStream(nullptr, 0);
}

}  // namespace w32::shell
