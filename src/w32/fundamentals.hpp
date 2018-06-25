#pragma once

namespace w32 {

template <class T>
struct size {
  T width;
  T height;
};

template <class T>
struct rect {
  T x;
  T y;
  T width;
  T height;
};

template <class T>
struct resolution {
  T dpi_x;
  T dpi_y;
};

}  // namespace w32
