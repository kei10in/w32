#pragma once

#include <memory>
#include <string>

#include "wic_fwd.hpp"

namespace w32::wic::internal {

template <class T>
class bitmap_codec_info_t : public com::internal::unknown_t<T> {
 public:
  using com::internal::unknown_t<T>::unknown_t;

  inline container_format_id get_container_format() const;

  template <class Allocator = std::allocator<pixel_format_id>>
  inline std::vector<pixel_format_id, Allocator> get_pixel_formats(
      Allocator const& alloc = Allocator{}) const;

  template <class Allocator = std::allocator<wchar_t>>
  inline std::basic_string<wchar_t, std::char_traits<wchar_t>, Allocator>
  get_color_management_version(Allocator const& alloc = Allocator{}) const;

  template <class Allocator = std::allocator<wchar_t>>
  inline std::basic_string<wchar_t, std::char_traits<wchar_t>, Allocator>
  get_device_manufacturer(Allocator const& alloc = Allocator{}) const;

  template <class Allocator = std::allocator<wchar_t>>
  inline std::basic_string<wchar_t, std::char_traits<wchar_t>, Allocator>
  get_device_models(Allocator const& alloc = Allocator{}) const;

  template <class Allocator = std::allocator<wchar_t>>
  inline std::basic_string<wchar_t, std::char_traits<wchar_t>, Allocator>
  get_mime_types(Allocator const& alloc = Allocator{}) const;

  template <class Allocator = std::allocator<wchar_t>>
  inline std::basic_string<wchar_t, std::char_traits<wchar_t>, Allocator>
  get_file_extensions(Allocator const& alloc = Allocator{}) const;

  inline bool does_support_animation() const;

  inline bool does_support_chromakey() const;

  inline bool does_support_lossless() const;

  inline bool does_support_multiframe() const;

  inline bool matches_mime_type(std::wstring_view const& mime_type) const;
};

template <class T>
template <class Allocator>
std::vector<pixel_format_id, Allocator>
bitmap_codec_info_t<T>::get_pixel_formats(Allocator const& alloc) const {
  HRESULT hr;
  std::uint32_t needed;

  hr = p_->GetPixelFormats(0, nullptr, &needed);
  com::raise_if_failed(hr);

  std::vector<pixel_format_id, Allocator> buffer{needed, alloc};

  hr = p_->GetPixelFormats(needed, buffer.data(), &needed);
  com::raise_if_failed(hr);

  return buffer;
}

template <class F, class Allocator>
inline std::basic_string<wchar_t, std::char_traits<wchar_t>, Allocator>
get_wstring(F func, Allocator const& alloc) {
  std::uint32_t needed;

  func(0, nullptr, &needed);

  std::basic_string<wchar_t, std::char_traits<wchar_t>, Allocator> buffer{
      needed, 0, alloc};

  if (needed == 0) {
    return buffer;
  }

  func(needed, buffer.data(), &needed);

  buffer.resize(buffer.size() - 1);

  return buffer;
}

template <class T>
template <class Allocator>
inline std::basic_string<wchar_t, std::char_traits<wchar_t>, Allocator>
bitmap_codec_info_t<T>::get_color_management_version(
    Allocator const& alloc) const {
  return get_wstring(
      [this](std::uint32_t count, wchar_t* result, std::uint32_t* actual) {
        HRESULT hr = p_->GetColorManagementVersion(count, result, actual);
        com::raise_if_failed(hr);
      },
      alloc);
}

template <class T>
template <class Allocator>
inline std::basic_string<wchar_t, std::char_traits<wchar_t>, Allocator>
bitmap_codec_info_t<T>::get_device_manufacturer(Allocator const& alloc) const {
  return get_wstring(
      [this](std::uint32_t count, wchar_t* result, std::uint32_t* actual) {
        HRESULT hr = p_->GetDeviceManufacturer(count, result, actual);
        com::raise_if_failed(hr);
      },
      alloc);
}

template <class T>
template <class Allocator>
std::basic_string<wchar_t, std::char_traits<wchar_t>, Allocator>
bitmap_codec_info_t<T>::get_device_models(Allocator const& alloc) const {
  return get_wstring(
      [this](std::uint32_t count, wchar_t* result, std::uint32_t* actual) {
        HRESULT hr = p_->GetDeviceModels(count, result, actual);
        com::raise_if_failed(hr);
      },
      alloc);
}

template <class T>
template <class Allocator>
std::basic_string<wchar_t, std::char_traits<wchar_t>, Allocator>
bitmap_codec_info_t<T>::get_mime_types(Allocator const& alloc) const {
  return get_wstring(
      [this](std::uint32_t count, wchar_t* result, std::uint32_t* actual) {
        HRESULT hr = p_->GetMimeTypes(count, result, actual);
        com::raise_if_failed(hr);
      },
      alloc);
}

template <class T>
template <class Allocator>
std::basic_string<wchar_t, std::char_traits<wchar_t>, Allocator>
bitmap_codec_info_t<T>::get_file_extensions(Allocator const& alloc) const {
  return get_wstring(
      [this](std::uint32_t count, wchar_t* result, std::uint32_t* actual) {
        HRESULT hr = p_->GetFileExtensions(count, result, actual);
        com::raise_if_failed(hr);
      },
      alloc);
}

template <class T>
inline bool bitmap_codec_info_t<T>::does_support_animation() const {
  BOOL result;
  HRESULT hr = p_->DoesSupportAnimation(&result);
  com::raise_if_failed(hr);
  return static_cast<bool>(result);
}

template <class T>
inline bool bitmap_codec_info_t<T>::does_support_chromakey() const {
  BOOL result;
  HRESULT hr = p_->DoesSupportChromakey(&result);
  com::raise_if_failed(hr);
  return static_cast<bool>(result);
}

template <class T>
inline bool bitmap_codec_info_t<T>::does_support_lossless() const {
  BOOL result;
  HRESULT hr = p_->DoesSupportLossless(&result);
  com::raise_if_failed(hr);
  return static_cast<bool>(result);
}

template <class T>
inline bool bitmap_codec_info_t<T>::does_support_multiframe() const {
  BOOL result;
  HRESULT hr = p_->DoesSupportMultiframe(&result);
  com::raise_if_failed(hr);
  return static_cast<bool>(result);
}

template <class T>
inline bool bitmap_codec_info_t<T>::matches_mime_type(
    std::wstring_view const& mime_type) const {
  BOOL result;
  HRESULT hr = p_->MatchesMimeType(mime_type.data(), &result);
  com::raise_if_failed(hr);
  return static_cast<bool>(result);
}

}  // namespace w32::wic::internal
