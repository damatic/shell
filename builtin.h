int exit_shell();

int echo(char* line);

int cdir(const char* path);

int pwd();

int clear_terminal();

int history_shell(const char* cmd);

void print_history();

int check_builtin(char* line);