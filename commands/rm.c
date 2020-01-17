#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

void print_error(const char *this, const char *filename)
{	// in case if command fails for some reason
	// this will be name of the command
	fprintf(stderr, "%s: file '%s' cannot be deleted\n"
					"ERROR: %s\n", this, filename, strerror(errno));
	
	exit(EXIT_FAILURE);
}

void print_usage(const char *this)
{	// if syntax of command is not correct
	fprintf(stderr, "SYNTAX ERROR: \n"
					"USAGE %s [FILE]\n", this);
	
	exit(EXIT_FAILURE);
}

void brisanje_direktorija(const char* path) // for empty directories
{	
	if(rmdir(path) == -1 && errno == ENOTEMPTY){
		print_error("rm", path);
	}
}

int main(int argc, char* argv[])
{
	struct stat stbuf;
	
	if(stat(argv[1], &stbuf) == -1){ // if directory does not exist
		print_error(argv[0], argv[1]);
	}
	if((stbuf.st_mode & S_IFMT) == S_IFDIR){
		brisanje_direktorija(argv[1]);

	}else{
		if(remove(argv[1]) == -1){
			print_error(argv[0], argv[1]);
		}
	}
	return 0;
}