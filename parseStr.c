#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** parseStr (char* cmd, char* delim)
{
	int buff_sz = 64, it = 0;
	char** tokens = (char**)malloc(64*sizeof(char*));
	if (tokens == NULL)
	{
		printf("Allocation Error\n");
		exit(EXIT_FAILURE);
	}
	char* token = strtok(cmd, delim);
	while (token != NULL)
	{
		tokens[it++] = token;
		token = strtok(NULL, delim);
		if (it >= buff_sz)
		{
			buff_sz <<= 1;
			tokens = realloc(tokens, buff_sz);
			if (tokens == NULL)
			{
				printf("Reallocation Error\n");
				exit(EXIT_FAILURE);
			}
		}
	}
	tokens[it] = NULL;
	return tokens;
}