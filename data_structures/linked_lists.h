#include <stdlib.h>
#include <stdio.h>

#ifndef LIST_H
#define LIST_H

struct node {
	int key;
	int value;
	struct node *next;
};

typedef struct list {
	size_t size;
	struct node *head;
	struct node *last;
} list;


list *list_init();

int list_push( list *l, int key, int val );

int removefirst( list *l );

int list_free( list *l, int index );

int list_search( list *l, int nkey );

#endif
