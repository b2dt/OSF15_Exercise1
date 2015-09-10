#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "command.h"

#define MAX_CMD_COUNT 50
#define MAX_CMD_LEN 25


	//TODO FUNCTION COMMENT
/*
Purpose: to parse the user input and determine if it was correct input
Input: the input from the user
       the cmd array of different possible commands
Return: true if the command was valid
        false if the command was not valid
*/
bool parse_user_input (const char* input, Commands_t** cmd) {
	
	//TODO ERROR CHECK INCOMING PARAMETERS
	if (!input || !cmd)
	{
		return false;
	}

	char *string = strdup(input);
	
	*cmd = calloc (1,sizeof(Commands_t));
	(*cmd)->cmds = calloc(MAX_CMD_COUNT,sizeof(char*));

	unsigned int i = 0;
	char *token;
	token = strtok(string, " \n");
	for (; token != NULL && i < MAX_CMD_COUNT; ++i) {
		(*cmd)->cmds[i] = calloc(MAX_CMD_LEN,sizeof(char));
		if (!(*cmd)->cmds[i]) {
			perror("Allocation Error\n");
			return false;
		}	
		strncpy((*cmd)->cmds[i],token, strlen(token) + 1);
		(*cmd)->num_cmds++;
		token = strtok(NULL, " \n");
	}
	free(string);
	return true;
}

	//TODO FUNCTION COMMENT
/*
Purpose: To deallocate memory associated with the cmd array
Input: the cmd array
Return: void
*/
void destroy_commands(Commands_t** cmd) {

	//TODO ERROR CHECK INCOMING PARAMETERS
	if (!cmd)
	{
		return;
	}
	for (int i = 0; i < (*cmd)->num_cmds; ++i) {
		free((*cmd)->cmds[i]);
	}
	free((*cmd)->cmds);
	free((*cmd));
	*cmd = NULL;
}

