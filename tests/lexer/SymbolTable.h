#ifndef	_SYMBOL_TABLE_H
#define _SYMBOL_TABLE_H

/**
 * Interface should allow inserting and looking up symbols (labels) as they
 * appear in an assembly program.  I'm thinking symbols should just be 
 * associated with a number corresponding to the address they point to
 */

/**
 * Just like CodeSets, get your SymbolTable by taking it from here.
 */
void *SymTbInit();
void SymTbDestroy(void *simtb);

/**
 * Insert a symbol into the table with a corresponding value.  (if this were
 * python, it could just be like dict[name] = val but we ain't about that).
 * Return 0 normally and anything else in case of error.
 */
int SymTbInsert(void *simtb, char *name, int val);

/**
 * Look up a symbol in the table and find the value associated with it.
 * Return 0 normally and anything else in case of error.
 */
int SymTbLookup(void *simtb, char *name, int *val);

#endif
