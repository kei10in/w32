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
  "src/w32/com/ocidl.hpp"
  "src/w32/com/stream.hpp"
  "src/w32/com/unknown.hpp"
  "src/w32/utils/enum_flags.hpp"
  "src/w32/wic/bitmap_clipper.hpp"
  "src/w32/wic/bitmap_codec_info.hpp"
  "src/w32/wic/bitmap_decoder_info.hpp"
  "src/w32/wic/bitmap_decoder.hpp"
  "src/w32/wic/bitmap_encoder.hpp"
  "src/w32/wic/bitmap_flip_rotator.hpp"
  "src/w32/wic/bitmap_frame_decode.hpp"
  "src/w32/wic/bitmap_frame_encode.hpp"
  "src/w32/wic/bitmap_lock.hpp"
  "src/w32/wic/bitmap_scaler.hpp"
  "src/w32/wic/bitmap_source.hpp"
  "src/w32/wic/bitmap_view.hpp"
  "src/w32/wic/bitmap.hpp"
  "src/w32/wic/color_context.hpp"
  "src/w32/wic/color_transform.hpp"
  "src/w32/wic/component_info.hpp"
  "src/w32/wic/fast_metadata_encoder.hpp"
  "src/w32/wic/format_converter.hpp"
  "src/w32/wic/imaging_factory.hpp"
  "src/w32/wic/metadata_query_reader.hpp"
  "src/w32/wic/metadata_query_writer.hpp"
  "src/w32/wic/palette.hpp"
  "src/w32/wic/stream.hpp"
  "src/w32/wic/wic_def.hpp"
  "src/w32/wic/wic_fwd.hpp"
  "src/w32/wic/wic_guids.hpp"
  "src/w32/wic/wicsdk_guids.hpp"
  "src/w32/com.hpp"
  "src/w32/result.hpp"
  "src/w32/w32.hpp"
  "src/w32/wic.hpp"
  )

set(w32_TESTS
  "src/w32/com/com_ptr_test.cpp"
  "src/w32/com/stream_test.cpp"
  "src/w32/com/unknown_test.cpp"
  "src/w32/utils/enum_flags_test.cpp"
  "src/w32/wic/bitmap_codec_info_test.cpp"
  "src/w32/wic/bitmap_decoder_info_test.cpp"
  "src/w32/wic/bitmap_decoder_test.cpp"
  "src/w32/wic/bitmap_encoder_test.cpp"
  "src/w32/wic/bitmap_frame_decode_test.cpp"
  "src/w32/wic/bitmap_frame_encode_test.cpp"
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
