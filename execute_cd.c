#include "shell.h"
#include <string.h>
#include <unistd.h>
#include <stdio.h>

void execute_cd (char* str, char** args)
{
	if ((args[1] && strcmp("&", args[1]) == 0)||(args[2] && strcmp("&", args[2]) == 0));
	else if (!args[1] || (strcmp("~", args[1]) == 0)) chdir(home);
	else 
	{
		if (strncmp("~", args[1], 1) == 0)
		{
			char* path = home;
			strcat(path, &args[1][1]);
			args[1] = path;
		}
		if (chdir(args[1]) == -1)
			printf("Error: could not change directory\n");
	}
}