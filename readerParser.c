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
	//rl_bind_key('\t', rl_abort);//disable auto-complete
	
	char* line = NULL;
	
	line = readline(data->buffer_prompt); // inicijalizacija readline skupa funkcija
	
	if (!line){ // u slucaju da je ^D End-Of-File
		printf("exited - EOF\n");
		exit(0);
	}
	
	if (line && *(line)){ // sprema povijest naredbi, sve razlicito od prazne linije
		add_history(line); // history iz readline biblioteke
		history_shell(line); // vlastito spremanje povijesti naredbi
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
	
	if (strtok(temp_buffer, " \t\n\r") == NULL) { // prazna komanda
		printf("empty command!!!\n");
		return 2; //break;
	}
	
	strcpy(line_builtin, line); // posebno za builtin programe, da ne dira izvorni string u slucaju da nije nasao builtin program/funkciju
	if(check_builtin(line_builtin) == 1){
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
		token = strtok(NULL, " \n\t()<>;"); // " \n\t()<>&;" znakovi koje "ignorira"
	}
	
	if(count_pipe > 0){
		argv1[argc1] = NULL;
		argv2[argc2] = NULL;
		
		execArgsPiped(argv1, argv2);
		
		cleaning(data);
		return 2; //break;
	}
	
	argv1[argc1] = NULL; // potrebno zbog execvp, da se zna gdje je kraj niza argumenata
	strcat(data->program_path, argv1[0]); // spajanje putanje gdje se nalaze programi i samog imena programa
	
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
	
	if(pid == 0){ // child
		if(execvp(data->program_path, argv) == -1){
			printf("ERRNO: %s\n", strerror(errno));
			exit(1);
		}
	}else{ // parrent
		//wait(&child_status); // cekanje da dijete proces zavrsi sa dodatnim informacijama, pomocu MACRO-a provjera
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
