#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

void print_error(char *this, char *filename1, char *filename2)
{	// u slucaju da radnja ne uspije iz nekog razloga
	// this ce biti ime komande
	fprintf(stderr, "%s: cannot move '%s' to '%s'\n"
	"error: %s\n", this, filename1, filename2, strerror(errno));
	
	exit(EXIT_FAILURE);
}

void print_usage(char *this)
{	// u slucaju da nije sintaksno tocno
	fprintf(stderr, "SYNTAX ERROR: \n"
	"USAGE %s [filename1] [filename2]\n", this);
	
	exit(EXIT_FAILURE);
}

int main(int argc, char* argv[])
{	
	//errno = 0; // potrebno postavit, trenutno nema greski
	
	//printf("%d\n", argc);
	
	if(argc == 3){
		if(rename(argv[1], argv[2]) == -1) {
			print_error(argv[0], argv[1], argv[2]);
			return EXIT_FAILURE;
		}
	}
	else{
		print_usage(argv[0]);
		return EXIT_FAILURE;
	}
    
    
	return EXIT_SUCCESS;
}

