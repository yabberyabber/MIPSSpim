CPP=gcc
CPPFLAGS=-Wall

DEPS=CodeGenerator.o Lexer.o SymbolTable.o Tokenizer.o

TARGET=assemble

it: $(DEPS)
	$(CPP) $(CPPFLAGS) Assemble.c $(DEPS) -o $(TARGET)

%.o: %.c %.h
	$(CPP) $(CPPFLAGS) -c $<

clean:
	rm *.o $(TARGET)
