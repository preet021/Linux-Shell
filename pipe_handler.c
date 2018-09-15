#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "shell.h"
#include <string.h>

int fildes[2];

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
	int in_fd = dup(0);
	int out_fd = dup(1);
	pipe(fildes);
	for (int i=0, pid, status; i<=no_of_pipes; ++i)
	{
		char** args = parseStr(pipe_sep_cmds[i],  " \n\t\v\f\r\a");
		if (i == 0)
			dup2(fildes[1], 1);
		else if (i == no_of_pipes)
		{
			close(fildes[1]);
			if(dup2(fildes[0], 0) == -1)
				fprintf(stderr, "Error: dup2 failed\n");
			close(fildes[0]);
		}
		else
		{
			// close(fildes[1]);
			if (dup2(fildes[0], 0) == -1)
				fprintf(stderr, "Error: dup2 failed\n");
			if (dup2(fildes[1], 1) == -1)
				fprintf(stderr, "
					Error: dup2 failed\n");
		}
		pid = fork();
		if (pid == 0)
		{
			// args = redirect_handler(pipe_sep_cmds[i]);
			// if (!args) exit(0);
			int x = isAllowed(pipe_sep_cmds[i]);
			if (x >= 0) executeCmd(args, allowed_execs[x]);
			else execvp(args[0], args);
			fprintf(stderr,"baadme%d\n",fildes[0]);
			exit(0);
		}
		else 
		{
			waitpid(pid, &status, WUNTRACED);
			dup2(in_fd,0);
			dup2(out_fd,1);
		}
	}
	return 0;
}