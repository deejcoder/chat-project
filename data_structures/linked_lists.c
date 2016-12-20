#include "linked_lists.h"

//ERROR HANDLING - here temp till error handling sorted
void RaiseMemoryError() {
	perror( "RaiseMemoryError: Unable to allocate enough memory for list." );
	exit( EXIT_FAILURE );
}

void RaiseIndexError() {
	perror( "Invalid index was passed to linked list." );
	exit( EXIT_FAILURE );
}


list *list_init() {
	//create a new list
	list *l;
	l = malloc( sizeof( list ) );
	
	if( l == NULL ) {
		RaiseMemoryError();
	}

	//allocate memory for head, last nodes.
	l->head = malloc( sizeof( struct node ) );
	l->last = malloc( sizeof( struct node ) );

	if( l->head == NULL || l->last == NULL ) {
		RaiseMemoryError();
	}
	return l;
}

int push( list *l, int val ) {
	//add a new node
	struct node *n;
	n = malloc( sizeof( struct node ) );
	if( n == NULL ) {
		RaiseMemoryError();	
	}
	
	//set the node's value
	n->value = val;
	
	//if list empty, set head.
	if( l->size == 0 ) {
		l->head = n;
		l->last = n;
	}
	else {
		/* insert at the end, set last to n
		*/
		l->last->next = n;
		l->last = n;
	}
	l->size++;
	return val;
}

int removefirst( list *l ) {
	//free l->head, make the next the head
	int val = l->head->value;
	free( l->head );
	l->head = l->head->next;
	return val;
}

int list_free( list *l, int index ) {
	if( index == 0 ) removefirst( l );
	if( index < 0 ) RaiseIndexError();
	/*	prev	current		current->next
		[v|n]	->[v|n]		->[v|n] 
	*/
	struct node *current = l->head;
	struct node *prev = NULL;
	
	int count = 0; int value;
	
	//iter through all nodes
	while( current != NULL ) {
		
		if( count == index ) {
			
			value = current->value;
			struct node *tmp = current;
			free( current );
			//move current-> to prev->next
			prev->next = tmp;
			
			//if last, set to last
			if( current == l->last ) {
				l->last = tmp;	
			}
			return value;
		}
		prev = current;
		current = current->next;
		count++;
	}
	return -1;
}

void main() {}
