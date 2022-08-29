#include <stdlib.h>
#include <stdbool.h>
#include "symtab.h"
#include "mem.h"
#include "assert.h"
#include "table.h"
#include "seq.h"
#include "array.h"
#include <stdio.h>
/******************************************************************************/
const int TABLE_SIZEHINT = 100;  //Estimated number of variables in average
                                 //Asteroid program.
const int SCOPES_SIZEHINT = 10;  //estimated scope depth for average Asteroid 
                                 //program.
int curr_scope = 0;
/******************************************************************************/
#define T SymTab_T
struct T {
	// global scope dictionary must always be present
	Seq_T scoped_symtab;
	Seq_T globals;
	Table_T global_scope; // reference to global dictionary
};
/******************************************************************************/
T SymTab_new() {
	// Initialize structures
	T symbol_table = malloc( sizeof( struct T ));
	Table_T namespace = Table_new(TABLE_SIZEHINT, NULL, NULL);
	Table_T gnamespace = Table_new(TABLE_SIZEHINT, NULL, NULL);
	Seq_T initial_scope = Seq_new(SCOPES_SIZEHINT);
	Seq_T initial_global = Seq_new(SCOPES_SIZEHINT);
	assert(namespace);
	assert(gnamespace);
	assert(initial_scope);
	assert(initial_global);

	//assemble symtab structure
	Seq_addlo(initial_scope,namespace);
	Seq_addlo(initial_global,gnamespace);
	symbol_table->global_scope = gnamespace;
	symbol_table->scoped_symtab = initial_scope;
	symbol_table->globals = initial_global;

	return symbol_table;
}
/******************************************************************************/
void SymTab_enterSym(T symbol_table, const void *key, void *value){

	assert(symbol_table);
	assert(key);
	// Value can legally be NULL/ no need to assert

	Table_T namespace = Seq_get( symbol_table->globals, curr_scope);

	// Check if it already exists in global table
	void * oldValue = Table_get( Seq_get( symbol_table->globals, curr_scope), key);
	if (oldValue == NULL) {
		namespace = Seq_get( symbol_table->scoped_symtab, curr_scope);
	}
	Table_put(namespace,key,value);
}
/******************************************************************************/
Table_T SymTab_findSym(T symbol_table, const void *key){
	assert(symbol_table);
	assert(key);
	int i,n_scopes;
	Table_T namespace = NULL;
	void *value = NULL;

	n_scopes = Seq_length( symbol_table->scoped_symtab );

	for(i = 0;i < n_scopes;++i){
		namespace = Seq_get( symbol_table->scoped_symtab, i );
		value = Table_get(namespace,key);
		if (value){
			return namespace;	
		}
	}
	return NULL;
}
/******************************************************************************/
void *SymTab_lookupSym(T symbol_table, const void *key, bool strict){

	Table_T namespace = SymTab_findSym(symbol_table, key);
	if (!namespace){
		if (strict){
			// **TODO ERROR SYMBOL NOT FOUND ON STRICT
			fprintf(stderr,"Error, %s not found.\n", (char*)key);
		}
		return NULL;
	}
	return Table_get(namespace,key);
}
/******************************************************************************/
// find the first occurence of sym and update the associated value
void SymTab_updateSym(T symbol_table, const void *key, void *value){

	Table_T namespace = SymTab_findSym(symbol_table, key);
	if (namespace == NULL){
		// **TODO ERROR SYMBOL NOT FOUND ON UPDATE
		return;
	} else {
		Table_put(namespace, key, value);
	}
}
/******************************************************************************/
// push a new dictionary and globals lookup onto the sequences - seqs grow to 
// the left
void SymTab_pushScope(T symbol_table, Table_T scope){
	Seq_addlo( symbol_table->scoped_symtab, scope );
	Seq_addlo( symbol_table->globals, Table_new( TABLE_SIZEHINT,NULL,NULL ));
}
/******************************************************************************/
// pop the left most dictionary off the sequence
Table_T SymTab_popScope(T symbol_table){
	int n_scopes = Seq_length( symbol_table->scoped_symtab );
	if (n_scopes == 1){
		// **TODO ERROR POP BASE SCOPE
		fprintf(stderr,"Error, cannont pop the base/global scope.\n");
		return NULL;
	} else {
		Seq_remlo(symbol_table->globals);
		return Seq_remlo(symbol_table->scoped_symtab);
	}
}
/******************************************************************************/
bool SymTab_isSymbolLocal(T symbol_table, const void *key){
	void *value = Table_get( Seq_get(symbol_table->scoped_symtab, curr_scope), key );
	if (value){
		return true;
	} else {
		return false;
	}
}
/******************************************************************************/
bool SymTab_isSymbolGlobal(T symbol_table, const void *key){
	void *value = Table_get( Seq_get(symbol_table->globals, curr_scope), key );
	if (value){
		return true;
	} else {
		return false;
	}
}
/******************************************************************************/
// enter the symbol in the global table at the appropriate scope
void SymTab_enterGlobal(T symbol_table, const void *key){
	Table_put( Seq_get( symbol_table->globals, curr_scope), key, (int*)1 );
}
/******************************************************************************/
// Development tool
// dumps entire contents of symbol table to console in text format.
void SymTab_dumb(T symbol_table){
	int i,j,scope_length;
	int n_scopes = Seq_length( symbol_table->scoped_symtab );
	void **scope_dump = NULL;
	printf("*****************************************\n");
	printf("* * *       SYMBOL TABLE DUMP       * * *\n");
	printf("*****************************************\n");
	printf("**** TABLE SCOPE LEVEL %d\n",curr_scope);
	for (i=0; i < n_scopes; ++i){
		printf("*****************************************\n");
		printf("**** GLOBAL SCOPE: %d\n",i);
		scope_length = 2 * Table_length( Seq_get( symbol_table->globals, i));
		scope_dump = Table_toArray( Seq_get( symbol_table->globals, i), NULL);
		for (j=0; j<scope_length; j += 2){
			printf("* ID: %s \t\tVALUE: %f\n",(char*)scope_dump[j],*(double*)scope_dump[j+1]);
		}
		if (scope_length == 0){
			printf("* \n");
		}
		printf("**** LOCAL SCOPE: %d\n",i);
		scope_length = 2 * Table_length( Seq_get( symbol_table->scoped_symtab, i));
		scope_dump = Table_toArray( Seq_get( symbol_table->scoped_symtab, i), NULL);
		for (j=0; j<scope_length; j += 2){
			printf("*ID: %s \t\tVALUE: %f\n",(char*)scope_dump[j],*(double*)scope_dump[j+1]);
		}
		if (scope_length == 0){
			printf("* \n");
		}
	}
	printf("*****************************************\n");
}