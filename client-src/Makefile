CC=gcc
CPP=g++
CFLAGS=-std=c99 -Wall -Wextra -pedantic -o
CPPFLAGS=-std=c++17 -Wall -Wextra -pedantic -o
DEBUGFLAGS=-g
INSTALLDIR=/usr/local/bin
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
	cp xpac.1 /usr/local/share/man/man1/
	mandb

uninstall:
	rm -f $(INSTALLDIR)/xpac
	rm /usr/local/share/man/man1/xpac.1
