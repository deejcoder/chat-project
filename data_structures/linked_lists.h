#include <stdlib.h>
#include <stdio.h>

#ifndef LIST_H
#define LIST_H

//should we have a "key"?
struct node {
	int value;
	struct node *next;
};

typedef struct list {
	size_t size;
	struct node *head;
	struct node *last;
} list;

//============[Forwards]===========

list *list_init();

int push( list *l, int val );

int removefirst( list *l );

int list_free( list *l, int index );

//=================================

#endif
