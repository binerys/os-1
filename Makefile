OPTIMIZE=-O2
CC = gcc
CFLAGS = $(OPTIMIZE) -g3 -std=gnu11
DEPS = parser.h handler.h simpsh.h
OBJ = main.o parser.o handler.o simpsh.o
SOURCES = Makefile main.c parser.h parser.c README.md handler.c handler.h test.sh simpsh.c simpsh.h

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

simpsh: $(OBJ)
	gcc $(CFLAGS) -o $@ $^

#tests: 
check:
	./test.sh

dist: lab1-GarimaLunawatBreannaNery.tar.gz
lab1-GarimaLunawatBreannaNery.tar.gz: $(SOURCES)
	mkdir lab1-GarimaLunawatBreannaNery
	cp $(SOURCES) lab1-GarimaLunawatBreannaNery
	tar -czf $@ lab1-GarimaLunawatBreannaNery
	rm -r lab1-GarimaLunawatBreannaNery

clean:
	rm -f *.o *.so *.so.* simpsh lab1-GarimaLunawatBreannaNery.tar.gz


