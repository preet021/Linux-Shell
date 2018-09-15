#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "shell.h"
#include <string.h>

int pipe_handler(char* s)
{
	char cmd[1024], tmp[1024];
	strcpy(cmd, s);
	char** pipe_sep_cmds = parseStr(cmd, "|");
	int no_of_pipes = 0;
	for (int i=0; pipe_sep_cmds[i] != NULL; ++i, no_of_pipes++)
	{
		strcpy(tmp, pipe_sep_cmds[i]);
		trim(tmp, pipe_sep_cmds[i]);
	}
	no_of_pipes--;
	if (no_of_pipes == 0) return -1;
	int *fildes = (int*)malloc(sizeof(int)*2*no_of_pipes);
	for (int i=0; i<no_of_pipes; ++i)
		if (pipe(fildes+2*i) == -1)
		{
			fprintf(stderr, "Error: pipe failed\n");
			return -1;
		}
	for (int i=0, pid; i<=no_of_pipes; ++i)
	{
		pid = fork();
		if (pid == 0)
		{
			if (i != 0)
			{
				dup2(fildes[]);
			}
			if (i != no_of_pipes)
			{
				dup2(fildes[2*i+1]);
			}
		}
		else
		{

		}
	}
	return 0;
}