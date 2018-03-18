CC=gcc
CPP=g++
CFLAGS=-std=c99 -Wall -Wextra -pedantic -o
CPPFLAGS=-std=c++17 -Wall -Wextra -pedantic -o
DEBUGFLAGS=-g
INSTALLDIR=/usr/local/bin
MANPATH=/usr/share/man/man1
CPPFILES=client.cpp client_socket.cpp man_help.cpp

all: xpac

clean:
	-rm xpac

xpac:	client.cpp
	$(CPP) $(CPPFLAGS) xpac $(CPPFILES)

debug:	
	$(CPP) $(DEBUGFLAGS) $(CPPFLAGS) xpac $(CPPFILES)

install:
	mv xpac $(INSTALLDIR)
	cp xpac.1 $(MANPATH)
	mandb

uninstall:
	rm -f $(INSTALLDIR)/xpac
	rm $(MANPATH)/xpac.1
	mandb
