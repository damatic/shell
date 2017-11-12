#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <linux/kdev_t.h>
#include <errno.h>


#define BUFFER_LENGTH 1024
#define BUFFER_SIZE_FOR_NAMES 50


void print_error(char *this)
{	// u slucaju da radnja ne uspije iz nekog razloga
	// this ce biti ime komande
	fprintf(stderr, "%s: cannot list informations about processes\n"
	"ERROR: %s\n", this, strerror(errno));
	
	exit(EXIT_FAILURE);
}

void print_usage(char *this)
{	// u slucaju da nije sintaksno tocno
	fprintf(stderr, "SYNTAX ERROR: \n"
	"USAGE %s\n", this);
	
	exit(EXIT_FAILURE);
}

int main(int argc, char* argv[])
{
	DIR *mydir;
	FILE* fp;
	struct dirent *myfile;
	char buff[BUFFER_LENGTH] = "/proc/";
	int pid;
	char cmd[BUFFER_SIZE_FOR_NAMES];
	char state;
	char* token_cmd;
	char ignore[BUFFER_SIZE_FOR_NAMES];
	int tty_nr;
	char str_tty[BUFFER_SIZE_FOR_NAMES];
	//int starttime;
	
    if ((mydir = opendir("/proc")) == NULL){
        print_error(argv[0]);
    }
	
	printf("%5s %6s %s %7s\n", "PID", "TTY", "STATE", "COMMAND"); // formatiranje headera
	
    while((myfile = readdir(mydir)) != NULL){ 	// otvaranje direktorija /proc
        if (isdigit(myfile->d_name[0])){ 		// provjera je li prvi znak broj
			strcat(buff, myfile->d_name);		
			strcat(buff, "/stat");				// rezultat spajanja putanje /proc/PID/comm gdje se nalazi naziv naredbe
			fp = fopen(buff, "r");
			fscanf(fp, "%d %s %c %s %s %s %d", &pid, cmd, &state, ignore, ignore, ignore, &tty_nr);
			token_cmd = strtok(cmd, "()");
			
			printf("%5d", pid);
			
			if(MAJOR(tty_nr) == 0){				// izdvajanje bitova za osnovni uređaj pts, tty...
				printf(" %6s", "?");
			}else{
				sprintf(str_tty, "%d:%d", MAJOR(tty_nr), MINOR(tty_nr));
				printf(" %6s", str_tty);
			}
			printf(" %c", state);
			
			printf("     %s\n", token_cmd);
			
			fclose(fp);
        }
		strcpy(buff, "/proc/");					// postavljanje na pocetno buff
    }
	closedir(mydir);
	
	return 0;
}