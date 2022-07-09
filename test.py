import os

def parent_child ():
    n = os.fork()

    if n > 0:
        print("Parent process id: ", os.getpid())

    elif n == 0:
        print("Child process id: ", os.getpid())

parent_child()
        
