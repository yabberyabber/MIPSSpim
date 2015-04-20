#include "stdio.h"

#include "Tokenizer.h"

int main(int argc, char **argv) {
	Token *tok;
	void *tokenizer;

	tokenizer = TokenizerInit();

	while (TokenGet(tokenizer, &tok) == 0) {
		printf("(%d, |%s|)\n", tok->type, tok->st);
	}

	TokenizerDestroy(tokenizer);

	printf("ende\n");
	return 0;
}
