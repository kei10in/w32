# w32

The w32 is C++ wrapper for Win32 API.

## Example

```c++
#include <w32/wic.hpp>

void f() {
  w32::wic::imaging_factory factory;

  w32::wic::bitmap bmp = factory.create_bitmap(
    600, 400, pixel_format_32bpp_rgba, bitmap_create_cache_option::cache_on_demand);
  );

  w32::wic::bitmap_lock lock = bmp.lock();

  w32::wic::bitmap_view view = bmp.get_view();

  // read and write bitmap
}
```
