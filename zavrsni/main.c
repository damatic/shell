#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <linux/limits.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFER_LENGTH 1024

int main()
{	
	pid_t pid;
	char program_path[PATH_MAX] = "/home/stingy/Desktop/zavrsni/commands/";
	char line[BUFFER_LENGTH];
	char* argv[256];
	char* token;
	int i = 0;
	int argc = 0;
	size_t length;
	
	
	while(1){
	
		printf("test >> ");

		if (fgets(line, BUFFER_LENGTH, stdin) == 0){
			return 1;
		}
		if (line[0] == '\n') { // prazna komanda
			printf("empty command!!!\n");
    		continue;
  		}else{
  			length = strlen(line);
  			
			if (line[length - 1] == '\n'){
				line[length - 1] = '\0';
			}		
		
	  		if(strcmp(line, "exit") == 0){ // u slucaju da je exit
		    	return 1;
			}

			token = strtok(line, " ");
			while(token != NULL && i < 256){
				argv[i] = token;
				token = strtok(NULL, " ");
				i++;
			}
			
			argv[i] == NULL;
			strcat(program_path, argv[0]);
			
			//printf("%s\n", program_path); // ispis putanje programa
			
			argc = i;

			/*for(i = 0; i < argc; i++){ // ispis argumenata
				printf("%s\n", argv[i]);
			}*/
			
			pid = fork();
			if(pid == 0){ // child process
				execvp(program_path, argv);
				fprintf(stderr, "Child process could not do execvp\n");
			}else{ // parrent process
				wait(NULL);
		    	printf("Child exited\n");
		    	program_path[0] = 0;
		    	argv[0] = 0;
		    	line[0] = 0;
				length = 0;
				argc = 0;
				i = 0;
			}
		}
		//printf("%s\n", program_path);
	}
    
	return EXIT_SUCCESS;
}






















