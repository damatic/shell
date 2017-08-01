#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

void print_error(char *this, char *filename)
{	// u slucaju da radnja ne uspije iz nekog razloga
	// this ce biti ime komande
	fprintf(stderr, "%s: cannot create directory '%s'\n"
	"error: %s\n", this, filename, strerror(errno));
	
	exit(EXIT_FAILURE);
}

void print_usage(char *this)
{	// u slucaju da nije sintaksno tocno
	fprintf(stderr, "SYNTAX ERROR: "
	"USAGE %s [filename]\n", this);
	
	exit(EXIT_FAILURE);
}

int main(int argc, char* argv[])
{	// napraviti posebno za odredene dozvole
	//errno = 0; // potrebno postavit, trenutno nema greski
	
	//printf("%d\n", argc);
	
	if(argc == 2){
		if(mkdir(argv[1], 0700) == -1) {	// provjera da li postoji direktorij		
			print_error(argv[0], argv[1]);
			return EXIT_FAILURE;
		}
	}
	else{
		print_usage(argv[0]);
		return EXIT_FAILURE;
	}
    
    
	return EXIT_SUCCESS;
}
