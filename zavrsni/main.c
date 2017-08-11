#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <linux/limits.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include "builtin.h"


#define BUFFER_LENGTH 1024 // velicina buffera

/*
int initialize_shell()
{
	char path[256] = "/home/stingy/Desktop/zavrsni/commands/";
	char program_path[PATH_MAX];
	char line[BUFFER_LENGTH];
	char* argv[256];
	
	void (*fbuiltin_ptr_arr[])(char**) = {
		&exit_shell, 
		&echo, cdir, 
		&pwd, 
		&clear_terminal
	};
}
*/


int main()
{	
	pid_t pid;
	char path[256] = "/home/stingy/Desktop/zavrsni/commands/";
	char program_path[PATH_MAX];
	char line[BUFFER_LENGTH];
	char* argv[256];
	char* token;
	int i = 0;
	int argc = 0;
	size_t length;
	
	char *builtin_str[] = {
  		"cd",
  		"help",
  		"exit"
	};

	
	// dodati cd, clear, pwd...
	while(1){
		strcpy(program_path, path);
	
		printf("test >> ");
		pwd(); // probno path
		
		if (fgets(line, BUFFER_LENGTH, stdin) == 0){ // u slucaju da je ^D End-Of-File
			return 1;
		}
		
		if (line[0] == '\n') { // prazna komanda
			printf("empty command!!!\n");
  		}else{
  			length = strlen(line);
  			
			if (line[length - 1] == '\n'){ // brise oznaku za novi red
				line[length - 1] = '\0';
			}		
		
	  		if(strcmp(line, "exit") == 0){ // probno exit
		    	exit_shell();
			}
			
			if(strcmp(line, "clear") == 0){ // probno clear
		    	clear_terminal();
			}

			token = strtok(line, " \n\t()<>|&;");
			while(token != NULL && i < 256){
				argv[i] = token;
				token = strtok(NULL, " \n\t()<>|&;"); // " \n\t()<>|&;" znakovi koje "ignorira"
				i++;
			}
			
			if(strcmp(argv[0], "cdir") == 0){ // probno change directory
		    	cdir(argv[1]);
			}else
			
			argc = i;
			argv[i] == NULL; // potrebno zbog execvp, da se zna gdje je kraj
			strcat(program_path, argv[0]); // spajanje putanje programa
			
			pid = fork();
			if(pid == 0){ // child process
				
				if (execvp(program_path, argv) == -1)
                {
                    printf("ERRNO: %s\n", strerror(errno));
                    _exit(0);
                }
			}else{ // parrent process
				wait(NULL);
		    	// postavljanje svih varijabli na pocetno stanje
		    	argv[0] = 0;
		    	line[0] = '\0';
				length = 0;
				argc = 0;
				i = 0;
				//printf("Child exited\n");
			}
		}
	}
	return 0;
}





















