#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>

void print_error(const char *this, const char *filename)
{	// in case if command fails for some reason
	// this will be name of the command
	fprintf(stderr, "%s: cannot print '%s' to terminal\n"
					"ERROR: %s\n", this, filename, strerror(errno));
	
	exit(EXIT_FAILURE);
}

void print_usage(const char *this)
{	// if syntax of command is not correct
	fprintf(stderr, "SYNTAX ERROR: \n"
					"USAGE %s [source]\n", this);
	
	exit(EXIT_FAILURE);
}

int main(int argc, char* argv[])
{
	int c;
	FILE *file;
	struct stat stbuf;
	
	if(stat(argv[1], &stbuf) == -1){ // if source file/dir does not exist
		print_error(argv[0], argv[1]);
		return EXIT_FAILURE;
	}
	
	if((file = fopen(argv[1], "r")) == NULL){
		print_error(argv[0], argv[1]);
	}

	while ((c = getc(file)) != EOF){
		putchar(c);
	}
	//putchar('\n');
	
	fclose(file);

	return 0;
}
