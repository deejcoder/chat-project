/* Stack implemented using array */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#ifndef STACK_H
#define STACK_H

struct stack {
	size_t s_size; 		//count of elements in s_arr
	size_t s_data_size; 	//each element in s_arr in bytes
	char *s_arr;
	char *s_top;
};

int stack_init(struct stack *s, size_t data_size);

int push(struct stack *s, void *data);

int pop(struct stack *s, void *data);

int stack_free(struct stack *s);

int push_ex(struct stack *s, void *data, unsigned int count);

int pop_ex(struct stack *s, void *data, unsigned int count);

#endif
