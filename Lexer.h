#ifndef _DEFINE_LEXER_H
#define _DEFINE_LEXER_H
/**
 * This file takes tokens from the Tokenizer and groups them together
 * into lexemes (labels, I instructions, R instructions, S instructions, etc)
 * Which it returns one-by-one.
 *
 * This file is also responsible for registering labels in the Symbol Table and
 * expanding pseudo-instructions.
 */

#include "Tokenizer.h"

typedef struct Lexeme {
	int address;
	int type;
	Token *opcode;
	Token *args[5];
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
int LexerGetLexeme(void *lexer, Lexeme **lexeme);

#endif
