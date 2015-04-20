#ifndef	_INSTRUCTION_C
#define _INSTRUCTION_C

#include "string.h"

#include "Instruction.h"

#define	NUM_R_INSTR		13
#define NUM_I_INSTR		2
#define NUM_J_INSTR		2
#define NUM_P_INSTR		1

const char *R_INSTRUCTIONS[] = {"and", "or", "add", "addu", "sll", "srl", "sra", "sub", "sltu", "beq", "bne", "lw", "sw"};
const char *I_INSTRUCTIONS[] = {"addi", "addiu", "sltiu"};
const char *J_INSTRUCTIONS[] = {"j", "jal"};
const char *P_INSTRUCTIONS[] = {"syscall"};

int IsInstruction(char *str) {
	int i;

	for (i = 0; i < NUM_R_INSTR; i++) {
		if (strcmp(R_INSTRUCTIONS[i], str) == 0)
			return 1;
	}

	for (i = 0; i < NUM_I_INSTR; i++) {
		if (strcmp(I_INSTRUCTIONS[i], str) == 0)
			return 1;
	}

	for (i = 0; i < NUM_J_INSTR; i++) {
		if (strcmp(J_INSTRUCTIONS[i], str) == 0)
			return 1;
	}

	for (i = 0; i < NUM_P_INSTR; i++) {
		if (strcmp(P_INSTRUCTIONS[i], str) == 0)
			return 1;
	}

	return 0;
}

#endif
