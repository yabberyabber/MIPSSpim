#include "stdio.h"

#include "Lexer.h"

int main(int argc, char **argv) {
	Lexeme *lex;
	void *lexer;
	int i;

	lexer = LexerInit();

	while (LexerGetLexeme(lexer, &lex) == 0) {
		printf("%d: (%s", lex->type,
				lex->opcode->st);
		for (i = 0; i < 4; i++)
			if (lex->args[i] != NULL)
				printf(", |%s|", lex->args[i]->st);
		printf(")\n");
	}

	LexerDestroy(lexer);

	printf("ende\n");
	return 0;
}
