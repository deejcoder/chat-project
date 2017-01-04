//Hash tables.

#include <stdlib.h>
#include <stdio.h>

#ifndef HASH_H
#define HASH_H

#include "linked_lists.h"
#include "linked_lists.c"

#ifndef hash
#define hash(K) K % 7 //just for testing with table size 11
#endif

typedef struct htable {
	size_t arr_size;
	struct list *arr[];
} htable;

int ht_insert( htable *h, int key, int data );
int ht_search( htable *h, int key );
//int ht_remove( htable *h, int key );

#endif
