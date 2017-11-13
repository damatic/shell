int init_hostname(const char* hostname, const char* filename);

int exit_shell();

int echo(char* line);

char* name(const char* hostname_file);

int cdir(const char* path);

int pwd();

int clear_terminal();

int history_shell(const char* cmd);

int check_builtin(char* line);