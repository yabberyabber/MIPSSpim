CPP=gcc
CPPFLAGS=-Wall

DEPS=Lexer.o SymbolTable.o Tokenizer.o Instruction.o

TARGET=assemble

it: $(DEPS)
	$(CPP) $(CPPFLAGS) Assemble.c $(DEPS) -o $(TARGET)

%.o: %.c %.h
	$(CPP) $(CPPFLAGS) -c $<

clean:
	touch $(TARGET)
	touch a.o
	rm *.o $(TARGET)

tests: it testToken testLexer

testToken: it
	cp util.h Tokenizer.c Tokenizer.h Instruction.c Instruction.h tests/tokenizer/
	cd tests/tokenizer; ./runtests

testLexer: it
	cp util.h Lexer.c Lexer.h Tokenizer.c Tokenizer.h Instruction.c Instruction.h tests/lexer/
	cd tests/lexer; ./runtests

testSymTb: it
	cp SymbolTable.c SymbolTable.h tests/symbolTable/
	cd tests/symbolTable; ./runtests
