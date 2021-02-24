# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/types.h>
# include <errno.h>
# include <sys/wait.h>
# include <wordexp.h>
# include <signal.h>

typedef struct file_descs {
    int input_fd;
    int pipe_fd[2];
} FD;

int start_process(char **args, FD *fdescs);

int execute_command(char **args, FD *fdescs);
