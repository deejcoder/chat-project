#include "htables.h"

htable *htable_init( size_t size ) {
	struct htable *ht;
	ht = malloc( sizeof( struct htable ) );
	
	ht->arr_size = size;
	
	for( int slot; slot < size; slot++ )  {
		ht->arr[slot] = list_init();
	}

	return ht;
}

int ht_insert( htable *h, int key, int data ) { 
	#ifndef hash
	perror( "No hash function is defined." );
	#else
	int hkey = hash( key );
	if( hkey < 0 || hkey >= h->arr_size ) {
		perror( "Index out of bounds." );
	}
	list_push( h->arr[hkey], key, data );
	#endif
	
	return 1;
}

int ht_search( htable *h, int key ) { //searches for key, returns key's data.
	#ifndef hash
	perror( "No hash function is defined."  );
	#else
	int hkey = hash( key );
	if( hkey < 0 || hkey >= h->arr_size ) {
		perror( "Index out of bounds." );	
	}
	return list_search( h->arr[hkey], key );
	#endif
	return 1;
}
