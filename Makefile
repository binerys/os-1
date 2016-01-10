OPTIMIZE=-O2
CC = gcc
CFLAGS = $(OPTIMIZE) -g3 -Wall
DEPS = parsing.h
OBJ = main.o parsing.o

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

simpsh: $(OBJ)
	gcc $(CFLAGS) -o $@ $^

#tests: 
#check:

#dist: lab1-GarimaLunawatBreannaNery.tar.gz
#sources: Makefile main.c
#lab1-GarimaLunawatBreannaNery.tar.gz: $(sources) 
 #   tar -czf $@ $(sources)

clean:
	rm -f *.o *.so *.so.* simpsh


