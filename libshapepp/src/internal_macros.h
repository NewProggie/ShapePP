// Copyright (c) 2016 Kai Wolf <mail@kai-wolf.me>
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef SHAPE_PP_INTERNAL_MACROS_H
#define SHAPE_PP_INTERNAL_MACROS_H

// define host OS
#if defined(_WIN32) || defined(_WIN64)
  #define OS_WINDOWS 1
#elif defined(__APPLE__)
  #define OS_MACOSX 1
#elif defined(__FreeBSD__)
  #define OS_FREEBSD 1
#elif defined(__linux__)
  #define OS_LINUX 1
#endif

// determine used compiler
#if defined(__clang__)
  #define COMPILER_CLANG
#elif defined(_MSC_VER)
  #define COMPILER_MSVC
#elif defined(__GNUC__)
  #define COMPILER_GCC
#endif

#endif
