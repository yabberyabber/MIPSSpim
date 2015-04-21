CPP=gcc
CPPFLAGS=-Wall

DEPS=SymbolTable.o

TARGET=driver

it: $(DEPS)
	$(CPP) $(CPPFLAGS) symTbDriver.c $(DEPS) -o $(TARGET)

%.o: %.c %.h
	$(CPP) $(CPPFLAGS) -c $<

clean:
	touch $(TARGET)
	touch a.o
	rm *.o $(TARGET)
