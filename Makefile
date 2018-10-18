# ADDBRA001 Makefile Template

## FLAGS ==================================================================
CC=g++ -std=c++11
LIBS=-lm
## ========================================================================

ann4: ann4.o
	$(CC) ann4.o -o ann4 $(LIBS)


ann4.o: ann4.cpp
	$(CC) -c ann4.cpp

clean:
	@rm -f *.o
	@rm ann4

install:

	@mv ann4 ~/bin
