#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <linux/limits.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

#define BUFFER_LENGTH 1024

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
	
	while(1){
		strcpy(program_path, path);
	
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
				token = strtok(NULL, " \n\t()<>|&;");
				i++;
			}
			
			argv[i] == NULL;
			printf("Prije: %s\n", program_path);
			strcat(program_path, argv[0]);
			printf("Poslije: %s\n", program_path);
			
			//printf("%s\n", program_path); // ispis putanje programa
			
			argc = i;

			/*for(i = 0; i < argc; i++){ // ispis argumenata
				printf("%s\n", argv[i]);
			}*/
			
			pid = fork();
			if(pid == 0){ // child process
				
				if (execvp(program_path, argv) == -1)
                {
                    printf("ERRNO: %s\n", strerror(errno));
                    _exit(1);
                }
			}else{ // parrent process
				wait(NULL);
		    	
		    	//program_path[PATH_MAX] = "/home/stingy/Desktop/zavrsni/commands/";
		    	// postavljanje svih varijabli na pocetno stanje
		    	argv[0] = 0;
		    	line[0] = '\0';
				length = 0;
				argc = 0;
				i = 0;
				//printf("Child exited\n");
			}
		}
		//printf("%s\n", program_path);
	}
	return EXIT_SUCCESS;
}


TEST TEST LUKAAAA




















