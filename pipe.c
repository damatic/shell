#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h> 		// needed for fork()
#include <linux/limits.h> 	// needed for PATH_MAX
#include <sys/wait.h> 		// needed for wait()


void execArgsPiped(char* parsed[], char* parsedpipe[])
{
	int first_child_status;
	int second_child_status;
    int pipefd[2];
    pid_t pid1, pid2;
	char program_path[PATH_MAX];
	
	strcpy(program_path, getenv("HOME"));
	strcat(program_path, "/shell/obj_output/");
	
    if (pipe(pipefd) < 0) {
        perror("\nPipe could not be initialized!\n");
        return;
    }
	
    if ((pid1 = fork()) == -1) {
        perror("\nfork() failed\n");
        return;
    }

    if (pid1 == 0) { // child process 1	
		close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);
		
		strcat(program_path, parsed[0]);
        if (execvp(program_path, parsed) < 0) {
            perror("\nCould not execute command 1..\n");
            exit(1);
        }
    } else { // parent process
		wait(&first_child_status); // waiting for first child process to end
		
		if ((pid2 = fork()) == -1) { //second time fork(), from the same parent process
			perror("\nfork() failed\n");
			return;
		}
		if(pid2 == 0){ // child process 2
			close(pipefd[1]);
			dup2(pipefd[0], STDIN_FILENO);
			close(pipefd[1]);
			
			strcat(program_path, parsedpipe[0]);
			if (execvp(program_path, parsedpipe) < 0) {
				perror("\nCould not execute command 2..\n");
				exit(1);
			}
		} // parent process
		close(pipefd[0]); // close because parent proces shave connected file descriptors
		close(pipefd[1]); // close because parent process have connected file descriptors
		wait(&second_child_status);
	}
}