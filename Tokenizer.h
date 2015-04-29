#ifndef	_TOKENIZER_H
#define _TOKENIZER_H
/**
 * This module tokenizes input.  It is responsible for reading from stdin, 
 * discarding comments, discarding comments, and returning one string at
 * time (super simple).
 */

#define 		TOKEN_LABEL_DEF			1
#define			TOKEN_OPCODE			2
#define			TOKEN_ARG				3
#define			TOKEN_ENDL				4
#define			TOKEN_DIRECTIVE			5

typedef struct Token {
	int type;
	char *st;
	int num;
} Token;

void *TokenizerInit();
void TokenizerDestroy(void *tk);

/**
 * GetToken grabs a single word from stdin and puts a pointer to it in |token|.
 * It returns 0 normally, 1 in case of error (idk what kind of errors
 * there'd be), and -1 in case of EOF.
 */
int TokenGet(void *tkp, Token **token);

#endif
