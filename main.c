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

#define BUFFER_LENGTH 1024 // velicina buffera
#define BUFFER_SIZE_FOR_NAMES 124
#define ARGUMENT_SIZE 50
//  strsep(“|”)


// pipe radi, oba programa odrade posao, problem je kod citanja izlaza, ne postoji EOF
void execArgsPiped(char* parsed[], char* parsedpipe[])
{
	// execlp("cat", "cat", "builtin.h", NULL)
	// execlp("wc", "wc", "-w", NULL)
	// execvp(program_path, parsed)
	// execvp(program_path, parsedpipe)
	
	int first_child_status;
	int second_child_status;
	//int extstatus;
    int pipefd[2];
    pid_t pid1, pid2;
	char program_path[PATH_MAX] = "/home/matic/shell/commands/"; // potrebno upisati trenutnu putanju!!!
	
    if (pipe(pipefd) < 0) {
        printf("\nPipe could not be initialized!\n");
        return;
    }

    if ((pid1 = fork()) == -1) {
        printf("\nfork() failed\n");
        return;
    }

    if (pid1 == 0) {
        printf("First child is writing to pipe...\n");
		close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);
        
		strcat(program_path, parsed[0]);
        if (execvp(program_path, parsed) < 0) {
            printf("\nCould not execute command 1..\n");
            exit(1);
        }
		
    } else {
		wait(&first_child_status); // cekanje da zavrsi prvo dijete

		/*if (WIFEXITED(first_child_status) == 0)
			printf("exit status = %d\n", WEXITSTATUS(first_child_status));*/
		
		if ((pid2 = fork()) == -1) { // drugi put fork(), iz istog roditelja
			printf("\nfork() failed\n");
			return;
		}
		
		if(pid2 == 0){
			printf("Second child is reading from pipe...\n");
			close(pipefd[1]);
			dup2(pipefd[0], STDIN_FILENO);
			close(pipefd[0]);
			
			strcat(program_path, parsedpipe[0]);
			if (execvp(program_path, parsedpipe) < 0) {
				printf("\nCould not execute command 2..\n");
				exit(1);
			}
		}
		wait(&second_child_status);
	}
}

int check_builtin(char *line)
{
	char *argv[ARGUMENT_SIZE];
	int argc = 0;
	char* token;
	
	
	token = strtok(line, " \n\t()<>|&;");
	while(token != NULL && argc < 256){
		argv[argc] = token;
		token = strtok(NULL, " \n\t()<>|&;"); // " \n\t()<>|&;" znakovi koje "ignorira"
		argc++;
	}
	
	argv[argc] = NULL;

	if(strcmp(line, "exit") == 0){
		exit_shell();
		return 1;
	}else if(strcmp(line, "cdir") == 0){
		cdir(argv[1]);
		return 1;
	}else if(strcmp(line, "pwd") == 0){
		pwd();
		return 1;
	}else if(strcmp(line, "clear") == 0){
		clear_terminal();
		return 1;
	}else if(strcmp(line, "echo") == 0){
		echo(argv[1]);
		return 1;
	}
	
	return 0;	
}

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
			}
			argv[0] = 0;
			line[0] = '\0';
			length = 0;
			argc = 0;
		}
	}
	return 0;
}





















