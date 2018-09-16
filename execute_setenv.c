#include "shell.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void execute_setenv (char*str, char** args)
{
	int sz = 0;
	for (int i=0; args[i] != NULL; ++i, ++sz);
	if (sz == 1)
		fprintf(stderr, "Error: too few arguments to \"setenv\"\n");
	else if (sz > 3)
		fprintf(stderr, "Error: too many arguments to \"setenv\"\n");
	else if (sz == 2)
	{
		if (setenv(args[1], "", 1) != 0)
			fprintf(stderr, "Error: cannot set variable %s\n", args[1]);
	}
	else if (sz == 3)
	{
		if (setenv(args[1], args[2], 1) != 0)
			fprintf(stderr, "Error: cannot set variable %s\n", args[1]);
	}
	return;
}