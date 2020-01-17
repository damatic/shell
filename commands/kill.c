#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <signal.h>


void print_error(const char *this, const char *filename)
{	// in case if command fails for some reason
	// this will be name of the command
	fprintf(stderr, "%s: cannot terminate process with PID: %s\n"
					"ERROR: %s\n", this, filename, strerror(errno));
	
	exit(EXIT_FAILURE);
}

void print_usage(const char *this)
{	// if syntax of command is not correct
	fprintf(stderr, "SYNTAX ERROR: \n"
					"USAGE %s [PID]\n", this);
	
	exit(EXIT_FAILURE);
}


int main(int argc, char* argv[])
{
	pid_t pid;
	
	if(argv[1] == NULL){
		print_usage(argv[0]);
	}
	
	pid = atoi(argv[1]);
	
	if(kill(pid, SIGTERM) != 0){			// better SIGTERM, with SIGKILL process killed without clean
		print_error(argv[0], argv[1]);
	}
	
	return 0;
}