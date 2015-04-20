#ifndef CODEGENERATOR_H
#define CODEGENERATOR_H

/**
 * This module does the second pass.
 *
 * It makes use of the symbol table filled out by the lexer, 
 * as well as a lexeme created by the lexer, and returns 1's and 0's.
 */

typedef struct CodeGenerator {
	//I can't imagine what would be needed here
	//but it makes sense to have it
};

void *CGInit();
void CGDestroy(void *codeGenr);

/**
 * Parses the Lexeme |command| (resolving any labels using |symTb|
 * and puts the resulting instruction (represented as a 32-bit int)
 * into |machineCode|.  Returns 0 on success, and non-zero on error.
 */
int CGGenerateInstruction(CodeGenerator *cg, SymbolTable *symTb,
	Lexeme *command, int *machineCode);

#endif