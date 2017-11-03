#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

int main()
{
	DIR *mydir;
	FILE* fp;
	struct dirent *myfile;
	char buff[1024] = "/proc/";
	
	
    if ((mydir = opendir("/proc")) == NULL){
        perror("/proc");
        exit(1);
    }
	
	printf("%5s %s %11s %s\n", "PID", "TTY", "TIME", "CMD"); // formatiranje headera
	
    while((myfile = readdir(mydir)) != NULL){ 	// otvaranje direktorija /proc
        if (isdigit(myfile->d_name[0])){ 		// provjera je li prvi znak broj
			printf("%5s", myfile->d_name);		// ispis imena odnosno PID procesa
			printf(" ?");
			printf("%14s", "00:00:00");			// hardcode time, ne radi
			strcat(buff, myfile->d_name);		// 
			strcat(buff, "/comm");				// rezultat spajanja putanje /proc/PID/comm gdje se nalazi naziv naredbe
			
			fp = fopen(buff, "r");
			fscanf(fp, "%s", buff);
			printf(" %s\n", buff);
			fclose(fp);
        }
		strcpy(buff, "/proc/");					// postavljanje na pocetno buff
    }
	closedir(mydir);
	
	return 0;
}