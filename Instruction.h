#ifndef	_INSTRUCTION_H
#define _INSTRUCTION_H

#define R_INSTR 		1
#define I_INSTR 		2
#define J_INSTR 		3
#define P_INSTR 		4

int IsInstruction(char *str);
int IsRTypeInstruction(char *str);
int IsITypeInstruction(char *str);
int IsJTypeInstruction(char *str);
int IsPTypeInstruction(char *str);

int getCodes(char* str);

#endif
