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
#include <stdio.h>

#define UNUSED(arg)  if (arg) {}


static size_t hash1 = 0;
static size_t hash2 = 0;
static size_t not_found = 0;


static
void
lookup_hash1(const struct cuckoo_hash *hash, int depth)
{
  UNUSED(hash && depth);

  ++hash1;
}


static
void
lookup_hash2(const struct cuckoo_hash *hash, int depth)
{
  UNUSED(hash && depth);

  ++hash2;
}


static
void
lookup_not_found(const struct cuckoo_hash *hash, int depth)
{
  UNUSED(hash && depth);

  ++not_found;
}


static
void
command(const char *cmd, int (*out)(const char *msg))
{
  if (strcmp(cmd, "dump") == 0)
    {
      char buf[128];
      sprintf(buf,
              "hash1: %zu\n"
              "hash2: %zu\n"
              "not_found: %zu\n",
              hash1, hash2, not_found);
      out(buf);
    }
  else
    {
      out("unknown command ");
      out(cmd);
    }
}


static __attribute__((__destructor__))
void
report(void)
{
  fprintf(stderr,
          "probe_lookup:\n"
          "hash1: %zu\n"
          "hash2: %zu\n"
          "not_found: %zu\n",
          hash1, hash2, not_found);
}


XPROBES_MODULE(command, 0,
  XPROBES_PROBE("cuckoo_hash_lookup_hash1",
                lookup_hash1, (const struct cuckoo_hash *, int)),
  XPROBES_PROBE("cuckoo_hash_lookup_hash2",
                lookup_hash2, (const struct cuckoo_hash *, int)),
  XPROBES_PROBE("cuckoo_hash_lookup_not_found",
                lookup_not_found, (const struct cuckoo_hash *, int)));
