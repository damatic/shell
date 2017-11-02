#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h> // potrebno za rmdir


void print_error(char *this, char *filename)
{	// u slucaju da radnja ne uspije iz nekog razloga
	// this ce biti ime komande
	fprintf(stderr, "%s: Cant count chars/words/lines in '%s'\n"
	"ERROR: %s\n", this, filename, strerror(errno));
	
	exit(EXIT_FAILURE);
}

void print_usage(char *this)
{	// u slucaju da nije sintaksno tocno
	fprintf(stderr, "SYNTAX ERROR: \n"
	"USAGE %s [OPTION] [FILE]\n", this);
	
	exit(EXIT_FAILURE);
}


int brisanje_direktorija(char* path) // za prazne direktorije
{
	if(rmdir(path) == -1){
		print_error("rm: rmdir", path);
	}
	
	return 0;
}


int main(int argc, char* argv[])
{
	int c;
	FILE *file;
	struct stat stbuf1;
	int count = 0;
	char word[128];
	
	if(argv[1][0] != '-'){
		print_usage(argv[0]);
	}
	
	if(stat(argv[2], &stbuf1) == -1){ // ako datoteka za citanje ne postoji
		print_error(argv[0], argv[2]);
		return EXIT_FAILURE;
	}
	
	
	file = fopen(argv[0], "r");
	
	if (file == NULL) {
		printf("File cannot be opened\n");
		return EXIT_FAILURE;
	}

	if(strcmp(argv[1], "-c") == 0){
		while ((c = getc(file)) != EOF)
		if(c != ' ' || c != '\n' || c != '\t')
			count++;
		
		printf("Broj znakova u datoteci je: %d\n", count);
	}
	
	if(strcmp(argv[1], "-w") == 0){
		/*while ((c = getc(file)) != EOF)
			if(c == ' ' || c == '\n')*/
		
		while (fscanf(file, "%s", word) == 1)
			count++;
		
		printf("Broj \"rijeci\" u datoteci je: %d\n", count);
	}
	
	if(strcmp(argv[1], "-l") == 0){
		while ((c = getc(file)) != EOF)
		if(c == '\n')
			count++;
		
		printf("Broj linija u datoteci je: %d\n", count);
	}

	fclose(file);
	
	return 0;
}
