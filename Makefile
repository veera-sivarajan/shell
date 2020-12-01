CC = gcc
CFLAGS = -g -Wall -std=c99 
OBJECTS = $(filter-out test.c, $(wildcard *.c)) #Source files
NAME = myshell #Desired filename
TODELETE = *.o # the *.o should be the same as the objects

mt-collatz : $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME) $(LIBS) -lreadline

.PHONY: clean run

clean:
	rm -f $(TODELETE)

run:	myshell
	./myshell
