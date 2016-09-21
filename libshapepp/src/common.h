// Copyright (c) 2014 Sofien Bouaziz <sofien.bouaziz@gmail.com>
// Copyright (c) 2014 LGG EPFL
// Copyright (c) 2016 Kai Wolf <mail@kai-wolf.me>
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef SHAPE_PP_COMMON_H
#define SHAPE_PP_COMMON_H

#include "internal_macros.h"

/// @brief Export functions to shared/dynamic libraries
#if defined(OS_WINDOWS)
  #if defined(SHAPEPP_IMPLEMENTATION)
    #define SHAPEPP_EXPORT __declspec(dllexport)
    #define SHAPEPP_STATIC_EXPORT static __declspec(dllexport)
    #define SHAPEPP_CALL __stdcall
  #else
    #define SHAPEPP_EXPORT __declspec(dllimport)
    #define SHAPEPP_STATIC_EXPORT static __declspec(dllimport)
    #define SHAPEPP_CALL __stdcall
  #endif // defined(SHAPEPP_IMPLEMENTATION)
#else // defined(OS_WINDOWS)
  #if defined(SHAPEPP_IMPLEMENTATION)
    #define SHAPEPP_EXPORT __attribute__((visibility("default")))
    #define SHAPEPP_STATIC_EXPORT static __attribute__((visibility("default")))
    #define SHAPEPP_CALL
  #else
    #define SHAPEPP_EXPORT
    #define SHAPEPP_STATIC_EXPORT
    #define SHAPEPP_CALL
  #endif // defined(SHAPEPP_IMPLEMENTATION)
#endif

#endif
