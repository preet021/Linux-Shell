#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void execute_echo (char* args)
{
	for (int i=0; args[i]; ++i)
		if (args[i] == '>')
		{
			args[i] = '\0';
			break;
		}
	for (int i=0, j; args[i];)
	{
		if (isspace(args[i]))
		{
			++i;
			continue;
		}
		if (args[i] == '$')
		{
			++i;
			j = 0;
			char s[1024];
			while (args[i] && !isspace(args[i]))
				s[j++] = args[i++];
			s[j] = '\0';
			char *ret = getenv(s);
			if (ret == NULL)
				fprintf(stderr, "Error: variable \"%s\" does not exist\n", s);
			else printf("%s ", ret);
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