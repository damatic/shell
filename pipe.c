#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>


int main (void) {
    int fd[2];
	int a;
	
    pipe(fd);

    if (fork()) {
        // Child process
        dup2(fd[0], 0); // wc reads from the pipe
        close(fd[0]);
        close(fd[1]);
        execlp("wc", "wc", "-l", NULL);
    } else {
		if(fork()){
			// Parent process
			dup2(fd[1], 1); // grep writes to the pipe
			close(fd[0]);
			close(fd[1]);
			execlp("cat", "cat", "builtin.h", NULL);
		}
    }
	
    exit(EXIT_FAILURE);
	
	
	scanf("%d", &a);
	
	return 0;
}
	
	
	
	
	
	
	
	
	
	
