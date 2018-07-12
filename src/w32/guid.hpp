#pragma once

#include "guiddef.h"

namespace w32 {

using guid = GUID;

template <class T>
class tagged_guid : public guid {
 public:
  constexpr tagged_guid() noexcept : guid{} {}

  tagged_guid(tagged_guid const& pf) noexcept = default;
  tagged_guid& operator=(tagged_guid const& pf) noexcept = default;

  tagged_guid(tagged_guid&& pf) noexcept = default;
  tagged_guid& operator=(tagged_guid&& pf) noexcept = default;

  constexpr explicit tagged_guid(guid const& guid_value) noexcept
      : guid{guid_value} {}

  tagged_guid& operator=(guid const& guid_value) noexcept {
    guid = guid_value;
    return *this;
  }
};

}  // namespace w32
