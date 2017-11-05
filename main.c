/*
#################################################################
#																#	
#		Description: Linux ljuska u c programskom jeziku		#
#		Author: Danijel Matic									#
#		Unversity: Sveucilisni odjel za strucne studije			#
#																#
#																#
#																#
#################################################################
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <linux/limits.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include "builtin.h"
#include "pipe.h"


#define BUFFER_LENGTH 1024 // velicina buffera
#define BUFFER_SIZE_FOR_NAMES 124
#define ARGUMENT_SIZE 50
//  strsep(“|”)


int main()
{
	pid_t pid;
	char program_path[PATH_MAX] = "/home/matic/shell/commands/"; // korisnik postaviti svoju putanju!!!!
	char line[BUFFER_LENGTH];
	char* argv[ARGUMENT_SIZE];
	char* token;
	int child_status;
	int argc = 0;
	size_t length;
	char hostname[BUFFER_SIZE_FOR_NAMES] = "slash";
	char* username = "matic";
	char* hostname_file = "/home/matic/shell/hostname_test";
	char line_builtin[BUFFER_LENGTH];

	while(1){
		//printf("START\n");
		while(1){
			init_shell(hostname, hostname_file);
			//strcpy(program_path, path);
		
			printf("%s@%s >> ", username, name(hostname_file));
					
			if (fgets(line, BUFFER_LENGTH, stdin) == 0) // u slucaju da je ^D End-Of-File
				return 1;

			if (line[0] == '\n') { // prazna komanda
				printf("empty command!!!\n");
				break;
			}
			
			history_shell(line);
			
			if(strcmp(line, "pipe\n") == 0){
				char* argpipe1[1024] = { "cat", "builtin.h", NULL };
				char* argpipe2[1024] = { "wc", "-c", NULL};
				
				execArgsPiped(argpipe1, argpipe2);

				argv[0] = 0;
				line[0] = '\0';
				length = 0;
				argc = 0;
				strcpy(program_path, "/home/matic/shell/commands/");
				break;
			}
			
			length = strlen(line);
			if (line[length - 1] == '\n'){ // brise oznaku za novi red
				line[length - 1] = '\0';
			}		
			
			strcpy(line_builtin, line); // posebno za builtin programe, da ne dira izvorni string
			if(check_builtin(line_builtin) == 1){
				argv[0] = 0;
				line[0] = '\0';
				length = 0;
				argc = 0;
				strcpy(program_path, "/home/matic/shell/commands/");
				break;
			}
			
			token = strtok(line, " \n\t()<>|&;");
			while(token != NULL && argc < 256){
				argv[argc] = token;
				token = strtok(NULL, " \n\t()<>|&;"); // " \n\t()<>|&;" znakovi koje "ignorira"
				argc++;
			}
						
			argv[argc] = NULL; // potrebno zbog execvp, da se zna gdje je kraj niza argumenata
			strcat(program_path, argv[0]); // spajanje putanje gdje se nalaze programi i samog imena programa

			if((pid = fork()) == -1){
				perror("fork() failed!");
				argv[0] = 0;
				line[0] = '\0';
				length = 0;
				argc = 0;
				strcpy(program_path, "/home/matic/shell/commands/");
				break;
			}
			
			if(pid == 0){ // child process
				if (execvp(program_path, argv) == -1){
						printf("ERRNO: %s\n", strerror(errno));
						exit(1);
				}
			}else{ // parrent process
			// cekanje da dijete proces zavrsi sa dodatnim informacijama, pomocu MACRO-a provjera
				wait(&child_status); 
				//printf("Child exited\n");
				argv[0] = 0;
				line[0] = '\0';
				length = 0;
				argc = 0;
			}
			argv[0] = 0;
			line[0] = '\0';
			length = 0;
			argc = 0;
			strcpy(program_path, "/home/matic/shell/commands/");
		}
	}
	return 0;
}





















