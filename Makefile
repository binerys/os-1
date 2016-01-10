OPTIMIZE=-O2

CC=gcc
CFLAGS=$(OPTIMIZE) -g3 #add more as needed

all: simpsh

simpsh: main.o parsing.o
	$(CC) $(CFLAGS) main.o parsing.o -o simpsh
	#could need to be main.o - may need to have depend on many object files

main.o: main.c
	$(CC) $(CFLAGS) main.c

parsing.o: parsing.c
	$(CC) $(CFLAGS) parsing.c

#tests: 
#check:

#dist: lab1-GarimaLunawatBreannaNery.tar.gz
#sources: Makefile main.c
#lab1-GarimaLunawatBreannaNery.tar.gz: $(sources) 
 #   tar -czf $@ $(sources)

clean:
	rm -f *.o *.so *.so.* simpsh


