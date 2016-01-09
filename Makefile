OPTIMIZE=-O2

CC=gcc
CFLAGS=$(OPTIMIZE) -g3 #add more as needed

default: simpsh

simpsh: 
	$(CC) $(CFLAGS) $@ main.c
	#could need to be main.o - may need to have depend on many object files

tests: 
check:

dist: lab1-GarimaLunawatBreannaNery.tar.gz
sources: Makefile main.c
lab1-GarimaLunawatBreannaNery.tar.gz: $(sources) 
    tar -czf $@ $(sources)

clean:
	rm -f *.o *.so *.so.* *.tgz simpsh lab1-GarimaLunawatBreannaNery.tar.gz


