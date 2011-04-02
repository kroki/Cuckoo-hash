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

#ifndef _CUCKOO_HASH_H
#define _CUCKOO_HASH_H 1

#include <stddef.h>
#include <stdbool.h>


#define CUCKOO_HASH_FAILED  ((void *) -1)


struct cuckoo_hash_item
{
  const void *key;
  size_t key_len;
  void *value;
};


struct _cuckoo_hash_elem;


struct cuckoo_hash
{
  struct _cuckoo_hash_elem *table;
  size_t count;
  unsigned int bin_size;
  unsigned char power;
};


#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */


/*
  cuckoo_hash_init(hash, power):

  Initialize the hash.  power controls the initial hash table size,
  which is (bin_size << power), i.e., 4*2^power.  Zero means one.

  Return true on success, false if initialization failed (memory
  exhausted).
*/
bool
cuckoo_hash_init(struct cuckoo_hash *hash, unsigned char power);


/*
  cuckoo_hash_destroy(hash):

  Destroy the hash, i.e., free memory.
*/
void
cuckoo_hash_destroy(const struct cuckoo_hash *hash);


/*
  cuckoo_hash_count(hash):

  Return number of elements in the hash.
*/
static inline
size_t
cuckoo_hash_count(struct cuckoo_hash *hash)
{
  return hash->count;
}


/*
  cuckoo_hash_insert(hash, key, key_len, value):

  Insert new value into the hash under the given key.

  Return NULL on success, or the pointer to the existing element with
  the same key, or the constant CUCKOO_HASH_FAILED when operation
  failed (memory exhausted).  If you want to replace the existing
  element, assign the new value to result->value.  You likely will
  have to free the old value, and a new key, if they were allocated
  dynamically.
*/
struct cuckoo_hash_item *
cuckoo_hash_insert(struct cuckoo_hash *hash,
                   const void *key, size_t key_len, void *value);


/*
  cuckoo_hash_lookup(hash, key, key_len):

  Lookup given key in the hash.

  Return pointer to struct cuckoo_hash_item, or NULL if the key
  doesn't exist in the hash.
*/
struct cuckoo_hash_item *
cuckoo_hash_lookup(const struct cuckoo_hash *hash,
                   const void *key, size_t key_len);


/*
  cuckoo_hash_remove(hash, hash_item):

  Remove the element from the hash that was previously returned by
  cuckoo_hash_lookup() or cuckoo_hash_next().

  It is safe to pass NULL in place of hash_item, so you may write
  something like

    cuckoo_hash_remove(hash, cuckoo_hash_lookup(hash, key, key_len));

  hash_item passed to cuckoo_hash_remove() stays valid until the next
  call to cuckoo_hash_insert() or cuckoo_hash_destroy(), so if you
  allocated the key and/or value dynamically, you may free them either
  before or after the call (they won't be referenced inside):

    struct cuckoo_hash_item *item = cuckoo_hash_lookup(hash, k, l);
    free((void *) item->key);
    cuckoo_hash_remove(hash, item);
    free(item->value);

  (that (void *) cast above is to cast away the const qualifier).
*/
void
cuckoo_hash_remove(struct cuckoo_hash *hash,
                   const struct cuckoo_hash_item *hash_item);


/*
  cuckoo_hash_next(hash, hash_item):

  Get the next hash item.  Pass NULL as the hash_item on the first
  call, and the result of the previous call on subsequent calls.
  Normally you do not call this function directly, but use
  cuckoo_hash_each() loop instead.
*/
struct cuckoo_hash_item *
cuckoo_hash_next(const struct cuckoo_hash *hash,
                 const struct cuckoo_hash_item *hash_item);


/*
  cuckoo_hash_each(it, hash):

  Iterate over all elements in the hash.  it is an iterator variable
  of type struct cuckoo_hash_item *.  To be used as

    struct cuckoo_hash_item *it;
    ...
    for (cuckoo_hash_each(it, hash))
      {
        // work with it.
      }

  or as

    for (struct cuckoo_hash_item *cuckoo_hash_each(it, hash))
      {
        // work with it.
      }

  to make it local to the loop.

  It is safe to modify it->value (but do not change it->key or
  it->key_len), or to call cuckoo_hash_remove(hash, it).

  Calling cuckoo_hash_insert() inside the loop will reorder the
  elements so that some may then be visited twice, while others
  (including the new one) may not be visited at all.  In other words,
  don't do this.
*/
#define cuckoo_hash_each(it, hash)              \
  (it) = cuckoo_hash_next((hash), NULL);        \
  (it) != NULL;                                 \
  (it) = cuckoo_hash_next((hash), (it))


#ifdef __cplusplus
}      /* extern "C" */
#endif  /* __cplusplus */


#endif  /* ! _CUCKOO_HASH_H */
