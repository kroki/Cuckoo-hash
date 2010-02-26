/*
  Copyright (C) 2010 Tomash Brechko.  All rights reserved.

  This file is part of XProbes.

  XProbes is free software: you can redistribute it and/or modify
  it under the terms of the GNU Lesser General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  XProbes is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public License
  along with XProbes.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef XPROBES_H
#define XPROBES_H 1

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif


#if defined(WITH_XPROBES)

#include <xprobes/site.h>

#elif defined(WITH_SYSTEMTAP)

#include <sys/sdt.h>

#define XPROBES_ARGC_SFX0(z, n, ...)  n
#define XPROBES_ARGC_SFX1(z, n, ...)  XPROBES_ARGC_SFX0(z, ##__VA_ARGS__, z)
#define XPROBES_ARGC_SFX2(z, n, ...)  XPROBES_ARGC_SFX1(z, ##__VA_ARGS__, 1)
#define XPROBES_ARGC_SFX3(z, n, ...)  XPROBES_ARGC_SFX2(z, ##__VA_ARGS__, 2)
#define XPROBES_ARGC_SFX4(z, n, ...)  XPROBES_ARGC_SFX3(z, ##__VA_ARGS__, 3)
#define XPROBES_ARGC_SFX5(z, n, ...)  XPROBES_ARGC_SFX4(z, ##__VA_ARGS__, 4)
#define XPROBES_ARGC_SFX6(z, n, ...)  XPROBES_ARGC_SFX5(z, ##__VA_ARGS__, 5)
#define XPROBES_ARGC_SFX7(z, n, ...)  XPROBES_ARGC_SFX6(z, ##__VA_ARGS__, 6)
#define XPROBES_ARGC_SFX8(z, n, ...)  XPROBES_ARGC_SFX7(z, ##__VA_ARGS__, 7)
#define XPROBES_ARGC_SFX9(z, n, ...)  XPROBES_ARGC_SFX8(z, ##__VA_ARGS__, 8)
#define XPROBES_ARGC_SFX10(z, n, ...)  XPROBES_ARGC_SFX9(z, ##__VA_ARGS__, 9)
#define XPROBES_ARGC_SFX(...)  XPROBES_ARGC_SFX10(/*empty*/, ##__VA_ARGS__, 10)

#define XPROBES_CONCAT(a, b)  a##b
#define XPROBES_EVAL_CONCAT(a, b)  XPROBES_CONCAT(a, b)

#define XPROBES_FLATTEN_ARGS(...)  , ##__VA_ARGS__

#define XPROBES_SITE(provider, name, proto, args)                       \
  do                                                                    \
    {                                                                   \
      if (0)                                                            \
        {                                                               \
          extern void _xprobes_typecheck_##provider##_##name proto;     \
          _xprobes_typecheck_##provider##_##name args;                  \
        }                                                               \
                                                                        \
      XPROBES_EVAL_CONCAT                                               \
        (STAP_, XPROBES_EVAL_CONCAT(PROBE, XPROBES_ARGC_SFX args)       \
                  (provider, name XPROBES_FLATTEN_ARGS args));          \
    }                                                                   \
  while (0)

#elif defined(WITH_DTRACE)

#define XPROBES_SITE(provider, name, proto, args)       \
  do                                                    \
    {                                                   \
      extern void __dtrace_##provider##___##name proto; \
      __dtrace_##provider##___##name args;              \
    }                                                   \
  while (0)

#else

#define XPROBES_SITE(provider, name, proto, args)

#endif


#endif  /* ! XPROBES_H */
