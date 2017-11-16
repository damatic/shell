#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

void print_error(const char *this, const char *filename)
{	// u slucaju da radnja ne uspije iz nekog razloga
	// this ce biti ime komande
	fprintf(stderr, "%s: failed to create '%s' file\n"
					"ERROR: %s\n", this, filename, strerror(errno));
	
	exit(EXIT_FAILURE);
}

void print_usage(const char *this)
{	// u slucaju da nije sintaksno tocno
	fprintf(stderr, "SYNTAX ERROR: "
					"USAGE %s [filename]\n", this);
	
	exit(EXIT_FAILURE);
}

int main(int argc, char* argv[])
{
	FILE* fp;
	struct stat stbuf;
	
	if(argv[1] == NULL){
		print_usage(argv[0]);
	}
	
	if(stat(argv[1], &stbuf) == 0){ // ako datoteka postoji
		print_error(argv[0], argv[1]);
	}
	
	if((fp = fopen(argv[1] , "a")) == NULL){
		print_error(argv[0], argv[1]);
	}
	
	if(fclose(fp)){
		print_error(argv[0], argv[1]);
	}
	
	return 0;
}