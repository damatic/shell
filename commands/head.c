#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>

void print_error(const char *this, const char *filename)
{	// u slucaju da radnja ne uspije iz nekog razloga
	// this ce biti ime komande
	fprintf(stderr, "%s: cannot print 10 lines of '%s' to terminal\n"
	"ERROR: %s\n", this, filename, strerror(errno));
	
	exit(EXIT_FAILURE);
}

void print_usage(const char *this)
{	// u slucaju da nije sintaksno tocno
	fprintf(stderr, "SYNTAX ERROR: \n"
	"USAGE %s [OPTION] [source]\n", this);
	
	exit(EXIT_FAILURE);
}

int main(int argc, char* argv[])
{
	int c;
	FILE *file;
	struct stat stbuf1, stbuf2;
	const int limit = 10;
	int count = 0;
	int flag = 0;
	
	if(fstat(3, &stbuf2) == 0){ // provjera ako je fd otvoren, stdin spojen na read kraj od pipe-a....
		flag++;
		if((file = fopen("head_temp", "w")) == NULL) // problem s EOF-om pa je zbog toga 'i' granica...
			print_error(argv[0], "head_temp");
			
		while((c = getc(stdin)) != EOF ){
			fprintf(file, "%c", c);
		}
		
		fclose(file);
		argv[1] = malloc(sizeof(char)*50);
		strcpy(argv[1], "head_temp");
	}
	
	if(stat(argv[1], &stbuf1) == -1){ // ako source file/dir ne postoji
		print_error(argv[0], argv[1]);
	}
	
	file = fopen(argv[1], "r");
	
	if (file != NULL) {
		while ((c = getc(file)) != EOF && count < limit){
			if(c == '\n')
				count++;
			putchar(c);
		}
	}
	if(flag == 1){ // ciscenje programa u slucaju da je bio pipe
			fclose(file);
			if(remove("head_temp") == -1){
				perror("cannot remove file 'head_temp'");
			}
	}else{
		fclose(file);
	}

	return 0;
}