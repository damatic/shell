#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h> // potrebno za fork()
#include <linux/limits.h> // potrebno za PATH_MAX
#include <sys/wait.h> // potrebno za wait()


// pipe radi, oba programa odrade posao, problem je kod pisanja, ne postoji EOF
void execArgsPiped(char* parsed[], char* parsedpipe[])
{
	int first_child_status;
	int second_child_status;
    int pipefd[2];
    pid_t pid1, pid2;
	char program_path[PATH_MAX] = "/home/matic/shell/commands/"; // potrebno upisati trenutnu putanju!!!
	
    if (pipe(pipefd) < 0) {
        perror("\nPipe could not be initialized!\n");
        return;
    }
	
    if ((pid1 = fork()) == -1) {
        perror("\nfork() failed\n");
        return;
    }

    if (pid1 == 0) { // child 2
        //printf("First child is writing to pipe...\n");	
		close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);
		
		strcat(program_path, parsed[0]);
        if (execvp(program_path, parsed) < 0) {
            perror("\nCould not execute command 1..\n");
            exit(1);
        }
    } else { // parent
		wait(&first_child_status); // cekanje da zavrsi prvo dijete
		
		if ((pid2 = fork()) == -1) { // drugi put fork(), iz istog roditelja
			perror("\nfork() failed\n");
			return;
		}
		if(pid2 == 0){ // child 2
			//printf("Second child is reading from pipe...\n");
			close(pipefd[1]);
			dup2(pipefd[0], STDIN_FILENO);
			close(pipefd[1]);
			
			strcat(program_path, parsedpipe[0]);
			if (execvp(program_path, parsedpipe) < 0) {
				perror("\nCould not execute command 2..\n");
				exit(1);
			}
		} // parent
		close(pipefd[0]); // potrebno zatvoriti jer i roditelj ima spojene file descriptore
		close(pipefd[1]); // potrebno zatvoriti jer i roditelj ima spojene file descriptore
		wait(&second_child_status);
	}
}