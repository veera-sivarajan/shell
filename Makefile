# CC = gcc
CC = zig cc
CFLAGS = -g -Wall 
OBJECTS = $(filter-out test.c, $(wildcard *.c)) #Source files
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
