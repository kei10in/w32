#pragma once

#include <Unknwn.h>

#include <cassert>
#include <cstdint>

#include "com.hpp"
#include "com_ptr.hpp"

namespace w32::com {

namespace internal {

template <class T>
class unknown_t {
 protected:
  com_ptr<T> p_;

 public:
  using interface_type = T;
  using pointer = interface_type*;

  unknown_t(interface_type* p) : p_(p) { assert(p_); }

  unknown_t(CLSID const& clsid, class_context context)
      : p_(make_com<interface_type>(clsid, context)) {
    assert(p_);
  }

  pointer const& get() const { return p_.get(); }
};

}  // namespace internal

using unknown = internal::unknown_t<IUnknown>;

}  // namespace w32::com
