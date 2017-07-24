#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <linux/limits.h>



void print_error(char *this, char *src_filename, char *dest_filename)
{	// u slucaju da radnja ne uspije iz nekog razloga
	// this ce biti ime komande
	fprintf(stderr, "%s: cannot copy '%s' to '%s'\n"
	"error: %s\n", this, src_filename, dest_filename, strerror(errno));
	
	exit(EXIT_FAILURE);
}

void print_usage(char *this)
{	// u slucaju da nije sintaksno tocno
	fprintf(stderr, "SYNTAX ERROR: \n"
	"USAGE %s [source] [destination]\n", this);
	
	exit(EXIT_FAILURE);
}

int copyFile(char* src_file, char* dest_file) // kopiranje datoteka
{
	FILE *fd_src;
	FILE *fd_dest;
	size_t read_size, write_size;
	unsigned char buff[8192];
	
	fd_src = fopen(src_file, "rb");
	if(fd_src == NULL){
		perror("file open for reading");
		return EXIT_FAILURE;
	}
	
	fd_dest = fopen(dest_file, "wb");
	if(fd_dest == NULL){
		fclose(fd_src);
		perror("file open for writing");
		return EXIT_FAILURE;
	}
	
	
	do {
    	read_size = fread(buff, 1, sizeof(buff), fd_src);
    	if (read_size != 0) 
    		write_size = fwrite(buff, 1, read_size, fd_dest);
    	else   
    		write_size = 0;
	} while ((read_size > 0) && (read_size == write_size));
	
	if (write_size != 0) 
		perror("copy");
	
	if (fclose(fd_dest)) 
		perror("close output file");
	if (fclose(fd_src)) 
		perror("close input file");

	return 0;
}

int copyDirectory(char* src_dir, char* dest_dir) // kopiranje direktorija - rekurzivno
{
	// potrebna implementacija!!!!
	
	return 0;
}

int main(int argc, char* argv[])
{	
	//errno = 0; // potrebno postavit, trenutno nema greski
	//printf("%d\n", argc);
	
	char buffer[PATH_MAX];
	struct stat stbuf1;
	struct stat stbuf2;
	
	if(stat(argv[1], &stbuf1) == -1){ // ako source file/dir ne postoji
		print_error(argv[0], argv[1], argv[2]);
		return EXIT_FAILURE;
	}else{
		if((stbuf1.st_mode & S_IFMT) == S_IFREG){
		// (S_ISREG(sb.st_mode)) macro:)
		// ako je src datoteka
			if((stat(argv[2], &stbuf2) == 0) && (stbuf2.st_mode & S_IFMT) == S_IFREG){
			// ako dest postoji i ako je datoteka
				//printf("f1 i f2 postoje i datoteke su\n");
				copyFile(argv[1], argv[2]);
			}else if(((stbuf2.st_mode & S_IFMT) != S_IFDIR)){ // ako ne postoji file2
				copyFile(argv[1], argv[2]);					//a naveden je u putanji
			}else{ // ako ne postoji 
				strcpy(buffer, argv[2]);
				//strcat(buffer, "/");
				strcat(buffer, argv[1]);
				printf("BUFFER: %s\n", buffer);
				copyFile(argv[1], buffer);
			}
		}else if((stbuf1.st_mode & S_IFMT) == S_IFDIR){
			copyDirectory(argv[1], argv[2]);
		}else{
			print_error(argv[0], argv[1], argv[2]);
		}
	}

    
    
	return EXIT_SUCCESS;
}






















