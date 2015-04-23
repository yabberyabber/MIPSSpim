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

int CGGenerateInstruction(void *symTb, Lexeme *command, int *machineCode){
	int val;
 	char *str = command->opcode->st;
 	int func = IsInstruction(str);
 	*machineCode = getCodes(str);
 	switch(func){
 		case R_INSTR:
 			if(!strcmp(str, "sll") || !strcmp(str, "srl") || !strcmp(str, "sra")){
 				*machineCode |= getReg(command->args[0]->st) << 10; // rd
 				*machineCode |= getReg(command->args[1]->st) << 15; // rt
 				*machineCode |= atoi(command->args[2]->st) << 5; // shamt
 			}
 			else if(!strcmp(str, "jr")){
 				*machineCode |= getReg(command->args[0]->st) << 20; // rs
 			}
 			else{
 				*machineCode |= getReg(command->args[0]->st) << 10; // rd
 				*machineCode |= getReg(command->args[1]->st) << 20; // rs
 				*machineCode |= getReg(command->args[2]->st) << 15; // rt
 			}
 			break;
 		case I_INSTR:
 			*machineCode |= getReg(command->args[0]->st) << 15; // rt
 			*machineCode |= getReg(command->args[1]->st) << 20; // rs
 			if(!strcmp(str, "beq") || !strcmp(str, "bne")){
 				SymTbLookup(symTb, command->args[2]->st, &val);
 				*machineCode |= (val - command->address) & 0x0000FFFF; // branch address
 			}
 			else
 				*machineCode |= atoi(command->args[2]->st) & 0x0000FFFF; // imm
 			break;
 		case J_INSTR:
 			SymTbLookup(symTb, command->args[0]->st, &val);
 			*machineCode |= val & 0x07FFFFFF; // j address
 			break;
 		case P_INSTR:
 			break;
 	}
 	return 0;
}
