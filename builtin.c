#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#define BUFFER_SIZE_FOR_NAMES 50
#define ARGUMENT_SIZE 50

void exit_shell()
{
	printf("shell exited\n");
	_exit(0);
}

void echo(char* argv[]) // echo sa ispisom systemskih varijabli
{
	char* token;
	char* buff;
	int i = 1;
	
	token = strtok(argv[1], "$");
	
	if(argv[1][0] == '$'){
		buff = getenv(token);
		if(buff != NULL)
			printf("%s\n", buff);
		else
			printf("Cannot find system variable\n");
	}else{
		while(argv[i] != NULL){
			printf("%s ", argv[i]);
			i++;
		}
		printf("\n");
	}
}

int cdir(const char* path)
{
	if(chdir(path) == -1){
		fprintf(stderr, "cdir: ERROR: %s\n", strerror(errno));
		return -1;
	}
	
	return 0;
}

void pwd()
{
  	char cwd[BUFFER_SIZE_FOR_NAMES];

  	if (getcwd(cwd, BUFFER_SIZE_FOR_NAMES) != NULL)
   	    fprintf(stdout, "%s\n", cwd);
   	else
		fprintf(stderr, "getcwd: ERROR: %s\n", strerror(errno));

}

void clear_terminal()
{
	printf("\033c");
}

void history_shell(const char* cmd) // dodati za brisanje citave povijesti...
{
	FILE* fd;
	
	if((fd = fopen("history", "a")) == NULL){
		printf("Cannot open history file!\n");
		return;
	}
	
	if(fprintf(fd, "%s\n", cmd) < 0){
		printf("Cannot print commands in history file!\n");
		return;
	}
	
	fclose(fd);
}

void print_history() // dodati za brisanje citave povijesti...
{
	FILE* fd;
	int count_commands = 0;
	int c;
	
	if((fd = fopen("/home/matic/shell/history", "r")) == NULL){
		printf("Cannot open history file fore reading!\n");
		return;
	}
	
	printf("%d ", count_commands);
	while((c = getc(fd)) != EOF){
		if(c == '\n'){
			putchar(c);
			printf("%d ", ++count_commands);
		}else{
			putchar(c);
		}
	}
	putchar('\n');
	
	fclose(fd);
}


int check_builtin(char* line)
{
	char *argv[ARGUMENT_SIZE];
	int argc = 0;
	char* token;
	
	token = strtok(line, " \n\t()<>|&;");
	while(token != NULL && argc < 256){
		argv[argc] = token;
		token = strtok(NULL, " \n\t()<>|&;"); // " \n\t()<>|&;" znakovi koje "ignorira"
		argc++;
	}
	
	argv[argc] = NULL;

	if(strcmp(line, "exit") == 0){
		exit_shell();
		return 1;
	}else if(strcmp(line, "cdir") == 0){
		cdir(argv[1]);
		return 1;
	}else if(strcmp(line, "ph") == 0){
		print_history();
		return 1;
	}else if(strcmp(line, "pwd") == 0){
		pwd();
		return 1;
	}else if(strcmp(line, "clear") == 0){
		clear_terminal();
		return 1;
	}else if(strcmp(line, "echo") == 0){
		echo(argv);
		return 1;
	}
	
	return 0;	
}










