#pragma once

#include <stdexcept>
#include <vector>

#include "bitmap_codec_info.hpp"
#include "wic_fwd.hpp"

namespace w32::wic {

class bitmap_pattern {
  WICBitmapPattern internal_;

 public:
  constexpr std::uint64_t position() const noexcept;
  constexpr std::size_t length() const noexcept;
  constexpr std::byte const* pattern() const noexcept;
  constexpr std::byte const* mask() const noexcept;
  constexpr bool end_of_stream() const noexcept;
};

template <class Allocator = std::allocator>
class bitmap_patterns_collection {
  std::size_t size_;
  std::vector<std::byte, Allocator> buffer_;

 public:
  inline bitmap_patterns_collection();
  bitmap_patterns_collection(bitmap_patterns_collection const& rhs) = delete;
  bitmap_patterns_collection& operator=(bitmap_patterns_collection const& rhs) =
      delete;
  bitmap_patterns_collection(bitmap_patterns_collection&& rhs) = default;
  bitmap_patterns_collection& operator=(bitmap_patterns_collection&& rhs) =
      default;

  explicit bitmap_patterns_collection(std::size_t size,
                                      std::vector<std::byte, Allocator> buffer);

  inline std::size_t size() const noexcept;

  inline bitmap_pattern const& operator[](std::size_t index) const noexcept;

  inline bitmap_pattern const& at(std::size_t index) const;
};

constexpr std::uint64_t bitmap_pattern::position() const noexcept {
  return internal_.Position.QuadPart;
}

constexpr std::size_t bitmap_pattern::length() const noexcept {
  return static_cast<std::size_t>(internal_.Length);
}

constexpr std::byte const* bitmap_pattern::pattern() const noexcept {
  return reinterpret_cast<std::byte const*>(internal_.Pattern);
}

constexpr std::byte const* bitmap_pattern::mask() const noexcept {
  return reinterpret_cast<std::byte const*>(internal_.Mask);
}

constexpr bool bitmap_pattern::end_of_stream() const noexcept {
  return internal_.EndOfStream > 0;
}

template <class Allocator>
inline bitmap_patterns_collection<Allocator>::bitmap_patterns_collection()
    : size_{} {}

template <class Allocator>
inline bitmap_patterns_collection<Allocator>::bitmap_patterns_collection(
    std::size_t size,
    std::vector<std::byte, Allocator> buffer)
    : size_{size}, buffer_{std::move(buffer)} {}

template <class Allocator>
inline std::size_t bitmap_patterns_collection<Allocator>::size() const
    noexcept {
  return size_;
}

template <class Allocator>
inline bitmap_pattern const& bitmap_patterns_collection<Allocator>::operator[](
    std::size_t index) const noexcept {
  bitmap_pattern const* p =
      reinterpret_cast<bitmap_pattern const*>(buffer_.data());
  return p[index];
}

template <class Allocator>
inline bitmap_pattern const& bitmap_patterns_collection<Allocator>::at(
    std::size_t index) const {
  if (index >= size_) {
    throw std::out_of_range("bitmap_patterns_collection::at");
  }
  return operator[](index);
}

namespace internal {

template <class T>
class bitmap_decoder_info_t : public bitmap_codec_info_t<T> {
 public:
  using bitmap_codec_info_t<T>::bitmap_codec_info_t;

  template <class Allocator = std::allocator<std::byte>>
  bitmap_patterns_collection<Allocator> get_patterns(
      Allocator const& alloc = Allocator()) const;

  inline bool matches_pattern(stream const& s) const;

  inline bitmap_decoder create_instance() const;
};

template <class T>
template <class Allocator>
bitmap_patterns_collection<Allocator> bitmap_decoder_info_t<T>::get_patterns(
    Allocator const& alloc) const {
  HRESULT hr;
  std::uint32_t count, needed;

  hr = p_->GetPatterns(0, nullptr, &count, &needed);
  com::raise_if_failed(hr);

  std::vector<std::byte, Allocator> buffer{needed, alloc};

  WICBitmapPattern* patterns =
      reinterpret_cast<WICBitmapPattern*>(buffer.data());

  hr = p_->GetPatterns(needed, patterns, &count, &needed);

  return bitmap_patterns_collection<Allocator>{static_cast<std::size_t>(count),
                                               std::move(buffer)};
}

template <class T>
inline bool bitmap_decoder_info_t<T>::matches_pattern(stream const& s) const {
  BOOL matches;
  HRESULT hr = p_->MatchesPattern(s.get(), &matches);
  com::raise_if_failed(hr);
  return matches > 0;
}

template <class T>
inline bitmap_decoder bitmap_decoder_info_t<T>::create_instance() const {
  IWICBitmapDecoder* decoder;
  HRESULT hr = p_->CreateInstance(&decoder);
  com::raise_if_failed(hr);
  return decoder;
}

}  // namespace internal
}  // namespace w32::wic
