OPTIMIZE=-O2
CC = gcc
CFLAGS = $(OPTIMIZE) -g3 -std=gnu11
DEPS = parser.h handler.h simpsh.h
OBJ = main.o parser.o handler.o simpsh.o
SOURCES = Makefile main.c parser.h parser.c README.md handler.c handler.h test-design.sh simpsh.c simpsh.h 

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

simpsh: $(OBJ)
	gcc $(CFLAGS) -o $@ $^

#tests: 
check:
	./test-design.sh

dist: lab1DP-GarimaLunawatBreannaNery.tar.gz
lab1DP-GarimaLunawatBreannaNery.tar.gz: $(SOURCES)
	mkdir lab1DP-GarimaLunawatBreannaNery
	cp $(SOURCES) lab1DP-GarimaLunawatBreannaNery
	tar -czf $@ lab1DP-GarimaLunawatBreannaNery
	rm -r lab1DP-GarimaLunawatBreannaNery

clean:
	rm -f *.o *.so *.so.* simpsh lab1-GarimaLunawatBreannaNery.tar.gz lab1DP-GarimaLunawatBreannaNery.tar.gz


