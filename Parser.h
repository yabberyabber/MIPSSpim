/**
 * This module should be able to read input (either from standard in or 
 * a file it shouldn't matter), discard comments and whitespace, and
 * figure out whether the line contains any symbols to register or an
 * instruction to convert (or I guess a pseudoinstruction to deconstruct?)
 * 
 * One possibility could be to have a struct that represents a "line" of code
 * It would have a field saying whether it was a label or an instruction
 * and if it was an instruction the opcode and arguments fields would be 
 * filled out.  
 */
