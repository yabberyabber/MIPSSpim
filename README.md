# MIPSSpim
Lab 3 for CSC 315

I'm pretty sure throughout the quarter Retz will have us add more and more functionality to this assembler so let's continue using this repo.  Also I'm pretty sure he's going to have us write a mips assembly interpretor and I think that should go here.  

I put all the specs we have so far (that pdf) in the specs directory.  

Here's my proposed organization (let me know what you think cuz I'm not like the king or anything):
 * Assemble.c has the main in it which starts the first pass then starts the second pass.
 * Parser.c/h does the first pass.  It reads through the program text and returns an array of structs where every struct represents a label or an instruction
 * SymbolTable is pretty much an associative array... you put in symbols and their address and then you can get an address given a symbol (this is useful for pass 2)
 * CodeGenerator is pass 2.  It takes the results of pass 1 and goes line by line and outputs some code every time
 * I guess maybe assemble.c gets that code and outputs it or something?  
 
Let me know what you think; I tried to organize it as similarly to lzw as possible but I don't know if that's a good thing or a bad thing... After I finish some homework this afternoon I'll start filling out the header files .  
