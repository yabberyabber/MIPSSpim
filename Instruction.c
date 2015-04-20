#ifndef	_INSTRUCTION_C
#define _INSTRUCTION_C

#include "string.h"

#include "Instruction.h"

#define	NUM_R_INSTR		13
#define NUM_I_INSTR		2
#define NUM_J_INSTR		2
#define NUM_P_INSTR		1
#define R_INSTR 		1
#define I_INSTR 		2
#define J_INSTR 		3
#define P_INSTR 		4

const char *R_INSTRUCTIONS[] = {"and", "or", "add", "addu", "sll", "srl", "sra", "sub", "sltu", "beq", "bne", "lw", "sw", "jr"};
const char *I_INSTRUCTIONS[] = {"addi", "addiu", "sltiu"};
const char *J_INSTRUCTIONS[] = {"j", "jal"};
const char *P_INSTRUCTIONS[] = {"syscall"};

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

int IsInstruction(char *str) {
	return IsRTypeInstruction(str) ||
		IsITypeInstruction(str) ||
		IsJTypeInstruction(str) ||
		IsPTypeInstruction(str);
}

#endif
