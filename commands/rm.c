#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

void print_error(char *this, char *filename)
{	// u slucaju da radnja ne uspije iz nekog razloga
	// this ce biti ime komande
	fprintf(stderr, "%s: file '%s' cannot be deleted\n"
	"ERROR: %s\n", this, filename, strerror(errno));
	
	exit(EXIT_FAILURE);
}

void print_usage(char *this)
{	// u slucaju da nije sintaksno tocno
	fprintf(stderr, "SYNTAX ERROR: \n"
	"USAGE %s [FILE]\n", this);
	
	exit(EXIT_FAILURE);
}

void brisanje_direktorija(char* path) // za prazne direktorije
{	
	if(rmdir(path) == -1 && errno == ENOTEMPTY){
		print_error("rm", path);
	}
}

int main(int argc, char* argv[])
{
	struct stat stbuf;
	
	if(stat(argv[1], &stbuf) == -1){ // ako datoteka ne postoji
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