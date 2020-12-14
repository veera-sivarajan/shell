# include <stdio.h>
# include <unistd.h>
# include <errno.h>
# include <stdlib.h>
# include <string.h>

extern char *all_builtin[];

extern int (*builtin_func[]) (char **);

int get_num_builtins();

int change_dir(char **args);

int help_cmd(char **args);

int exit_cmd(char **args);

int lock_cmd(char **args);
