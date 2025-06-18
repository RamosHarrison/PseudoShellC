/*
 * string_parser.c
 *
 *  Created on: Nov 25, 2020
 *      Author: gguan, Monil
 *
 */
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "string_parser.h"



int count_token (char* buf, const char* delim)
{
	//TODO：
	/*
	*	#1.	Check for NULL string
	*	#2.	iterate through string counting tokens
	*		Cases to watchout for
	*			a.	string start with delimeter
	*			b. 	string end with delimeter
	*			c.	account NULL for the last token
	*	#3. return the number of token (note not number of delimeter)
	*/

	if (buf == NULL){
		return 0;
	}

	int count = 0;

	char *token; char *ptr;

	char* copy_buffer = (char *)malloc(strlen(buf) + 1);

	strcpy(copy_buffer, buf);

	copy_buffer[strlen(buf)] = '\0';

	token = strtok_r(copy_buffer, delim, &ptr);

	while (token != NULL) {

		count++;
		token = strtok_r(NULL, delim, &ptr);

	}
	free(copy_buffer);
	return count;
}

command_line str_filler (char* buf, const char* delim)
{
	//TODO：
	/*
	*	#1.	create command_line variable to be filled and returned
	*	#2.	count the number of tokens with count_token function, set num_token. 
    *           one can use strtok_r to remove the \n at the end of the line.
	*	#3. malloc memory for token array inside command_line variable
	*			based on the number of tokens.
	*	#4.	use function strtok_r to find out the tokens 
    *   #5. malloc each index of the array with the length of tokens,
	*			fill command_list array with tokens, and fill last spot with NULL.
	*	#6. return the variable.
	*/
	command_line result;
	result.num_token = count_token(buf, delim);
	result.command_list = (char **)malloc(sizeof(char*) * (result.num_token + 1));
	char *token, *ptr;
	int i = 0;
	char* buffer_copy = (char*)malloc(strlen(buf) + 1);
	strcpy(buffer_copy, buf);

	token = strtok_r(buffer_copy, delim, &ptr);
	while (token != NULL) {
		if (strlen(token) == 0 || (strlen(token) == 1 && token[0] == '\n')){
			token = strtok_r(NULL, delim, &ptr);
			continue;
		}

		
		result.command_list[i] = strdup(token);
		
		i++;
		token = strtok_r(NULL, delim, &ptr);
		
	}
	result.num_token = i;
	result.command_list[i] = NULL;
	free(buffer_copy);
	return result;
}
				






void free_command_line(command_line* command)
{
	//TODO：
	/*
	*	#1.	free the array base num_token
	*/
	for (int i = 0; i <command->num_token; i++) {
		free(command->command_list[i]);
	}
	free(command->command_list);
	command->command_list = NULL;

}
