#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <linux/limits.h>

void print_error(const char *this, const char *filename1, const char *filename2)
{	// u slucaju da radnja ne uspije iz nekog razloga
	// this ce biti ime komande
	fprintf(stderr, "%s: cannot move '%s' to '%s'\n"
	"error: %s\n", this, filename1, filename2, strerror(errno));
	
	exit(EXIT_FAILURE);
}

void print_usage(const char *this)
{	// u slucaju da nije sintaksno tocno
	fprintf(stderr, "SYNTAX ERROR: \n"
	"USAGE %s [filename1] [filename2]\n", this);
	
	exit(EXIT_FAILURE);
}

int main(int argc, char* argv[])
{	
	struct stat stbuf;
	char buffer[PATH_MAX];
	
	
	if(argv[1] == NULL || argv[2] == NULL){
		print_usage(argv[0]);
	}
	
	strcpy(buffer, argv[2]);

	if(stat(argv[2], &stbuf) == 0){					// u slucaju da se dezi premjestiti direktorij sa sadrzajem
		if((stbuf.st_mode & S_IFMT) == S_IFDIR){
			strcat(buffer, "/");
			strcat(buffer, argv[1]);
		}
	}
	
	if(rename(argv[1], buffer) == -1) {
		print_error(argv[0], argv[1], buffer);
	}
    
	return 0;
}








