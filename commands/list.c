#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <string.h>

#define __USE_XOPEN // potrebno za strptime javlja gresku bez njega
#define _GNU_SOURCE // -||-
#include <time.h>
#include "../builtin.h"

// ls samo imena
// ls -l imena, dozvole, veze, vlasnici bez . i ..
// ls -all imena, dozvole, veze, vlasnici sa . i ..
// ls -a imena i . i .. bez dozvola itd


int main(int argc, char* argv[])
{
	
	DIR *mydir;
    struct dirent *myfile;
    struct stat mystat;
	char buf[512];
	char* last_modif_date;
	struct tm tm;
	struct passwd *pwd;
	struct group *grp;

	

	if(argv[1] == NULL){ // u slucaju da nema argumenta poslije ls
		argv[1] = ".";
	}
		
	//printf("Broj argumenata: %d, %s %s\n", argc, argv[0], argv[1]);
	
    mydir = opendir(argv[1]);
    
    while((myfile = readdir(mydir)) != NULL){
    	if(myfile->d_name[0] != '.'){
			sprintf(buf, "%s/%s", argv[1], myfile->d_name);
		    stat(buf, &mystat);

			
		    // dozvole nad datotekama
		    //printf("%o\t", mystat.st_mode & S_IWGRP);		    
		    printf( (mystat.st_mode & S_IRUSR) ? "r" : "-"); // vrati 400
		    printf( (mystat.st_mode & S_IWUSR) ? "w" : "-"); // vrati 200 itd
		    printf( (mystat.st_mode & S_IXUSR) ? "x" : "-"); // vrati 0 ako nema dozvole
		    printf( (mystat.st_mode & S_IRGRP) ? "r" : "-");
		    printf( (mystat.st_mode & S_IWGRP) ? "w" : "-");
		    printf( (mystat.st_mode & S_IXGRP) ? "x" : "-");
		    printf( (mystat.st_mode & S_IROTH) ? "r" : "-");
		    printf( (mystat.st_mode & S_IWOTH) ? "w" : "-");
		    printf( (mystat.st_mode & S_IXOTH) ? "x" : "-");
		    
		    printf(" %ld", mystat.st_nlink); // broj veza
		    
			pwd = getpwuid(mystat.st_uid);
		    printf(" %s", pwd->pw_name); // ID of the owner of the file
		    
			grp = getgrgid(mystat.st_gid);
		    printf(" %s", grp->gr_name); // ID of the group owner of the file
		    
		    // velicina datoteke
		    printf(" %ld",mystat.st_size);
		    
		    // vrijeme zadnje promjene
			char buffer[125];
			
			last_modif_date = ctime(&mystat.st_mtime);
			
			strptime(last_modif_date, "%a %b %d %H:%M:%S %Y", &tm);
			strftime(buffer, 125, "%b %d %H:%M", &tm);
		    //printf("mjesec %d ", tm.tm_mon + 1);
			printf("\t%s", buffer); // potrebno popraviti..##########POPRAVKA##########
		    
		    // ime datoteke
		    printf(" %s\n", myfile->d_name);
        }
    }
    
    closedir(mydir);
    // printf("list exited\n");
    
	return 0;
}
