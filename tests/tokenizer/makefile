CPP=gcc
CPPFLAGS=-Wall

DEPS=Tokenizer.o Instruction.o

TARGET=driver

it: $(DEPS)
	$(CPP) $(CPPFLAGS) tokenDriver.c $(DEPS) -o $(TARGET)

%.o: %.c %.h
	$(CPP) $(CPPFLAGS) -c $<

clean:
	touch $(TARGET)
	touch a.o
	rm *.o $(TARGET)
