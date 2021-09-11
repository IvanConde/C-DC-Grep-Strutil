CC = gcc
CFLAGS = -g -std=c99 -Wall -Wtype-limits -pedantic -Wconversion -Wno-sign-conversion
VFLAGS = --leak-check=full --track-origins=yes --show-reachable=yes
EXEC_GREP = grep
EXEC_DC = dc

build-grep: grep.c lista.c lista.h
	$(CC) $(CFLAGS) grep.c lista.c -o $(EXEC_GREP)

valgrind-grep: build-grep
	valgrind $(VFLAGS) ./$(EXEC_GREP) re 2 charla.txt

build-dc: dc.c pila.c pila.h strutil.c strutil.h
	$(CC) $(CFLAGS) dc.c pila.c strutil.c -o $(EXEC_DC)

valgrind-dc: build-dc
	valgrind $(VFLAGS) ./$(EXEC_DC) < cuentas.txt

clean:
	rm -f *.o $(EXEC_GREP) $(EXEC_DC)