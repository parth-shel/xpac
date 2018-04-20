CC=gcc
CPP=g++
CFLAGS=-std=c99 -Wall -Wextra -pedantic -o
SUFFIXFLAGS=-lssl -lcrypto
CPPFLAGS=-std=c++11 -Wall -Wextra -pedantic -o
DEBUGFLAGS=-g
INSTALLDIR=/usr/local/bin
MANPATH=/usr/share/man/man1
CPPFILES=client.cpp client_socket.cpp man_help.cpp metadata.cpp xpac_install_utility.cpp installed_packages_modules.cpp cleanup_directory.cpp MD5checksum.cc

all: xpac

clean:
	rm -f xpac

xpac:	$(CPPFILES)
	$(CPP) $(CPPFLAGS) xpac $(CPPFILES) $(SUFFIXFLAGS)

debug:	
	$(CPP) $(DEBUGFLAGS) $(CPPFLAGS) xpac $(CPPFILES)

install:
	mv xpac $(INSTALLDIR)
	cp man_help_txt $(INSTALLDIR) 
	cp xpac.1 $(MANPATH)
	mandb

uninstall:
	rm -f $(INSTALLDIR)/xpac
	rm -f $(INSTALLDIR)/man_help_txt
	rm $(MANPATH)/xpac.1
