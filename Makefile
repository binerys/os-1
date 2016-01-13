OPTIMIZE=-O2
CC = gcc
CFLAGS = $(OPTIMIZE) -g3 -std=gnu11
DEPS = parser.h handler.h openF.h
OBJ = main.o parser.o openF.o handler.o

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

simpsh: $(OBJ)
	gcc $(CFLAGS) -o $@ $^

#tests: 
check:
	./test.sh

#dist: lab1-GarimaLunawatBreannaNery.tar.gz
#sources: Makefile main.c
#lab1-GarimaLunawatBreannaNery.tar.gz: $(sources) 
 #   tar -czf $@ $(sources)

clean:
	rm -f *.o *.so *.so.* simpsh


