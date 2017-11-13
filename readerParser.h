#include <stdio.h>
#include <unistd.h>
#include <linux/limits.h>


#define BUFFER_LENGTH 1024
#define BUFFER_SIZE_FOR_NAMES 50
#define ARGUMENT_SIZE 50

typedef struct init{
	char program_path[PATH_MAX];
	char hostname_file[PATH_MAX];
	char hostname[BUFFER_SIZE_FOR_NAMES];
	char username[BUFFER_SIZE_FOR_NAMES];
	char line[BUFFER_LENGTH];
	char* argv1[BUFFER_SIZE_FOR_NAMES];
	char* argv2[BUFFER_SIZE_FOR_NAMES];
	char* token;
	int child_status;
	unsigned argc1;
	unsigned argc2;
	size_t length;
	char line_builtin[BUFFER_LENGTH];
	unsigned count_pipe;
	char temp_buffer[BUFFER_LENGTH];
	pid_t pid;
}init;

init* init_shell();

char* readLineCommand(void);

void parseCommand(const char* commandLine);

int parseInfo();

void cleaning(init* data);