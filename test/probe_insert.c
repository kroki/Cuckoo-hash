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

#include <xprobes/probe.h>
#include "../src/cuckoo_hash.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define UNUSED(arg)  if (arg) {}


struct depth_vector
{
  size_t size;
  size_t max_depth;
  int *depth_count;
};

static struct depth_vector depth_vector[32] = { [0] = { .size = 0 } };
static int depth_after_grows[32] = { 0 };


static
void
insert_done(const struct cuckoo_hash *hash,
            int phase, size_t depth, size_t max_depth)
{
  if (phase == 0)
    {
      size_t size = depth_vector[hash->power].size;
      if (size <= depth)
        {
          depth_vector[hash->power].depth_count =
            realloc(depth_vector[hash->power].depth_count,
                    (depth + 1) * sizeof(int));
          memset(&depth_vector[hash->power].depth_count[size], 0,
                 (depth + 1 - size) * sizeof(int));
          depth_vector[hash->power].size = depth + 1;
          depth_vector[hash->power].max_depth = max_depth;
        }
      ++depth_vector[hash->power].depth_count[depth];
    }
  else
    {
      depth_after_grows[hash->power] = depth;
    }
}


static
void
insert_exists(const struct cuckoo_hash *hash)
{
  UNUSED(hash);
}


static __attribute__((__destructor__))
void
report(void)
{
  fprintf(stderr,
          "probe_insert:\n"
          "insert depth:\n");
  for (size_t power = 0;
       power < sizeof(depth_vector) / sizeof(*depth_vector);
       ++power)
    {
      if (depth_vector[power].size == 0)
        continue;

      int sum = 0;
      for (size_t i = 0; i < depth_vector[power].size; ++i)
        sum += depth_vector[power].depth_count[i];

      double norm = sum / 100.0;
      sum = 0;
      fprintf(stderr, "%2zu (%zu):", power, depth_vector[power].max_depth);
      for (size_t i = 0; i < depth_vector[power].size; ++i)
        {
          if (depth_vector[power].depth_count[i] == 0)
            continue;

          sum += depth_vector[power].depth_count[i];
          fprintf(stderr, " %zu=%2.3f%%", i, sum / norm);
        }
      fprintf(stderr, "\n");
    }

  fprintf(stderr, "insert depth after table grows:\n");
  for (size_t power = 0;
       power < sizeof(depth_after_grows) / sizeof(*depth_after_grows);
       ++power)
    {
      if (depth_after_grows[power] == 0)
        continue;

      fprintf(stderr, "%2zu: %10d\n", power, depth_after_grows[power]);
    }
}


static
void
insert_grow_bin(const struct cuckoo_hash *hash, int phase, size_t max_depth)
{
  UNUSED(hash && phase && max_depth);

  fprintf(stderr, "bin grows happened\n");
  abort();
}


XPROBES_MODULE(NULL, 0,
  XPROBES_PROBE("cuckoo_hash_insert_exists",
                insert_exists, (const struct cuckoo_hash *)),
  XPROBES_PROBE("cuckoo_hash_insert_grow_bin",
                insert_grow_bin, (const struct cuckoo_hash *, int, size_t)),
  XPROBES_PROBE("cuckoo_hash_insert_done",
                insert_done, (const struct cuckoo_hash *,
                              int, size_t, size_t)));
