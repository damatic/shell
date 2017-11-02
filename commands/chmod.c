#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>


void print_error(char *this, char *filename)
{	// u slucaju da radnja ne uspije iz nekog razloga
	// this ce biti ime komande
	fprintf(stderr, "%s: cannot change permission mode for '%s'\n"
	"error: %s\n", this, filename, strerror(errno));
	
	exit(EXIT_FAILURE);
}

void print_usage(char *this)
{	// u slucaju da nije sintaksno tocno
	fprintf(stderr, "SYNTAX ERROR: \n"
	"USAGE %s [mode] [filename]\n", this);
	
	exit(EXIT_FAILURE);
}

int main(int argc, char* argv[])
{
    char mode[125];
    char buf[125];
    int i;
	
	strcpy(mode, argv[1]);
	strcpy(buf, argv[2]);
	
    i = strtol(mode, 0, 8);	
	
    if (chmod (buf, i) < 0)
    {
        fprintf(stderr, "%s: error in chmod(%s, %s) - %d (%s)\n",
                argv[0], buf, mode, errno, strerror(errno));
        exit(1);
    }
	
    return(0);
}
