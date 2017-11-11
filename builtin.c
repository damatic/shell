#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#define BUFFER_SIZE_FOR_NAMES 124
#define ARGUMENT_SIZE 50

int init_hostname(char* hostname, char* filename)
{
	FILE* fp;
	
	if((fp = fopen(filename, "w")) == NULL)
		return EXIT_FAILURE;
	
	fprintf(fp, "%s\n", hostname);

	fclose(fp);

	return 0;
}

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

char* name(char* hostname_file)
{
	FILE * fp;
	char* hostname;

	hostname = (char*)malloc(BUFFER_SIZE_FOR_NAMES * sizeof(char));

	if((fp = fopen(hostname_file, "r")) == NULL)
		return (char*)(EXIT_FAILURE);
	
	fgets(hostname, BUFFER_SIZE_FOR_NAMES, fp);
	
	hostname[strcspn(hostname, "\n")] = 0;
	
	fclose(fp);

	return hostname;
}

int cdir(char* path)
{
	if(chdir(path) == -1){
		fprintf(stderr, "ERROR: %s\n", strerror(errno));
		return -1;
	}
	
	return 0;
}

void pwd()
{
  	char cwd[1024];

  	if (getcwd(cwd, sizeof(cwd)) != NULL)
   	    fprintf(stdout, "%s\n", cwd);
   	else
		perror("getcwd() error");

}

void clear_terminal()
{
	printf("\033c");
}

void history_shell(char* cmd) // dodati za brisanje citave povijesti...
{
	FILE* fd;
	static int count = 0;
	
	if((fd = fopen("/home/matic/shell/history", "a")) == NULL){
		printf("Cannot open history file!\n");
		return;
	}
	
	if(fprintf(fd, "%d %s", count++, cmd) < 0){
		printf("Cannot print commands in history file!\n");
		return;
	}
	
	fclose(fd);
}

int check_builtin(char *line)
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










