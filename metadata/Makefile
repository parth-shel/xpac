CPP=g++
CPPFLAGS=-std=c++17 -Wall -Wextra -pedantic -o
DEBUGFLAGS=-g
all:	metadata

clean:
	-rm test.exe

metadata:
	$(CPP) $(CPPFLAGS) test.exe metadata.cpp test_metadata.cpp

debug:
	$(CPP) $(DEBUGFLAGS) $(CPPFLAGS) test.exe metadata.cpp test_metadata.cpp
