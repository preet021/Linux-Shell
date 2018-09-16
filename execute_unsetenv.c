#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "shell.h"

void execute_unsetenv (char* str, char** args)
{
	int sz = 0;
	for (int i=0; args[i] != NULL; ++i, ++sz);
	if (sz == 0)
	{
		fprintf(stderr, "Error: too few arguments to \"insetenv\"\n");
		return;
	}
	else if (sz > 2)
	{
		fprintf(stderr, "Error: too many arguments to \"insetenv\"\n");
		return;	
	}
	else if (sz == 2)
	{
		if (unsetenv(args[1]) != 0)
			fprintf(stderr, "Error: error unsetting the variable\n");
		return;
	}
	return;
}