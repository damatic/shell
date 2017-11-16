#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>

void print_error(const char *this, const char *filename)
{	// u slucaju da radnja ne uspije iz nekog razloga
	// this ce biti ime komande
	fprintf(stderr, "%s: cannot print '%s' to terminal\n"
					"ERROR: %s\n", this, filename, strerror(errno));
	
	exit(EXIT_FAILURE);
}

void print_usage(const char *this)
{	// u slucaju da nije sintaksno tocno
	fprintf(stderr, "SYNTAX ERROR: \n"
					"USAGE %s [source]\n", this);
	
	exit(EXIT_FAILURE);
}

int main(int argc, char* argv[])
{
	int c;
	FILE *file;
	struct stat stbuf;
	
	if(stat(argv[1], &stbuf) == -1){ // ako source file/dir ne postoji
		print_error(argv[0], argv[1]);
		return EXIT_FAILURE;
	}
	
	if((file = fopen(argv[1], "r")) == NULL){
		print_error(argv[0], argv[1]);
	}

	while ((c = getc(file)) != EOF){
		putchar(c);
	}
	putchar('\n');
	
	fclose(file);

	return 0;
}