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

// TO DO:
// ls only names
// ls -l names, permissions, relations, owners wtih . and ..
// ls -all names, permissions, relations, owners with . and ..
// ls -a names with . and .. without permissions etc

// implementation of list command without additional argumets

void print_error(const char *this, const char *filename)
{	// in case if command fails for some reason
	// this will be name of the command
	fprintf(stderr, "%s: cannot list directory '%s'\n"
					"ERROR: %s\n", this, filename, strerror(errno));
	
	exit(EXIT_FAILURE);
}

void print_usage(const char *this)
{	// if syntax of command is not correct
	fprintf(stderr, "SYNTAX ERROR: "
					"USAGE %s [path]\n", this);
	
	exit(EXIT_FAILURE);
}

void print_permissions(struct stat stbuf)
{	
	//printf("%o\t", mystat.st_mode & S_IWGRP);
    printf( (stbuf.st_mode & S_IRUSR) ? "r" : "-"); // returns 400
    printf( (stbuf.st_mode & S_IWUSR) ? "w" : "-"); // returns 200 etc
    printf( (stbuf.st_mode & S_IXUSR) ? "x" : "-"); // returns 0 if there is no permission
    printf( (stbuf.st_mode & S_IRGRP) ? "r" : "-");
    printf( (stbuf.st_mode & S_IWGRP) ? "w" : "-");
    printf( (stbuf.st_mode & S_IXGRP) ? "x" : "-");
    printf( (stbuf.st_mode & S_IROTH) ? "r" : "-");
    printf( (stbuf.st_mode & S_IWOTH) ? "w" : "-");
    printf( (stbuf.st_mode & S_IXOTH) ? "x" : "-");
}

int main(int argc, char* argv[])
{
	DIR *mydir;
    struct dirent *myfile;
    struct stat stbuf;
	char buf[BUFFER_LENGTH];
	char* last_modif_date;
	struct tm tm;
	struct passwd *pwd;
	struct group *grp;

	
	if(argv[1] == NULL){ // in case there is no argument after ls command
		argv[1] = ".";
	}
	
    if((mydir = opendir(argv[1])) == NULL){
		print_error(argv[0], argv[1]);
	}
    
    while((myfile = readdir(mydir)) != NULL){
    	if(myfile->d_name[0] != '.'){
			sprintf(buf, "%s/%s", argv[1], myfile->d_name);
		    stat(buf, &stbuf);

			// permissions over directories
			print_permissions(stbuf);
		    
		    printf(" %ld", stbuf.st_nlink); // number of relations
		    
			pwd = getpwuid(stbuf.st_uid);
		    printf(" %s", pwd->pw_name); // ID of the owner of the file
		    
			grp = getgrgid(stbuf.st_gid);
		    printf(" %s", grp->gr_name); // ID of the group owner of the file
		    
		    // size of a directory
		    printf(" %ld",stbuf.st_size);
		    
		    // time of the last change
			char buffer[BUFFER_LENGTH];
			
			last_modif_date = ctime(&stbuf.st_mtime);
			
			strptime(last_modif_date, "%a %b %d %H:%M:%S %Y", &tm);
			strftime(buffer, BUFFER_LENGTH, "%b %d %H:%M", &tm);
		    //printf("montj %d ", tm.tm_mon + 1);
			printf("\t%s", buffer);
		    
		    // directory nema
		    printf(" %s\n", myfile->d_name);
        }
    }
    
    closedir(mydir);
    
	return 0;
}
