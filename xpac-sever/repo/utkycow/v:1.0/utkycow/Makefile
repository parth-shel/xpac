goal: cowmake

cowmake: utkycow.c
	gcc -o utkycow utkycow.c

install:
	gcc -o utkycow utkycow.c
	cp ./utkycow /usr/bin/

uninstall:
	rm /usr/bin/utkycow

clean: 
	rm utkycow
