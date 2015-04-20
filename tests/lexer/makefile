CPP=gcc
CPPFLAGS=-Wall

DEPS=Lexer.o Tokenizer.o Instruction.o

TARGET=driver

it: $(DEPS)
	$(CPP) $(CPPFLAGS) lexerDriver.c $(DEPS) -o $(TARGET)

%.o: %.c %.h
	$(CPP) $(CPPFLAGS) -c $<

clean:
	touch $(TARGET)
	touch a.o
	rm *.o $(TARGET)
