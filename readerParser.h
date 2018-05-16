#include <stdio.h>
#include <unistd.h>
#include <linux/limits.h>

#define BUFFER_LENGTH 1024
#define BUFFER_SIZE_FOR_NAMES 50
#define ARGUMENT_SIZE 50

typedef struct init{
	char program_path[PATH_MAX];
	char hostname[BUFFER_SIZE_FOR_NAMES];
	char buffer_prompt[BUFFER_LENGTH];
	char* username;
	char* line;
	int child_status;
}init;

int start_shell(void);

int init_shell(init* data);

int readLineCommand(init* data);

int parseCommand(init* data);

int executeCommand(init* data, char* argv[]);

int parseInfo(void);

void cleaning(init* data);