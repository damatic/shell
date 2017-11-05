int init_shell(char* hostname, char* filename);

int exit_shell();

int echo(char* line);

char* name(char* hostname_file);

int cdir(char* path);

int pwd();

int clear_terminal();

int history_shell(char* cmd);

int check_builtin(char *line);