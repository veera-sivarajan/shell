# CC = gcc
CC = zig cc
CFLAGS = -g -Wall 
OBJECTS = $(filter-out test.c, $(wildcard ./c/*.c)) #Source files
OBJS = $(filter-out ./c/main.c, $(wildcard ./c/*.c)) #Source files
NAME = myshell #Desired filename
TODELETE = *.o # the *.o should be the same as the objects
LIBS = -lreadline

mt-collatz : $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME) $(LIBS) 

.PHONY: clean run

clean:
	rm -f $(TODELETE)

run:	myshell
	valgrind -s --tool=memcheck --track-origins=yes ./myshell

translate:	
	zig translate-c -lc -l readline c/main.c > src/main.zig

buildobj:	
	zig cc -c $(OBJS) -o src/obj.o

build:  translate buildobj	
	zig build-exe src/main.zig src/obj.o -lc -l readline




