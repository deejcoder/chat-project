#include "stack.h"


/* Initilize a new stack struct s with the size of each element. returns 1 on sucess -1 otherwise */


int stack_init(struct stack *s, size_t data_size) {
	//s assumed to allocated from caller
	if(data_size <= 0) {
		//TODO: err
	}

	if(s == NULL) {
		//TODO: err
	}

	s->s_data_size = data_size;
	if(!calloc(2, s->s_data_size)) { 
		perror("stack_init");
		return -1; 
	}
	s->s_top = s->s_arr;
	s->s_size = 2;
	return 1;
}

/* Push data onto the stack return 1 on sucess -1 on failure */

int push(struct stack *s, void *data) {
	if(s == NULL || data == NULL) {
		//TODO: err
	}
	
	if( ((s->s_top - s->s_arr) / s->s_data_size) >= s->s_size) {
		char *tmp = realloc(s->s_arr, 2 * s->s_size * s->s_data_size);
		if(tmp == NULL) {
			perror("push realloc");
			return -1;
		}
		s->s_arr = tmp;
	}

	memcpy(s->s_top, data, s->s_data_size);
	s->s_top += s->s_data_size;
	s->s_size++;
	return 1;
}

/* Pop the top of stack and stores in data return 1 on sucess -1 on failure */


int pop(struct stack *s, void *data) {
	if(s == NULL || data == NULL) {
		//TODO: err
	}
	
	if((s->s_top - s->s_arr) <= 0) {
		//TODO: err popping an empty stack
	}
	s->s_top -= s->s_data_size;
	memcpy(data, s->s_top, s->s_data_size);
	s->s_size--;
	return 1;
}

/* Primarity frees s_arr */

int stack_free(struct stack *s) {
	s->s_size = 0;
	s->s_data_size = 0;
	free(s->s_arr);
	s->s_arr = NULL;
	s->s_top = NULL;
	return -1;
}

/* Push count amount of data onto the stack return amount pushed and -1 on failure */

int push_ex(struct stack *s, void *data, unsigned int count) {
	if(count == 0) { return 0; }
	
	if(s == NULL || data == NULL) {
		//TODO: err	
	}
	
	unsigned int pushed = 0;
	char *next = data;
	while(pushed < count) {
		int err = push(s, next);
		if(err < 0) {
			//TODO: err
			return pushed;
		}
		pushed++;
		next += s->s_data_size;
	} 
	return pushed;
}

/* Pop count amount of data from the stack into data return amount popped and -1 on failure */

int pop_ex(struct stack *s, void *data, unsigned int count) {
	if(count == 0) { return 0; }
	
	if(s == NULL || data == NULL) {
		//TODO: err
	}

	if(s->s_size  < count) {
		//TODO: err 
	}
	
	unsigned int popped = 0;
	char *next = data;
	while(popped < count) {
		int err = pop(s, next);
		if(err < 0) {
			//TODO: err
			return popped;
		}
		popped++;
		next += s->s_data_size;
	}

	return popped;	
}

