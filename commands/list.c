#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <string.h>
#include <linux/limits.h>
#include <errno.h>

#define __USE_XOPEN // potrebno za strptime javlja gresku bez njega
#define _GNU_SOURCE // -||-
#include <time.h>

#define BUFFER_LENGTH 1024

// ls samo imena
// ls -l imena, dozvole, veze, vlasnici bez . i ..
// ls -al imena, dozvole, veze, vlasnici sa . i ..
// ls -a imena i . i .. bez dozvola itd


// impelemtacija list naredbe bez primanja dodatnih argumenata

void print_error(const char *this, const char *filename)
{	// u slucaju da radnja ne uspije iz nekog razloga
	// this ce biti ime komande
	fprintf(stderr, "%s: cannot list directory '%s'\n"
					"ERROR: %s\n", this, filename, strerror(errno));
	
	exit(EXIT_FAILURE);
}

void print_usage(const char *this)
{	// u slucaju da nije sintaksno tocno
	fprintf(stderr, "SYNTAX ERROR: "
					"USAGE %s [path]\n", this);
	
	exit(EXIT_FAILURE);
}

void print_permissions(struct stat stbuf)
{	
	//printf("%o\t", mystat.st_mode & S_IWGRP);
    printf( (stbuf.st_mode & S_IRUSR) ? "r" : "-"); // vrati 400
    printf( (stbuf.st_mode & S_IWUSR) ? "w" : "-"); // vrati 200 itd
    printf( (stbuf.st_mode & S_IXUSR) ? "x" : "-"); // vrati 0 ako nema dozvole
    printf( (stbuf.st_mode & S_IRGRP) ? "r" : "-");
    printf( (stbuf.st_mode & S_IWGRP) ? "w" : "-");
    printf( (stbuf.st_mode & S_IXGRP) ? "x" : "-");
    printf( (stbuf.st_mode & S_IROTH) ? "r" : "-");
    printf( (stbuf.st_mode & S_IWOTH) ? "w" : "-");
    printf( (stbuf.st_mode & S_IXOTH) ? "x" : "-");
}

void print_without_option(struct dirent* myfile)
{
	printf("%s  ", myfile->d_name);
}

int main(int argc, char* argv[])
{
	DIR *mydir;
    struct dirent *myfile;
    struct stat stbuf;
	char buf[BUFFER_LENGTH];
	//char* last_modif_date;
	//struct tm tm;
	//struct passwd *pwd;
	//struct group *grp;

	
	if(argv[1] == NULL){ // u slucaju da nema argumenta poslije ls
		argv[1] = ".";
	}
	
    if((mydir = opendir(argv[1])) == NULL){
		print_error(argv[0], argv[1]);
	}
    
    while((myfile = readdir(mydir)) != NULL){
    	if(myfile->d_name[0] != '.'){
			sprintf(buf, "%s/%s", argv[1], myfile->d_name);
		    stat(buf, &stbuf);
			/*
			// dozvole nad datotekama
			print_permissions(stbuf);
		    
		    printf(" %ld", stbuf.st_nlink); // broj veza
		    
			pwd = getpwuid(stbuf.st_uid);
		    printf(" %s", pwd->pw_name); // ID of the owner of the file
		    
			grp = getgrgid(stbuf.st_gid);
		    printf(" %s", grp->gr_name); // ID of the group owner of the file
		    
		    // velicina datoteke
		    printf(" %ld",stbuf.st_size);
		    
		    // vrijeme zadnje promjene
			char buffer[BUFFER_LENGTH];
			
			last_modif_date = ctime(&stbuf.st_mtime);
			
			strptime(last_modif_date, "%a %b %d %H:%M:%S %Y", &tm);
			strftime(buffer, BUFFER_LENGTH, "%b %d %H:%M", &tm);
		    //printf("mjesec %d ", tm.tm_mon + 1);
			printf("\t%s", buffer);
		    
		    // ime datoteke
		    printf(" %s\n", myfile->d_name);*/
			
			print_without_option(myfile);
        }
    }
    printf("\n");
    closedir(mydir);
    
	return 0;
}
