#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#define BUFFER_SIZE_FOR_NAMES 124


int init_shell(char* hostname, char* filename)
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

int echo(char* line)
{
	return 0;
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










