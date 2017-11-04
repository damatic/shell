/*
#########################################################
#	
#	VAŽNO!!!!
#	
#	trenutno je wc napravljen samo preko pipe-a
#	program cita sa stdin-a i pise u datoteku,
#	zatim program cita iz datoteke i provjerava 
#	ovisno o argumentima, razlog je jer stdin nema EOF,
#	vjerojatno pipe kod zatvaranja file descriptor-a...
#	
#	
#	
*/

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




int main(int argc, char* argv[])
{
	int c;
	FILE *file;
	//struct stat stbuf1;
	int count = 0;
	char word[128];
	char input[4096];
	int i = 0;
	
	
	if(argv[1][0] != '-'){
		print_usage(argv[0]);
	}
	
	/*if(stat(argv[2], &stbuf1) == -1){ // ako datoteka za citanje ne postoji
		print_error(argv[0], argv[2]);
		return EXIT_FAILURE;
	}*/
	
	file = fopen("pipetest", "w");
	
	/*if (file == NULL) {
		printf("File cannot be opened\n");
		return EXIT_FAILURE;
	}*/
	
	while(fgets(input, sizeof(input), stdin) && i < 13){ // problem s EOF-om pa je zbog toga "i < 13" granica...
		fprintf(file, "%s", input);
		i++;
	}

	fclose(file);
	file = fopen("pipetest", "r");
	
	if(strcmp(argv[1], "-c") == 0){
		while ((c = getc(file)) != EOF){
			if(c != ' ' && c != '\n' && c != '\t')
				count++;
		}
		printf("Broj znakova u datoteci je: %d\n", count);
		
		return 0;
	}
	
	if(strcmp(argv[1], "-w") == 0){
		/*while ((c = getc(file)) != EOF)
			if(c == ' ' || c == '\n')*/
		
		while(fscanf(file, "%s", word) == 1){
			count++;
		}
		printf("Broj \"rijeci\" u datoteci je: %d\n", count);
		
		return 0;
	}
	
	if(strcmp(argv[1], "-l") == 0){
		while ((c = getc(file)) != EOF){
			if(c == '\n')
				count++;
		}
		printf("Broj linija u datoteci je: %d\n", count);
		
		return 0;
	}

	fclose(file);
	
	return 1;
}
