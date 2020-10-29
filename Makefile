CC = gcc
CFLAGS = -g -Wall -std=c99
OBJECTS = builtin.c execute.c main.c parse.c #Source files
NAME = myshell #Desired filename
TODELETE = *.o # the *.o should be the same as the objects
LIBS = *.h  #remove line if no external libraries needed

mt-collatz : $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME) $(LIBS)

.PHONY: clean

clean:
	rm -f $(TODELETE)
