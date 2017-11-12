#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "readerParser.h"


init* init_shell()  // init data
{
	init* data;
	
	data = (init*)malloc(sizeof(init));
	
	strcpy(data->program_path, "/home/matic/shell/commands/");  // korisnik postaviti svoju putanju!!!!
	strcpy(data->hostname_file, "/home/matic/shell/hostname_test");
	strcpy(data->hostname, "slash");
	strcpy(data->username, "matic");
	data->line[0] = '\0';
	
	return data;
}

char* readLineCommand(void)
{
	return NULL;
}

void parseCommandAndExecute(char* commandLine)
{

}

int parseInfo()
{
	return 0;
}

void cleaning(init* data)
{
	free(data);
	data = NULL;
	
	init_shell(data);
}
