#include "CodeGenerator.h"
#include "Instruction.h"
#include "SymbolTable.h"
#include "Tokenizer.h"

int CGGenerateInstruction(CodeGenerator *cg, SymbolTable *symTb,
 Lexeme *command, int *machineCode){
 	char *str = command->opcode->st;
 	int func = IsInstruction(str);
 	*command = getfuncopcode(str, func);
 	/**switch(func){
 		
 	}*/
}