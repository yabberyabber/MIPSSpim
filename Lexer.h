/**
 * This file takes tokens from the Tokenizer and groups them together
 * into lexemes (labels, I instructions, R instructions, S instructions, etc)
 * Which it returns one-by-one.
 *
 * This file is also responsible for registering labels in the Symbol Table and
 * expanding pseudo-instructions.
 */


//this struct should probably go in the .c file
typedef struct Lexer {
	//should probably have a queue of already generated lexemes to return
	//so that if you are expanding a pseudo instruction you can just push
	//both of them and LexerGetLexeme can return one at a time in a simple
	//fashion.
} Lexer;

typedef struct Lexeme {
	int type;
	int opcode;
	Token args[5];
} Lexeme;

void *LexerInit();
void LexerDestroy(void *lexer);

/**
 * Returns a single lexeme (represents a command)
 *
 * In the case of pseudo instructions, this lexer will return the first
 * actual instruction and queue up any later instructions on the Lexer queue.
 * Consequently before creating any lexemes this function should check the
 * queue and return those lexemes first.
 */
int LexerGetLexeme(void *lexer, Lexeme *lexeme);
