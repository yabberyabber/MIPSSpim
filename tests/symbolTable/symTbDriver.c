#include "stdio.h"

#include "SymbolTable.h"

#define NUM_STRINGS 11
char *strs[] = {"a", "b", "c", "d", "e", "f", "g",
	"asdsadf", "ra4ws", "23f3w", "awawf"};

int main(int argc, char **argv) {
	void *symTb;
	int i;
	int val;

	symTb = SymTbInit();

	for (i = 0; i < NUM_STRINGS; i++) {
		SymTbInsert(symTb, strs[i], 50*i+10);
	}

	for (i = 0; i < NUM_STRINGS; i++) {
		SymTbLookup(symTb, strs[i], &val);
		printf("|%s| => %d\n", strs[i], val);
	}

	SymTbDestroy(symTb);

	printf("ende\n");
	return 0;
}
