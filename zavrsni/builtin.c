#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int exit_shell()
{
	printf("shell exited\n");
	return 0;
}

int echo(char* line)
{
	
}

int cdir(char* path)
{
	if(!chdir(path)){
		fprintf(stderr, "%s\n", strerror(errno));
		return -1;
	}
	
	return 0;
}

int pwd()
{
  	char cwd[1024];
  	if (getcwd(cwd, sizeof(cwd)) != NULL)
   	    fprintf(stdout, "%s ", cwd);
   	else
		perror("getcwd() error");
   	return 0;
}

int clear_terminal()
{
	printf("\033c");
}
