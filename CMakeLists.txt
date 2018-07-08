cmake_minimum_required (VERSION 3.10)

project("w32")

file(COPY "test_data" DESTINATION ${CMAKE_BINARY_DIR})

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)
enable_testing()

add_compile_options("-std:c++17")
add_compile_options("-utf-8")

set(CATCH_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/3rd-party/catch)
add_library(Catch2 INTERFACE)
target_include_directories(Catch2 INTERFACE ${CATCH_INCLUDE_DIR})

set(w32_HEADERS
  "src/w32/com/com_ptr.hpp"
  "src/w32/com/com.hpp"
  "src/w32/com/error.hpp"
  "src/w32/com/stream.hpp"
  "src/w32/com/unknown.hpp"
  "src/w32/wic/bitmap_lock.hpp"
  "src/w32/wic/bitmap_source.hpp"
  "src/w32/wic/bitmap_view.hpp"
  "src/w32/wic/bitmap.hpp"
  "src/w32/wic/imaging_factory.hpp"
  "src/w32/wic/palette.hpp"
  "src/w32/wic/pixel_format.hpp"
  "src/w32/com.hpp"
  "src/w32/result.hpp"
  "src/w32/w32.hpp"
  "src/w32/wic.hpp"
  )

set(w32_TESTS
  "src/w32/com/com_ptr_test.cpp"
  "src/w32/com/stream_test.cpp"
  "src/w32/com/unknown_test.cpp"
  "src/w32/wic/bitmap_test.cpp"
  "src/w32/wic/imaging_factory_test.cpp"
  "src/w32/wic/palette_test.cpp"
  "src/w32/result_test.cpp"
  "src/w32/test.cpp"
  )

add_executable(w32_test ${w32_HEADERS} ${w32_TESTS})
target_link_libraries(w32_test Catch2)

include(Catch)
catch_discover_tests(w32_test)
