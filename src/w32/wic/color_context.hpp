#pragma once

#include <filesystem>

#include "wic_fwd.hpp"

namespace w32::wic {

enum class exif_color_space : std::uint32_t {
  srgb = 0x01,
  adobe_rgb = 0x02,
};

namespace internal {

template <class T>
class color_context_t : public com::internal::unknown_t<T> {
 public:
  using com::internal::unknown_t<T>::unknown_t;

  inline void initialize_from_filename(
      std::filesystem::path const& filename) const;

  inline void initialize_from_memory(std::byte const* buffer,
                                     std::size_t size) const;

  inline void initialize_from_exif_color_space(exif_color_space value) const;

  inline color_context_type get_type() const;

  template <class Allocator = std::allocator<std::byte>>
  std::vector<std::byte, Allocator> get_profile_bytes(
      Allocator const& alloc = Allocator()) const;

  inline exif_color_space get_exif_color_space() const;
};

template <class T>
inline void color_context_t<T>::initialize_from_filename(
    std::filesystem::path const& filename) const {
  HRESULT hr = p_->InitializeFromFilename(filename.native().c_str());
  com::raise_if_failed(hr);
}

template <class T>
inline void color_context_t<T>::initialize_from_memory(std::byte const* buffer,
                                                       std::size_t size) const {
  HRESULT hr =
      p_->InitializeFromMemory(buffer, static_cast<std::uint32_t>(size));
  com::raise_if_failed(hr);
}

template <class T>
inline void color_context_t<T>::initialize_from_exif_color_space(
    exif_color_space value) const {
  HRESULT hr =
      p_->InitializeFromExifColorSpace(static_cast<std::uint32_t>(value));
  com::raise_if_failed(hr);
}

template <class T>
inline color_context_type color_context_t<T>::get_type() const {
  WICColorContextType type;
  HRESULT hr = p_->GetType(&type);
  com::raise_if_failed(hr);
  return static_cast<color_context_type>(type);
}

template <class T>
template <class Allocator>
std::vector<std::byte, Allocator> color_context_t<T>::get_profile_bytes(
    Allocator const& alloc) const {
  UINT needed;
  HRESULT hr;

  hr = p_->GetProfileBytes(0, nullptr, &needed);
  com::raise_if_failed(hr);

  std::vector<std::byete, Allocator> buffer{needed, alloc};
  hr = p_->GetProfileBytes(needed, reinterpret_cast<BYTE*>(buffer.data()),
                           &needed);
  com::raise_if_failed(hr);

  return buffer;
}

template <class T>
inline exif_color_space color_context_t<T>::get_exif_color_space() const {
  UINT type;
  HRESULT hr = p_->GetExifColorSpace(&type);
  com::raise_if_failed(hr);
  return static_cast<exif_color_space>(type);
}

}  // namespace internal
}  // namespace w32::wic
