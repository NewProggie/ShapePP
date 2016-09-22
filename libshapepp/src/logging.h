// Copyright (c) 2016 Kai Wolf <mail@kai-wolf.me>
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef SHAPE_PP_LOGGING_H
#define SHAPE_PP_LOGGING_H

#include <ostream>

namespace shapepp {
namespace internal {

int GetLoggingLevel();
void SetLoggingLevel(int level);

std::ostream &GetNullLoggingInstance();
std::ostream &GetErrorLoggingInstance();

inline std::ostream &GetLoggingInstanceForLevel(int level) {
  if (level <= GetLoggingLevel()) {
    return GetErrorLoggingInstance();
  }
  return GetNullLoggingInstance();
}

}
}

#define LOG(X)                                                                 \
  (::shapepp::internal::GetLoggingInstanceForLevel(x) << "-- LOG(" << x        \
                                                      << "): ")

#endif
