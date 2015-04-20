#ifndef	_SYMBOL_TABLE_C
#define _SYMBOL_TABLE_C

#include "SymbolTable.h"

//If we're gonna be super proper this struct should probably be in the .h
typedef struct SymbolTable {
	//idk maybe like a linked list or an array like CodeSets
} SymbolTable;

/**
 * Just like CodeSets, get your SymbolTable by taking it from here.
 */
void *SymTbInit() {return 0;}
void SymTbDestroy(void *simtb) {}

/**
 * Insert a symbol into the table with a corresponding value.  (if this were
 * python, it could just be like dict[name] = val but we ain't about that).
 * Return 0 normally and anything else in case of error.
 */
int SymTbInsert(void *simtb, char *name, int val) {return 0;}

/**
 * Look up a symbol in the table and find the value associated with it.
 * Return 0 normally and anything else in case of error.
 */
int SymTbLookup(void *simtb, char *name, int *val) {return 0;}

#endif
