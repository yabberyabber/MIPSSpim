# MIPSSpim
Lab 3 for CSC 315

I'm pretty sure throughout the quarter Retz will have us add more and more functionality to this assembler so let's continue using this repo.  Also I'm pretty sure he's going to have us write a mips assembly interpretor and I think that should go here.  

I put all the specs we have so far (that pdf) in the specs directory.  

I made a bunch of files and header files planning out how I think this project should work.  Let me know what you think... (I kind of just went through the wikipedia article for compilers and merged it with how lzw was organized to make an lzw-style wikipedia-informed two-pass assembler).  Here's a high level overview:

Assemble.c contains the main function.  It takes the output from pass 1 and feeds it into pass 2.  Then prints the output of pass 2 to stdout.  

# Pass 1
Lexer rules the first pass.  Lexer forces Tokenizer to scan input for labels, opcodes, registers, immediates, etc. (Tokenizer skips over any whitespace and comments) and groups tokens together into lexemes.  A lexeme is a command (an opcode and some arguments).  Lexer also registers any labels in the SymbolTable.

# Pass 2

CodeGenerator rules second pass.  CodeGenerator takes lexemes one by one, resolves any labels using SymbolTable, and outputs 1's and 0's (machine code).
