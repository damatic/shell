#include <stdio.h>
#include <unistd.h>
#include <linux/limits.h>

#define BUFFER_LENGTH 1024
#define BUFFER_SIZE_FOR_NAMES 50
#define ARGUMENT_SIZE 50

typedef struct init
{
    char program_path[PATH_MAX];
    char hostname[BUFFER_SIZE_FOR_NAMES];
    char buffer_prompt[BUFFER_LENGTH];
    char *username;
    int child_status;
} init;

void start_shell(void);

init *init_shell(void);

char *readLineCommand(init *data);

int parseCommand(init *data, char *line);

int executeCommand(init *data, char *argv[]);

int parseInfo(void);

void cleaning(init *data);