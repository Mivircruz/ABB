CC = gcc
CFLAGS =  -g -std=c99 -Wall -Wconversion -Wno-sign-conversion -Werror 
VFLAGS = --leak-check=full --track-origins=yes --show-reachable=yes

CFILES = main_abb.c abb.c testing.c pruebas_alumno.c
HFILES = abb.h testing.h
EXEC = pruebas 

build: $(CFILES) 
	$(CC) $(CFLAGS)  -o $(EXEC) $(CFILES) 

run: build
	./$(EXEC)

valgrind: build
	valgrind $(VFLAGS) ./$(EXEC)

gdb: build
	gdb $(GDBFLAGS) ./$(EXEC)

zip: build
	zip $(EXEC).zip $(CFILES) $(HFILES)

clean:
	rm -f *.o $(EXEC)