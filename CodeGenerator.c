#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "CodeGenerator.h"
#include "Instruction.h"
#include "SymbolTable.h"
#include "Tokenizer.h"

#define NUM_REG 32
const char *REGISTERS[] = {"$zero", "$at", "$v0", "$v1", "$a0", "$a1", "$a2", "$a3", "$t0", "$t1", "$t2", "$t3", "$t4", "$t5", "$t6", "$t7", "$s0", "$s1", "$s2", "$s3", "$s4", "$s5", "$s6", "$s7", "$t8", "$t9", "$k0", "$k1", "$gp", "$sp", "$fp", "$ra"};

int getReg(char *str){
	int i;
	for(i = 0; i < NUM_REG; i++){
		if(strcmp(REGISTERS[i], str) == 0)
			return i;
	}
	return -1;
}

/**
 * Takes a token (argument), the address of it's instruction, and the symbol 
 * table.  If the token is a label, it resolves the label (using the symbol
 * table and the address) and returns the offset.  Otherwise, the token should
 * represent a number so it returns that.
 */
static int resolveImmediate(Token *tok, int instrAddr, void *symTb) {
	int symbolAddr;

	if (tok->st == NULL)
		return tok->num;

	SymTbLookup(symTb, tok->st, &symbolAddr);
	return symbolAddr - instrAddr;
}

int CGGenerateInstruction(void *symTb, Lexeme *command, int *machineCode){
 	char *str = command->opcode->st;
 	int func = IsInstruction(str);

 	*machineCode = getCodes(str);
 	switch(func){
 		case R_INSTR:
 			if(!strcmp(str, "sll") || !strcmp(str, "srl") || !strcmp(str, "sra")){
 				*machineCode |= getReg(command->args[0]->st) << 11; // rd
 				*machineCode |= getReg(command->args[1]->st) << 16; // rt
 				*machineCode |= resolveImmediate(command->args[2], command->address,
						symTb) << 6; // shamt
 			}
 			else if(!strcmp(str, "jr")){
 				*machineCode |= getReg(command->args[0]->st) << 21; // rs
 			}
 			else{
 				*machineCode |= getReg(command->args[0]->st) << 11; // rd
 				*machineCode |= getReg(command->args[1]->st) << 21; // rs
 				*machineCode |= getReg(command->args[2]->st) << 16; // rt
 			}
 			break;
 		case I_INSTR:
			if (!strcmp(str, "lui")) {
				*machineCode |= getReg(command->args[0]->st) << 16; // rt
				*machineCode |= resolveImmediate(command->args[1], command->address,
						symTb) & 0x0000FFFF;
			}
			else {
				*machineCode |= getReg(command->args[0]->st) << 16; // rt
				*machineCode |= getReg(command->args[1]->st) << 21; // rs
				*machineCode |= resolveImmediate(command->args[2], command->address,
						symTb) & 0x0000FFFF;
			}
 			break;
 		case J_INSTR:
			*machineCode |= resolveImmediate(command->args[0], command->address,
					symTb) & 0x03FFFFFF;
 			break;
 		case P_INSTR:
 			break;
 	}
 	return 0;
}
