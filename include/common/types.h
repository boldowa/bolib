/**
 * @file types.h
 */
#pragma once

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "compiler.h"
#include "int_type.h"

#if    defined(WIN32) \
    || defined(_WIN32) \
    || defined(WINDOWS) \
    || defined(_WINDOWS) \
    || defined(Windows) \
    || defined(_Windows)
#  define isWindows 1
#  ifndef WINVER
#    define WINVER 0x0400  /* WINNT */
#  endif
#  define WIN32_LEAN_AND_MEAN
#  define popen _popen
#  define pclose _pclose
#else
#  define isWindows 0
#endif

#if    defined(UNIX) \
    || defined(_UNIX)
#  define isUnix 1
#else
#  define isUnix 0
#endif

#if    defined(Linux) \
    || defined(_Linux) \
    || defined(linux) \
    || defined(_linux)
#  define isLinux 1
#else
#  define isLinux 0
#endif


#if defined(_MSC_VER)
   /* MSVC funcs */
#  define strncasecmp _strnicmp
#  define strcasecmp _stricmp
#  if WINVER >= 0x0502
#    define fopen(fn,m) _fopen_b(fn,m,__func__)
     FILE* _fopen_b(const char*, const char*, const char*);
#  endif
#  include <strings.h>
#endif

/**
 * define maxpath
 */
#ifndef MAX_PATH
  #define MAX_PATH 260
#endif

/**
 * define __func__ for old Visual Studio
 */
#ifndef __func__
#  ifdef __FUNCTION__
#    define __func__ __FUNCTION__
#  endif
#endif

/**
 * string secure function overwrap for except visual studio
 */
#ifndef _MSC_VER
#  define strcpy_s(dst, len, src) strcpy(dst, src)
#  define strncpy_s(dst, len, src, cnt) strncpy(dst, src, cnt)
#  define strcat_s(s1, len, s2) strcat(s1, s2)
#  define strncat_s(s1, len, s2, cnt) strncat(s1, s2, cnt)
#  define sprintf_s(buf, len, fmt, ...)  sprintf(buf, fmt, ##__VA_ARGS__)
#  define _stprintf_s(buf, len, fmt, ...)  sprintf(buf, fmt, ##__VA_ARGS__)
#endif
