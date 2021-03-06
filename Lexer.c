#ifndef _DEFINE_LEXER_C
#define _DEFINE_LEXER_C
/**
 * This file takes tokens from the Tokenizer and groups them together
 * into lexemes (labels, I instructions, R instructions, S instructions, etc)
 * Which it returns one-by-one.
 *
 * This file is also responsible for registering labels in the Symbol Table and
 * expanding pseudo-instructions.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "Lexer.h"
#include "Tokenizer.h"
#include "SymbolTable.h"
#include "Instruction.h"

#define TEXT_START_ADDRESS		0x0000

/**
 * lQueue is a que of lexemes.  In the event of a pseudo instruction, having
 * 		a que lets us expand that pseudo instruction and save all the resulting
 * 		instructions
 * tokenizer is the initialized tokenizer
 * instrAddress is the address of the current instruction.  This is used when
 * 		registering labels
 */
typedef struct Lexer {
	Lexeme *lQueue[3];
	void *tokenizer;
	int instAddress;
	int endReached;
} Lexer;

void *LexerInit() {
	Lexer *l = malloc(sizeof(Lexer));

	l->lQueue[0] = NULL;
	l->lQueue[1] = NULL;
	l->lQueue[2] = NULL;

	l->tokenizer = TokenizerInit();

	l->instAddress = TEXT_START_ADDRESS;

	l->endReached = 0;

	return l;
}
void LexerDestroy(void *lexer) {
	Lexer *l = (Lexer*) lexer;

	TokenizerDestroy(l->tokenizer);
	free(l);
}

static void LexerRegisterLabel(Lexer *l, Token *t, void *symTb) {
#ifdef DBG
	printf("Registering label: |%s| at addr %d\n",
			token->st, l->instAddress);
#endif
	SymTbInsert(symTb, t->st, l->instAddress);
}

/**
 * return the first thing on the lexer's queue and shit
 * everything forward (later this might need to be replaced
 * with an actual queue of variable size, but this should do for
 * now).
 */
static Lexeme *LexerQueuePop(Lexer *l) {
	Lexeme *ret = l->lQueue[0];
	l->lQueue[0] = l->lQueue[1];
	l->lQueue[1] = l->lQueue[2];
	l->lQueue[2] = NULL;
	return ret;
}

static int LexerQueuePush(Lexer *l, Lexeme *v) {
	int i;

	for (i = 0; i < 3; i++) {
		if (l->lQueue[i] == NULL) {
			l->lQueue[i] = v;
			return 0;
		}
	}
	return 1;
}

static void LexerGenerateInstruction(Lexer *l, Token *instruction) {
	int argCount = 0;
	Lexeme *instr = malloc(sizeof(Lexeme));
	Token *arg;

	instr->opcode = instruction;

	while (argCount < 3) {
		TokenGet(l->tokenizer, &arg);
		if (arg->type == TOKEN_ENDL)
			break;
		instr->args[argCount++] = arg;
	}

	instr->address = l->instAddress;
	l->instAddress += 4;

	LexerQueuePush(l, instr);
}

/**
 * We don't actually know how to process any directives, so if one is
 * encountered, we throw away the rest of the line and hope it wasn't
 * important...
 */
static int LexerProcessDirective(Lexer *l, Token *tok) {
	if (strcmp(tok->st, ".end") == 0) {
		l->endReached = 1;
		return 1;
	}

	while (tok->type != TOKEN_ENDL)
		TokenGet(l->tokenizer, &tok);
	return 0;
}


/**
 * Returns a single lexeme (represents a command)
 *
 * In the case of pseudo instructions, this lexer will return the first
 * actual instruction and queue up any later instructions on the Lexer queue.
 * Consequently before creating any lexemes this function should check the
 * queue and return those lexemes first.
 */
int LexerGetLexeme(void *lexer, Lexeme **lexeme, void *symTb) {
	Lexer *l = (Lexer*) lexer;
	Token *tok;
	int status;

	if (l->lQueue[0] != NULL) {
		*lexeme = LexerQueuePop(l);
	}

	while ((status = TokenGet(l->tokenizer, &tok)) == 0) {
		if (tok->type == TOKEN_LABEL_DEF) {
			LexerRegisterLabel(l, tok, symTb);
		}
		else if (tok->type == TOKEN_OPCODE) {
			LexerGenerateInstruction(l, tok);
			*lexeme = LexerQueuePop(l);
			break;
		}
		else if (tok->type == TOKEN_ARG) {
			printf("argument at beginning of line. bad form, bro\n");
			return -1;
		}
		else if (tok->type == TOKEN_DIRECTIVE) {
			if (LexerProcessDirective(l, tok))
				break;
		}
	}

	if (status == -1 || l->endReached == 1)
		return -1;

	return 0;
}

#endif
