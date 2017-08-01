#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

int main(int argc, char* argv[])
{
	
	DIR *mydir;
    struct dirent *myfile;
    struct stat mystat;
	char buf[512];
	
	if(argc == 1){ // u slucaju da nema argumenta poslije ls
		argv[1] = ".";
	}
	printf("Broj argumenata: %d\n", argc);
	
    mydir = opendir(argv[1]);
    
    
    while((myfile = readdir(mydir)) != NULL)
    {
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
		    
		    // velicina datoteke
		    printf("\t%ld",mystat.st_size);
		    
		    // vrijeme zadnje promjene
		    printf("\t%ld", mystat.st_atime);
		    
		    // ime datoteke
		    printf("\t%s\n", myfile->d_name);
        }
    }
    
    closedir(mydir);
    
	return 0;
}
