#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <linux/limits.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "readerParser.h"
#include "pipe.h"
#include "builtin.h"


#include <readline/readline.h>
#include <readline/history.h>

#define BUFFER_SIZE_FOR_NAMES 50

void start_shell()
{
	init* data = NULL;

	while(1){
		data = init_shell();
		parseCommand(data, readLineCommand(data));
	}
}

init* init_shell()
{
	init* data;
	
	data = (init*)malloc(sizeof(init));
	
	strcpy(data->program_path, getenv("HOME"));
	strcat(data->program_path, "/shell/obj_output/");
	data->username = getenv("USER");
	
	if(gethostname(data->hostname, BUFFER_SIZE_FOR_NAMES) == -1){
		printf("Cannot get hostname\n"
			   "ERROR: %s", strerror(errno));
	}
	
	sprintf(data->buffer_prompt, "%s@%s >> ", data->username, data->hostname);
	
	return data;
}

char* readLineCommand(init* data)
{
	//rl_bind_key('\t', rl_abort); //disable auto-complete
	
	char* line = NULL;
	
	line = readline(data->buffer_prompt); // initialisation of readline library
	
	if (!line){ // incase there is ^D End-Of-File
		printf("exited - EOF\n");
		exit(0);
	}
	
	if (line && *(line)){ // save commands except it is empty line
		add_history(line); // history from readline linrary
		history_shell(line); // internal (readline library) saving of commands
	}
	
	return line;
}

int parseCommand(init* data, char* line)
{
	char* token;
	unsigned count_pipe = 0;
	char line_builtin[BUFFER_LENGTH];
	char temp_buffer[BUFFER_LENGTH];
	char* argv1[BUFFER_SIZE_FOR_NAMES];
	char* argv2[BUFFER_SIZE_FOR_NAMES];
	unsigned argc1 = 0;
	unsigned argc2 = 0;
	
	strcpy(temp_buffer, line);
	
	if (strtok(temp_buffer, " \t\n\r") == NULL) { // empty command
		return 2; //break;
	}
	
	strcpy(line_builtin, line); 			// particular for builin programs, not to
	if(check_builtin(line_builtin) == 1){   // modify string in case it didnt found builtin program
		cleaning(data);
		return 2; //break;
	}
	
	token = strtok(line, " \n\t()<>;");
	while(token != NULL && argc1 < 256 && argc2 < 256){
		if(strcmp(token, "|") == 0){
			count_pipe = 1;
		}else{
			if(count_pipe == 0){
				argv1[argc1] = token;
				argc1++;
			}
			if(count_pipe == 1){
				argv2[argc2] = token;
				argc2++;
			}
		}
		token = strtok(NULL, " \n\t()<>;"); // " \n\t()<>&;" chars that "ignores"
	}
	
	if(count_pipe > 0){
		argv1[argc1] = NULL;
		argv2[argc2] = NULL;
		
		execArgsPiped(argv1, argv2);
		
		cleaning(data);
		return 2; //break;
	}
	
	argv1[argc1] = NULL; // needed for execvp, so there is info about end of arguments
	strcat(data->program_path, argv1[0]); // concatinate path where programs are located and name of the program
	
	if(executeCommand(data, argv1) == 2)
		return 2;
	
	return 0;
}

int executeCommand(init* data, char* argv[])
{
	pid_t pid;
	
	if((pid = fork()) == -1){
		cleaning(data);
		return 1; //break;
	}
	
	if(pid == 0){ // child process
		if(execvp(data->program_path, argv) == -1){
			printf("ERRNO: %s\n", strerror(errno));
			exit(1);
		}
	}else{ // parrent process
		//wait(&child_status); // waiting for first child process to ends with additional informations, with MACRO
		wait(NULL);
		cleaning(data);
	}
	
	return 0;
}

int parseInfo()
{
	return 0;
}

void cleaning(init* data)
{
	free(data);
	data = NULL;
	
	data = init_shell();
}
