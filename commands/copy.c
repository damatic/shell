#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <linux/limits.h>

#define BUFFER_LENGTH 1024

void print_error(const char *this, const char *src_filename, const char *dest_filename)
{	// u slucaju da radnja ne uspije iz nekog razloga
	// this ce biti ime komande
	fprintf(stderr, "%s: cannot copy '%s' to '%s'\n"
	"error: %s\n", this, src_filename, dest_filename, strerror(errno));
	
	exit(EXIT_FAILURE);
}

void print_usage(const char *this)
{	// u slucaju da nije sintaksno tocno
	fprintf(stderr, "SYNTAX ERROR: \n"
	"USAGE %s [source] [destination]\n", this);
	
	exit(EXIT_FAILURE);
}

void copyFile(const char* src_file, char* dest_file) // kopiranje datoteka
{
	FILE *fd_src;
	FILE *fd_dest;
	size_t read_size, write_size;
	char buff[BUFFER_LENGTH];

	if((fd_src = fopen(src_file, "rb")) == NULL){
		print_error("copy", src_file, dest_file);
	}
	
	if((fd_dest = fopen(dest_file, "wb")) == NULL){
		fclose(fd_src);
		print_error("copy", src_file, dest_file);
	}
	
	do {
    	read_size = fread(buff, 1, sizeof(buff), fd_src); // citanje datoteke
    	if (read_size != 0) 
    		write_size = fwrite(buff, 1, read_size, fd_dest); // pisanje u datoteku
    	else   
    		write_size = 0;
	} while ((read_size > 0) && (read_size == write_size)); 
	
	if (write_size != 0) 
		perror("copy");
	
	if (fclose(fd_dest) == EOF) 
		print_error("copy", src_file, dest_file);
	if (fclose(fd_src) == EOF) 
		print_error("copy", src_file, dest_file);

}

void copyDirectory(const char* src_dir, char* dest_dir) 		// kopiranje direktorija - rekurzivno
{
	printf("Direktorij nije prazan\n");
}

int main(int argc, char* argv[])
{	
	char buffer[PATH_MAX];
	struct stat stbuf1, stbuf2;
	
	if(stat(argv[1], &stbuf1) == -1){ 					// ako source file/dir ne postoji
		print_error(argv[0], argv[1], argv[2]);
	}
	
	if((stbuf1.st_mode & S_IFMT) == S_IFREG){
		if((stat(argv[2], &stbuf2) == 0) && (stbuf2.st_mode & S_IFMT) == S_IFREG){ // ako je src datoteka
		// ako dest postoji i ako je datoteka
			copyFile(argv[1], argv[2]);
		}else if(((stbuf2.st_mode & S_IFMT) != S_IFDIR)){ 	// ako ne postoji file2
			copyFile(argv[1], argv[2]);						// a naveden je u putanji
		}else{ 
			strcpy(buffer, argv[2]);
			strcpy(buffer, "/");
			strcat(buffer, argv[1]);
			printf("BUFFER: %s\n", buffer);
			copyFile(argv[1], buffer);
		}
	}else if((stbuf1.st_mode & S_IFMT) == S_IFDIR){ // ako je direktorij
		copyDirectory(argv[1], argv[2]);
	}else{
		print_error(argv[0], argv[1], argv[2]);
	}
    
	return 0;
}

















