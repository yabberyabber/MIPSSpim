#ifndef	_INSTRUCTION_C
#define _INSTRUCTION_C

#include "string.h"

#include "Instruction.h"

#define	NUM_R_INSTR		10
#define NUM_I_INSTR		9
#define NUM_J_INSTR		2
#define NUM_P_INSTR		1

const char *R_INSTRUCTIONS[] = {"and", "or", "add", "addu", "sll", "srl", "sra", "sub", "sltu", "jr"};
const int R_OPCODES[] = {0,0,0,0,0,0,0,0,0,0};
const int R_FUNC_CODES[] = {0x24,0x25,0x20,0x21,0x00,0x02,0x03,0x22,0x2B,0x08};
const char *I_INSTRUCTIONS[] = {"addi", "addiu", "sltiu", "beq", "bne", "lw", "sw", "ori", "lui"};
const int I_OPCODES[] = {0x08,0x09,0x0B,4,5,0x23,0x2B, 0X0D, 0x0F};
const char *J_INSTRUCTIONS[] = {"j", "jal"};
const int J_OPCODES[] = {0x02,0x03};
const char *P_INSTRUCTIONS[] = {"syscall"};
const int P_OPCODES[] = {0xC};

int IsRTypeInstruction(char *str) {
	int i;

	for (i = 0; i < NUM_R_INSTR; i++) {
		if (strcmp(R_INSTRUCTIONS[i], str) == 0)
			return R_INSTR;
	}
	return 0;
}

int IsITypeInstruction(char *str) {
	int i;

	for (i = 0; i < NUM_I_INSTR; i++) {
		if (strcmp(I_INSTRUCTIONS[i], str) == 0)
			return I_INSTR;
	}
	return 0;
}

int IsJTypeInstruction(char *str) {
	int i;

	for (i = 0; i < NUM_J_INSTR; i++) {
		if (strcmp(J_INSTRUCTIONS[i], str) == 0)
			return J_INSTR;
	}
	return 0;
}

int IsPTypeInstruction(char *str) {
	int i;

	for (i = 0; i < NUM_P_INSTR; i++) {
		if (strcmp(P_INSTRUCTIONS[i], str) == 0)
			return P_INSTR;
	}
	return 0;
}

int getCodes(char* str) {
	int i, ret;
	int func = 0;
	if(IsRTypeInstruction(str)) {
		for(i = 0; i < NUM_R_INSTR; i++) {
			if (strcmp(R_INSTRUCTIONS[i], str) == 0){
        	                ret = R_OPCODES[i];
				func = R_FUNC_CODES[i];
			}
        }
	}
	else if(IsITypeInstruction(str)) {
                for(i = 0; i < NUM_I_INSTR; i++) {
                        if (strcmp(I_INSTRUCTIONS[i], str) == 0)
                                ret = I_OPCODES[i];
                }
        }
	else if(IsJTypeInstruction(str)) {
                for(i = 0; i < NUM_J_INSTR; i++) {
                        if (strcmp(J_INSTRUCTIONS[i], str) == 0)
                                ret = J_OPCODES[i];
                }
        }
	else if(IsPTypeInstruction(str)) {
                for(i = 0; i < NUM_P_INSTR; i++) {
                        if (strcmp(P_INSTRUCTIONS[i], str) == 0)
                                ret = P_OPCODES[i];
                }
        }
	else { return -1; }


	ret = ret << 27;
	ret = ret | func;
	return ret;
}

int IsInstruction(char *str) {
	return IsRTypeInstruction(str) |
		IsITypeInstruction(str) |
		IsJTypeInstruction(str) |
		IsPTypeInstruction(str);
}

#endif
