#pragma once

#include <Wincodec.h>

#include "../guid.hpp"

namespace w32::wic {

class pixel_format_id {
  guid guid_;

 public:
  constexpr pixel_format_id() noexcept : guid_{} {}

  pixel_format_id(pixel_format_id const& pf) noexcept = default;
  pixel_format_id& operator=(pixel_format_id const& pf) noexcept = default;

  pixel_format_id(pixel_format_id&& pf) noexcept = default;
  pixel_format_id& operator=(pixel_format_id&& pf) noexcept = default;

  constexpr pixel_format_id(guid const& guid_value) noexcept
      : guid_(guid_value) {}

  pixel_format_id& operator=(guid const& guid_value) noexcept {
    guid_ = guid_value;
    return *this;
  }

  constexpr operator guid const&() const noexcept { return guid_; }

  operator guid&() noexcept { return guid_; }

  guid const* operator&() const noexcept { return &guid_; }
  guid* operator&() noexcept { return &guid_; }

  guid const* operator->() const noexcept { return &guid_; }
  guid* operator->() noexcept { return &guid_; }
};

// clang-format off
const pixel_format_id pixel_format_undefined = GUID_WICPixelFormatUndefined;
const pixel_format_id pixel_format_dontcare = GUID_WICPixelFormatDontCare;
const pixel_format_id pixel_format_1bpp_indexed = GUID_WICPixelFormat1bppIndexed;
const pixel_format_id pixel_format_2bpp_indexed = GUID_WICPixelFormat2bppIndexed;
const pixel_format_id pixel_format_4bpp_indexed = GUID_WICPixelFormat4bppIndexed;
const pixel_format_id pixel_format_8bpp_indexed = GUID_WICPixelFormat8bppIndexed;
const pixel_format_id pixel_format_blackwhite = GUID_WICPixelFormatBlackWhite;
const pixel_format_id pixel_format_2bpp_gray = GUID_WICPixelFormat2bppGray;
const pixel_format_id pixel_format_4bpp_gray = GUID_WICPixelFormat4bppGray;
const pixel_format_id pixel_format_8bpp_gray = GUID_WICPixelFormat8bppGray;
const pixel_format_id pixel_format_8bpp_alpha = GUID_WICPixelFormat8bppAlpha;
const pixel_format_id pixel_format_16bpp_bgr_555 = GUID_WICPixelFormat16bppBGR555;
const pixel_format_id pixel_format_16bpp_bgr_565 = GUID_WICPixelFormat16bppBGR565;
const pixel_format_id pixel_format_16bpp_bgra_5551 = GUID_WICPixelFormat16bppBGRA5551;
const pixel_format_id pixel_format_16bpp_gray = GUID_WICPixelFormat16bppGray;
const pixel_format_id pixel_format_24bpp_bgr = GUID_WICPixelFormat24bppBGR;
const pixel_format_id pixel_format_24bpp_rgb = GUID_WICPixelFormat24bppRGB;
const pixel_format_id pixel_format_32bpp_bgr = GUID_WICPixelFormat32bppBGR;
const pixel_format_id pixel_format_32bpp_bgra = GUID_WICPixelFormat32bppBGRA;
const pixel_format_id pixel_format_32bpp_pbgra = GUID_WICPixelFormat32bppPBGRA;
const pixel_format_id pixel_format_32bpp_gray_float = GUID_WICPixelFormat32bppGrayFloat;
#if (_WIN32_WINNT >= _WIN32_WINNT_WIN8) || defined(_WIN7_PLATFORM_UPDATE)
const pixel_format_id pixel_format_32bpp_rgb = GUID_WICPixelFormat32bppRGB;
#endif
const pixel_format_id pixel_format_32bpp_rgba = GUID_WICPixelFormat32bppRGBA;
const pixel_format_id pixel_format_32bpp_prgba = GUID_WICPixelFormat32bppPRGBA;
const pixel_format_id pixel_format_48bpp_rgb = GUID_WICPixelFormat48bppRGB;
const pixel_format_id pixel_format_48bpp_bgr = GUID_WICPixelFormat48bppBGR;
#if (_WIN32_WINNT >= _WIN32_WINNT_WIN8) || defined(_WIN7_PLATFORM_UPDATE)
const pixel_format_id pixel_format_64bpp_rgb = GUID_WICPixelFormat64bppRGB;
#endif
const pixel_format_id pixel_format_64bpp_rgba = GUID_WICPixelFormat64bppRGBA;
const pixel_format_id pixel_format_64bpp_bgra = GUID_WICPixelFormat64bppBGRA;
const pixel_format_id pixel_format_64bpp_prgba = GUID_WICPixelFormat64bppPRGBA;
const pixel_format_id pixel_format_64bpp_pbgra = GUID_WICPixelFormat64bppPBGRA;
const pixel_format_id pixel_format_16bpp_gray_fixed_point = GUID_WICPixelFormat16bppGrayFixedPoint;
const pixel_format_id pixel_format_32bpp_bgr_101010 = GUID_WICPixelFormat32bppBGR101010;
const pixel_format_id pixel_format_48bpp_rgb_fixed_point = GUID_WICPixelFormat48bppRGBFixedPoint;
const pixel_format_id pixel_format_48bpp_bgr_fixed_point = GUID_WICPixelFormat48bppBGRFixedPoint;
const pixel_format_id pixel_format_96bpp_rgb_fixed_point = GUID_WICPixelFormat96bppRGBFixedPoint;
#if (_WIN32_WINNT >= _WIN32_WINNT_WIN8) || defined(_WIN7_PLATFORM_UPDATE)
const pixel_format_id pixel_format_96bpp_rgb_float = GUID_WICPixelFormat96bppRGBFloat;
#endif
const pixel_format_id pixel_format_128bpp_rgba_float = GUID_WICPixelFormat128bppRGBAFloat;
const pixel_format_id pixel_format_128bpp_prgba_float = GUID_WICPixelFormat128bppPRGBAFloat;
const pixel_format_id pixel_format_128bpp_rgb_float = GUID_WICPixelFormat128bppRGBFloat;
const pixel_format_id pixel_format_32bpp_cmyk = GUID_WICPixelFormat32bppCMYK;
const pixel_format_id pixel_format_64bpp_rgba_fixed_point = GUID_WICPixelFormat64bppRGBAFixedPoint;
const pixel_format_id pixel_format_64bpp_bgra_fixed_point = GUID_WICPixelFormat64bppBGRAFixedPoint;
const pixel_format_id pixel_format_64bpp_rgb_fixed_point = GUID_WICPixelFormat64bppRGBFixedPoint;
const pixel_format_id pixel_format_128bpp_rgba_fixed_point = GUID_WICPixelFormat128bppRGBAFixedPoint;
const pixel_format_id pixel_format_128bpp_rgb_fixed_point = GUID_WICPixelFormat128bppRGBFixedPoint;
const pixel_format_id pixel_format_64bpp_rgba_half = GUID_WICPixelFormat64bppRGBAHalf;
#if (_WIN32_WINNT >= _WIN32_WINNT_WIN8) || defined(_WIN7_PLATFORM_UPDATE)
const pixel_format_id pixel_format_64bpp_prgba_half = GUID_WICPixelFormat64bppPRGBAHalf;
#endif
const pixel_format_id pixel_format_64bpp_rgb_half = GUID_WICPixelFormat64bppRGBHalf;
const pixel_format_id pixel_format_48bpp_rgb_half = GUID_WICPixelFormat48bppRGBHalf;
const pixel_format_id pixel_format_32bpp_rgbe = GUID_WICPixelFormat32bppRGBE;
const pixel_format_id pixel_format_16bpp_gray_half = GUID_WICPixelFormat16bppGrayHalf;
const pixel_format_id pixel_format_32bpp_gray_fixed_point = GUID_WICPixelFormat32bppGrayFixedPoint;
const pixel_format_id pixel_format_32bpp_rgba_1010102 = GUID_WICPixelFormat32bppRGBA1010102;
const pixel_format_id pixel_format_32bpp_rgba_1010102_xr = GUID_WICPixelFormat32bppRGBA1010102XR;
const pixel_format_id pixel_format_64bpp_cmyk = GUID_WICPixelFormat64bppCMYK;
const pixel_format_id pixel_format_24bpp_3channels = GUID_WICPixelFormat24bpp3Channels;
const pixel_format_id pixel_format_32bpp_4channels = GUID_WICPixelFormat32bpp4Channels;
const pixel_format_id pixel_format_40bpp_5channels = GUID_WICPixelFormat40bpp5Channels;
const pixel_format_id pixel_format_48bpp_6channels = GUID_WICPixelFormat48bpp6Channels;
const pixel_format_id pixel_format_56bpp_7channels = GUID_WICPixelFormat56bpp7Channels;
const pixel_format_id pixel_format_64bpp_8channels = GUID_WICPixelFormat64bpp8Channels;
const pixel_format_id pixel_format_48bpp_3channels = GUID_WICPixelFormat48bpp3Channels;
const pixel_format_id pixel_format_64bpp_4channels = GUID_WICPixelFormat64bpp4Channels;
const pixel_format_id pixel_format_80bpp_5channels = GUID_WICPixelFormat80bpp5Channels;
const pixel_format_id pixel_format_96bpp_6channels = GUID_WICPixelFormat96bpp6Channels;
const pixel_format_id pixel_format_112bpp_7channels = GUID_WICPixelFormat112bpp7Channels;
const pixel_format_id pixel_format_128bpp_8channels = GUID_WICPixelFormat128bpp8Channels;
const pixel_format_id pixel_format_40bpp_cmyk_alpha = GUID_WICPixelFormat40bppCMYKAlpha;
const pixel_format_id pixel_format_80bpp_cmyk_alpha = GUID_WICPixelFormat80bppCMYKAlpha;
const pixel_format_id pixel_format_32bpp_3channels_alpha = GUID_WICPixelFormat32bpp3ChannelsAlpha;
const pixel_format_id pixel_format_40bpp_4channels_alpha = GUID_WICPixelFormat40bpp4ChannelsAlpha;
const pixel_format_id pixel_format_48bpp_5channels_alpha = GUID_WICPixelFormat48bpp5ChannelsAlpha;
const pixel_format_id pixel_format_56bpp_6channels_alpha = GUID_WICPixelFormat56bpp6ChannelsAlpha;
const pixel_format_id pixel_format_64bpp_7channels_alpha = GUID_WICPixelFormat64bpp7ChannelsAlpha;
const pixel_format_id pixel_format_72bpp_8channels_alpha = GUID_WICPixelFormat72bpp8ChannelsAlpha;
const pixel_format_id pixel_format_64bpp_3channels_alpha = GUID_WICPixelFormat64bpp3ChannelsAlpha;
const pixel_format_id pixel_format_80bpp_4channels_alpha = GUID_WICPixelFormat80bpp4ChannelsAlpha;
const pixel_format_id pixel_format_96bpp_5channels_alpha = GUID_WICPixelFormat96bpp5ChannelsAlpha;
const pixel_format_id pixel_format_112bpp_6channels_alpha = GUID_WICPixelFormat112bpp6ChannelsAlpha;
const pixel_format_id pixel_format_128bpp_7channels_alpha = GUID_WICPixelFormat128bpp7ChannelsAlpha;
const pixel_format_id pixel_format_144bpp_8channels_alpha = GUID_WICPixelFormat144bpp8ChannelsAlpha;
const pixel_format_id pixel_format_8bpp_y = GUID_WICPixelFormat8bppY;
const pixel_format_id pixel_format_8bpp_cb = GUID_WICPixelFormat8bppCb;
const pixel_format_id pixel_format_8bpp_cr = GUID_WICPixelFormat8bppCr;
const pixel_format_id pixel_format_16bpp_cbcr = GUID_WICPixelFormat16bppCbCr;
const pixel_format_id pixel_format_16bpp_y_quantized_dct_coefficients = GUID_WICPixelFormat16bppYQuantizedDctCoefficients;
const pixel_format_id pixel_format_16bpp_cb_quantized_dct_coefficients = GUID_WICPixelFormat16bppCbQuantizedDctCoefficients;
const pixel_format_id pixel_format_16bpp_cr_quantized_dct_coefficients = GUID_WICPixelFormat16bppCrQuantizedDctCoefficients;
// clang-format on

}  // namespace w32::wic
