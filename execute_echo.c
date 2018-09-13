#include "shell.h"
#include <stdio.h>
#include <ctype.h>

void execute_echo (char* args)
{
	for (int i=0; args[i];)
	{
		if (isspace(args[i]))
		{
			++i;
			continue;
		}
		if (args[i] == '"')
		{
			++i;
			while (args[i] && args[i] != '"')
			{
				printf("%c", args[i]);
				++i;
			}
			printf(" ");
			++i;
			continue;
		}
		while (args[i] && !isspace(args[i]))
		{
			printf("%c", args[i]);
			++i;
		}
		printf(" ");
	}
	printf("\n");
}