#ifndef	_TOKENIZER_CPP
#define _TOKENIZER_CPP
/**
 * This module tokenizes input.  It is responsible for reading from stdin, 
 * discarding comments, discarding comments, and returning one string at
 * time (super simple).
 */

#include "stdlib.h"
#include "stdio.h"
#include "string.h"

#include "util.h"

#include "Instruction.h"
#include "Tokenizer.h"

typedef struct Tokenizer {
	char *inputLine;
	int endFile;
} Tokenizer;

void *TokenizerInit() {
	//We're reading from stdin so no need to open any file handles
	Tokenizer *tk = malloc(sizeof(Tokenizer));
	tk->inputLine = NULL;
	tk->endFile = 0;

	return tk;
}

void TokenizerDestroy(void *tk) {
	free(tk);
}

void TokenEndln(Token **token) {
	*token = malloc(sizeof(Token));
	(*token)->type = TOKEN_ENDL;
	(*token)->st = NULL;
}

/**
 * if the given string |str| can be parsed into
 * a 10 or 16 bit int, then ret is set to it's value
 * and 1 is returned.  Otherwise (like if |str| is non-numeric),
 * 0 is returned and ret is set to 0.
 */
static int parseInt(char *str, int *ret) {
	int result;
	char *err;

	//try base ten
	result = strtol(str, &err, 10);
	if (*err == '\0') {
		*ret = result;
		return 1;
	}

	//try base 16
	result = strtol(str, &err, 16);
	if (*err == '\0') {
		*ret = result;
		return 1;
	}
	*ret = 0;
	return 0;
}

void TokenGenerate(char *tokenStr, Token **token) {
	*token = malloc(sizeof(Token));
	tokenStr = TrimString(tokenStr);

	if (tokenStr[strlen(tokenStr) - 1] == ':') {
		//Token ends with ':' so it must be a label
		(*token)->type = TOKEN_LABEL_DEF;
		(*token)->st = malloc(sizeof(char) * strlen(tokenStr) + 1);
		strcpy((*token)->st, tokenStr);
		(*token)->st[strlen(tokenStr) - 1] = 0;
	}
	else if (tokenStr[0] == '.') {
		//token starts with '.' so it must be an assembler directive
		(*token)->type = TOKEN_DIRECTIVE;
		(*token)->st = malloc(sizeof(char) * strlen(tokenStr));
		strcpy((*token)->st, tokenStr + 1);
	}
	else if (IsInstruction(tokenStr)) {
		//token is in the list of instructions
		(*token)->type = TOKEN_OPCODE;
		(*token)->st = malloc(sizeof(char) * strlen(tokenStr) + 1);
		strcpy((*token)->st, tokenStr);
	}
	else {
		//token is none of the above... default to argument
		(*token)->type = TOKEN_ARG;
		if (parseInt(tokenStr, &((*token)->num))) {
			(*token)->st = NULL;
		}
		else {
			(*token)->st = malloc(sizeof(char) * strlen(tokenStr) + 1);
			strcpy((*token)->st, tokenStr);
		}
	}
}

/**
 * GetToken grabs a single word from stdin and puts a pointer to it in |token|.
 * It returns 0 normally, 1 in case of error (idk what kind of errors
 * there'd be), and -1 in case of EOF.
 */
int TokenGet(void *tkp, Token **token) {
	int read;
	size_t len;
	char *tokenStr;
	Tokenizer *tk = (Tokenizer *) tkp;

	if (tk->inputLine == NULL) {
		read = getline(&(tk->inputLine), &len, stdin);
		if (read == -1)
			return -1;
		printf("read input line: |%s|\n", tk->inputLine);

		if (strlen(tk->inputLine) < 1) {
			tokenStr = "#";
		}
		else
			tokenStr = strtok(tk->inputLine, ", \t\n");
	}
	else {
		tokenStr = strtok(NULL, ", \t\n");
	}

	if (tokenStr == NULL || tokenStr[0] == '#' || tokenStr[0] == '\n') {
		free(tk->inputLine);
		tk->inputLine = NULL;
		TokenEndln(token);
		return 0;
	}

	TokenGenerate(tokenStr, token);

	return 0;
}


#endif
