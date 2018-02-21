CC=gcc
CPP=g++
CFLAGS=-std=c99 -Wall -Wextra -pedantic -o
CPPFLAGS=-std=c++17 -Wall -Wextra -pedantic -o
DEBUGFLAGS=-g

all: xpac

clean:
	-rm xpac
https://stackoverflow.com/questions/2855121/what-is-the-purpose-of-using-pedantic-in-gcc-g-compiler
xpac:	client.cpp
	$(CPP) $(CPPFLAGS) xpac client.cpp

debug:	
	$(CPP) $(DEBUGFLAGS) $(CPPFLAGS) xpac client.cpp
