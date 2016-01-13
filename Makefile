OPTIMIZE=-O2
CC = gcc
CFLAGS = $(OPTIMIZE) -g3 -std=gnu11
DEPS = parser.h handler.h openF.h
OBJ = main.o parser.o openF.o handler.o
SOURCES = Makefile main.c parser.h parser.c README.md openF.c openF.h handler.c handler.h test.sh 

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

simpsh: $(OBJ)
	gcc $(CFLAGS) -o $@ $^

#tests: 
check:
	./test.sh

dist: lab1-GarimaLunawatBreannaNery.tar.gz
lab1-GarimaLunawatBreannaNery.tar.gz: $(SOURCES) 
	tar -czf $@ $(SOURCES)

clean:
	rm -f *.o *.so *.so.* simpsh lab1-GarimaLunawatBreannaNery.tar.gz


