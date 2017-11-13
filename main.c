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
#include "readerParser.h"

#include <readline/readline.h>
#include <readline/history.h>

#define BUFFER_LENGTH 1024
#define BUFFER_SIZE_FOR_NAMES 50
#define ARGUMENT_SIZE 50

int main()
{
	init* data;
	
	//rl_bind_key('\t', rl_abort);//disable auto-complete
	
	while(1){
		while(1){
			data = init_shell();
			init_hostname(data->hostname, data->hostname_file);
			
			sprintf(data->buffer_prompt, "%s@%s >> ", data->username, name(data->hostname_file)); // prompt - matic@slash >> 
			
			/*if (fgets(data->line, BUFFER_LENGTH, stdin) == 0){ // u slucaju da je ^D End-Of-File
				printf("exit\n");
				return 1;
			}*/
			if (data->line){
				free (data->line);
				data->line = (char *)NULL;
			}
			
			data->line = readline(data->buffer_prompt); // inicijalizacija readline programa
			
			if (data->line[0] == EOF){ // u slucaju da je ^D End-Of-File
				printf("exit\n");
				return 1;
			}
			
			if (data->line && *(data->line)) // sprema povijest naredbi, sve razlicito od prazne linije
				add_history(data->line);
			
			strcpy(data->temp_buffer, data->line);
			if (strtok(data->temp_buffer, " \t\n") == NULL) { // prazna komanda
				printf("empty command!!!\n");
				break;
			}
			
			history_shell(data->line);
			
			data->length = strlen(data->line);
			if (data->line[data->length - 1] == '\n'){ // brise oznaku za novi red
				data->line[data->length - 1] = '\0';
			}
			
			strcpy(data->line_builtin, data->line); // posebno za builtin programe, da ne dira izvorni string
			if(check_builtin(data->line_builtin) == 1){
				cleaning(data);
				break;
			}
			
			data->token = strtok(data->line, " \n\t()<>;");
			while(data->token != NULL && data->argc1 < 256 && data->argc2 < 256){
				if(strcmp(data->token, "|") == 0){
					data->count_pipe = 1;
				}else{
					if(data->count_pipe == 0){
						data->argv1[data->argc1] = data->token;
						data->argc1++;
					}
					if(data->count_pipe == 1){
						data->argv2[data->argc2] = data->token;
						data->argc2++;
					}
				}
				data->token = strtok(NULL, " \n\t()<>;"); // " \n\t()<>|&;" znakovi koje "ignorira"
			}

			if(data->count_pipe > 0){
				data->argv1[data->argc1] = NULL;
				data->argv2[data->argc2] = NULL;

				execArgsPiped(data->argv1, data->argv2);
				cleaning(data);
				break;
			}
			
			data->argv1[data->argc1] = NULL; // potrebno zbog execvp, da se zna gdje je kraj niza argumenata
			strcat(data->program_path, data->argv1[0]); // spajanje putanje gdje se nalaze programi i samog imena programa
			if((data->pid = fork()) == -1){
				cleaning(data);
				break;
			}
			
			if(data->pid == 0){ // child process
				if(execvp(data->program_path, data->argv1) == -1){
					printf("ERRNO: %s\n", strerror(errno));
					exit(1);
				}

			}else{ // parrent process
			// cekanje da dijete proces zavrsi sa dodatnim informacijama, pomocu MACRO-a provjera
				//wait(&child_status);
				wait(NULL);
				cleaning(data);
			}
		}
	}
	
	free(data->line);
	
	return 0;
}





















