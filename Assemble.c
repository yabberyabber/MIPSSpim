/**
 * This file should contain a main.
 *
 * In the first pass, the lexer takes the text of the program and returns
 * a long list of lexemes (each lexeme represents an instruction).
 *
 * In the second pass, the code generator takes the lexemes from the first
 * pass and returns 1's and 0's.
 */

#include "stdlib.h"
#include "stdio.h"

#include "Lexer.h"
#include "CodeGenerator.h"
#include "SymbolTable.h"

#define MEM_SIZE		32000

typedef struct lexNode {
	Lexeme *lex;
	struct lexNode *next;
} lexNode;

void prettyPrintLexeme(Lexeme *lex) {
	int i;
	printf("%d: (%s", lex->address,
		lex->opcode->st);
	for (i = 0; i < 4; i++)
		if (lex->args[i] != NULL)
			printf(", (|%s| (%d), %d)", lex->args[i]->st, 
					lex->args[i]->num, lex->args[i]->type);
	printf(")\n");
}

lexNode *GenerateLexemeList(void *symTb) {
	void *lexer;
	Lexeme *lex;
	lexNode *head = NULL;
	lexNode *cur = NULL;

	lexer = LexerInit();

	while (LexerGetLexeme(lexer, &lex, symTb) == 0) {
		prettyPrintLexeme(lex);
		lexNode *new = malloc(sizeof(lexNode));
		new->lex = lex;
		new->next = NULL;

		if (head == NULL) {
			head = cur = new;
		}
		else {
			cur->next = new;
			cur = new;
		}
	}

	LexerDestroy(lexer);

	return head;
}

int *GenerateCodeSegmentArray(lexNode *head, void *symTb) {
	int *mem = malloc(sizeof(int) * MEM_SIZE);
	int status, instr;

	while (head) {
		prettyPrintLexeme(head->lex);
		status = CGGenerateInstruction(symTb, head->lex, &instr);
		printf("yay I generated a code!: %X\n", instr);
		if (status) {
			printf("Ran into the following error during code generation: %d\n",
					status);
			return NULL;
		}
		mem[head->lex->address / 4] = instr;

		head = head->next;
	}
	return mem;
}

int main(int argc, char **argv) {
	void *symTb = SymTbInit();
	lexNode *head = GenerateLexemeList(symTb);
	int *mem = GenerateCodeSegmentArray(head, symTb);

	if (mem == NULL)
		return 1;

	return 0;
}
