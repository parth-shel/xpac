CC=gcc
CPP=g++
CFLAGS=-std=c99 -Wall -Wextra -pedantic -o
CPPFLAGS=-std=c++17 -Wall -Wextra -pedantic -o
DEBUGFLAGS=-g
INSTALLDIR=/usr/local/bin

all: xpac

clean:
	-rm xpac

xpac:	client.cpp
	$(CPP) $(CPPFLAGS) xpac client.cpp client_socket.cpp

debug:	
	$(CPP) $(DEBUGFLAGS) $(CPPFLAGS) xpac client.cpp client_socket.cpp

install:
	mv xpac $(INSTALLDIR)

uninstall:
	rm -f $(INSTALLDIR)/xpac
