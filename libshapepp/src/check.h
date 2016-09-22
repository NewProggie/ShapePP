// Copyright (c) 2016 Kai Wolf <mail@kai-wolf.me>
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef SHAPE_PP_CHECK_H
#define SHAPE_PP_CHECK_H

#include "internal_macros.h"
#include "logging.h"
#include <cstdlib>
#include <ostream>

namespace shapepp {
namespace internal {

// Checkhandler is the class constructed by failing CHECK macros.
// CheckHandler will log information about the faulures and abort when
// it is destructed

class CheckHandler {
public:
  CheckHandler(const char *check, const char *file, const char *func, int line)
      : log_(GetErrorLoggingInstance()) {
    log_ << file << ":" << line << ": " << func << ": Check `" << check
         << "' failed. ";
  }

  std::ostream &GetLog() { return log_; }

  ~CheckHandler() {
    log_ << std::endl;
    std::abort();
  }

  CheckHandler &operator=(const CheckHandler &) = delete;
  CheckHandler(const CheckHandler &) = delete;
  CheckHandler() = delete;

private:
  std::ostream &log_;
};
}
}

// The CHECK macro returns a std::ostream object that can have extra
// information written to it.
#ifndef NDEBUG
#define CHECK(b)                                                               \
  (b ? ::shapepp::internal::GetNullLoggingInstance()                               \
     : ::shapepp::internal::CheckHandler(#b, __FILE__, __func__, __LINE__)         \
                                                                               \
           .GetLog())
#else
#define CHECK(b)
::shapepp::internal::GetNullLoggingInstance()
#endif

#define CHECK_EQ(a, b) CHECK((a) == (b))
#define CHECK_NE(a, b) CHECK((a) != (b))
#define CHECK_GE(a, b) CHECK((a) >= (b))
#define CHECK_LE(a, b) CHECK((a) <= (b))
#define CHECK_GT(a, b) CHECK((a) > (b))
#define CHECK_LT(a, b) CHECK((a) < (b))

#endif
