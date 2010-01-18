/*
  Copyright (C) 2010 Tomash Brechko.  All rights reserved.

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU Lesser General Public License as
  published by the Free Software Foundation, either version 3 of the
  License, or (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef TEST_H
#define TEST_H 1

#include <stdio.h>
#include <stdlib.h>


#define TEST_EXIT_IGNORE  77
#define TEST_HARD_ERROR  99


#define VAL(a)  # a
#define STR(a)  VAL(a)

#define ok(cond, ...)                                                   \
  ({                                                                    \
    if (! (cond))                                                       \
      {                                                                 \
        fprintf(stderr, __FILE__ ":" STR(__LINE__) ": failed: ");       \
        fprintf(stderr, # cond __VA_ARGS__);                            \
        fputs("\n", stderr);                                            \
        exit(1);                                                        \
      }                                                                 \
  })


#endif  /* ! TEST_H */
