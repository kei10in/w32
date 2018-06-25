#pragma once

#define WIN32WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <Objidl.h>

#include <cstdint>
#include <limits>

#include "unknown.hpp"

namespace w32::com {

enum class stream_seek : std::uint32_t {
  set = STREAM_SEEK_SET,
  current = STREAM_SEEK_CUR,
  end = STREAM_SEEK_END,
};

struct copied_counts {
  std::uint64_t read;
  std::uint64_t written;
};

namespace internal {

template <class T>
class sequential_stream_t : public unknown_t<T> {
 public:
  using unknown_t::unknown_t;

  std::size_t read(byte* p, std::size_t size) {
    std::size_t const read_limit = UINT32_MAX;

    std::size_t read_amount = 0;

    while (size > read_limit) {
      ULONG read_count;

      HRESULT hr = p_->Read(p, UINT32_MAX, &read_count);
      raise_if_failed(hr);

      read_amount += read_count;
      size -= read_count;

      if (hr == S_FALSE) {
        return read_amount;
      }
    }

    ULONG read_count;

    HRESULT hr = p_->Read(p, static_cast<std::uint32_t>(size), &read_count);
    raise_if_failed(hr);

    read_amount += read_count;

    return read_amount;
  }

  std::size_t write(byte const* p, std::size_t size) {
    std::size_t const write_limit = UINT32_MAX;

    std::size_t write_amount = 0;

    while (size > write_limit) {
      ULONG write_count;

      HRESULT hr = p_->Write(&p[write_amount], UINT32_MAX, &write_count);
      raise_if_failed(hr);

      write_amount += write_count;
      size -= write_count;
    }

    ULONG write_count;

    HRESULT hr = p_->Write(&p[write_amount], static_cast<std::uint32_t>(size),
                           &write_count);
    raise_if_failed(hr);

    write_amount += write_count;

    return write_amount;
  }
};

template <class T>
class stream_t : public sequential_stream_t<T> {
 public:
  using sequential_stream_t::sequential_stream_t;

  std::uint64_t seek(std::int64_t move, stream_seek origin) {
    LARGE_INTEGER move_count;
    move_count.QuadPart = move;
    ULARGE_INTEGER new_position;

    HRESULT hr =
        p_->Seek(move_count, static_cast<DWORD>(origin), &new_position);
    raise_if_failed(hr);

    return new_position.QuadPart;
  }

  void commit() {
    HRESULT hr = p_->Commit(STGD_DEFAULT);
    raise_if_failed(hr);
  }

  copied_counts copy_to(stream_t<IStream>& stream, std::uint64_t count) {
    copied_counts result;
    HRESULT hr = p_->CopyTo(stream.get(), count, &result.read, &resule.written);
    raise_if_failed(hr);
    return result;
  }

  void revert() {
    HRESULT hr = p_->Revert();
    raise_if_failed(hr);
  }

  std::uint64_t get_size() const {
    STATSTG statstg;
    HRESULT hr = p_->Stat(&statstg, STATFLAG_NONAME);
    raise_if_failed(hr);
    return static_cast<std::uint64_t>(statstg.cbSize.QuadPart);
  }

  void set_size(std::uint64_t new_size) {
    ULARGE_INTEGER ns;
    ns.QuadPart = new_size;
    HRESULT hr = p_->SetSize(ns);
    raise_if_failed(hr);
  }

  stream_t<IStream> clone() const {
    IStream cloned;
    HRESULT hr = p_->Clone(&cloned);
    raise_if_failed(hr);
    return cloned;
  }
};

}  // namespace internal

using sequential_stream = internal::sequential_stream_t<ISequentialStream>;
using stream = internal::stream_t<IStream>;

}  // namespace w32::com
