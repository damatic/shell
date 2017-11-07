#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>

void print_error(char *this, char *filename)
{	// u slucaju da radnja ne uspije iz nekog razloga
	// this ce biti ime komande
	fprintf(stderr, "%s: Cant print 10 lines of '%s' to terminal\n"
	"ERROR: %s\n", this, filename, strerror(errno));
	
	exit(EXIT_FAILURE);
}

void print_usage(char *this)
{	// u slucaju da nije sintaksno tocno
	fprintf(stderr, "SYNTAX ERROR: \n"
	"USAGE %s [OPTION] [source]\n", this);
	
	exit(EXIT_FAILURE);
}

int main(int argc, char* argv[])
{
	int c;
	FILE *file;
	struct stat stbuf1;
	int limit = 10;
	int count = 0;
	
	
	
	if(stat(argv[1], &stbuf1) == -1){ // ako source file/dir ne postoji
		print_error(argv[0], argv[1]);
		return EXIT_FAILURE;
	}
	
	file = fopen(argv[1], "r");
	
	if (file != NULL) {
		while ((c = getc(file)) != EOF && count < limit){
			if(c == '\n')
				count++;
			putchar(c);
		}
	}
	fclose(file);

	return 0;
}