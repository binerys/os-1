OPTIMIZE=-O2
CC = gcc
CFLAGS = $(OPTIMIZE) -g3
DEPS = parsing.h handling.h openF.h
OBJ = main.o parsing.o openF.o handling.o

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


