#ifndef	_SYMBOL_TABLE_C
#define _SYMBOL_TABLE_C

#include "stdlib.h"
#include "string.h"

#include "SymbolTable.h"

#define SYMBOL_TABLE_MAX_SIZE		200

typedef struct SymbolEntry {
	char *name;
	int address;
} SymbolEntry;

//If we're gonna be super proper this struct should probably be in the .h
typedef struct SymbolTable {
	int size;
	SymbolEntry *head;
} SymbolTable;

/**
 * Just like CodeSets, get your SymbolTable by taking it from here.
 */
void *SymTbInit() {
	SymbolTable *symTb = malloc(sizeof(SymbolTable));

	symTb->head = malloc(sizeof(SymbolEntry) * SYMBOL_TABLE_MAX_SIZE);
	symTb->size = 0;

	return symTb;
}
void SymTbDestroy(void *symTb) {
	SymbolTable *tb = (SymbolTable*) symTb;

	free(tb->head);
	free(tb);
}

/**
 * Insert a symbol into the table with a corresponding value.  (if this were
 * python, it could just be like dict[name] = val but we ain't about that).
 * Return 0 normally and anything else in case of error.
 */
int SymTbInsert(void *symTb, char *name, int val) {
	SymbolTable *tb = (SymbolTable*) symTb;
	SymbolEntry *newSym = tb->head + tb->size;

	if (tb->size >= SYMBOL_TABLE_MAX_SIZE)
		return -1;

	newSym->name = name;
	newSym->address = val;
	tb->size++;

	return 0;
}

/**
 * Look up a symbol in the table and find the value associated with it.
 * Return 0 normally and anything else in case of error.
 */
int SymTbLookup(void *symTb, char *name, int *val) {
	int i;
	SymbolTable *tb = (SymbolTable*) symTb;
	SymbolEntry *sym = tb->head;

	for (i = 0; i < tb->size; i++) {
		if (strcmp((sym + i)->name, name) == 0) {
			*val = (sym + i)->address;
			return 0;
		}
	}
	return 1;
}

#endif
