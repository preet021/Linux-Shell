#include <stdio.h>
#include "shell.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int is_bg, size_running_procs = 0;

void interpretCmd (char* cmd)
{
	char str_delim[] = ";";
	char cmd_delim[] = " &\n\t\v\f\r\a";
	char** cmds = parseStr(cmd, str_delim);
	for (int i=0, pid; cmds[i] != NULL; ++i)
	{
		char* s = (char*)malloc(sizeof(char)*(strlen(cmds[i])+2));
		strcpy(s, cmds[i]);
		trim(s, cmds[i]);
		free(s);
		if (strncmp("echo", cmds[i], 4) == 0)
		{
			int no_of_quotes = 0;
			for (int j=4; cmds[i][j]; ++j)
				if (cmds[i][j] == '"') no_of_quotes++;
			if (no_of_quotes % 2)
				fprintf(stderr, "Error: invalid syntax\n");
			else execute_echo(cmds[i]+4);
			continue;
		}
		if (redirect_handler(cmds[i])) continue;
		is_bg = 0;
		for (int j=0; cmds[i][j]; ++j)
			if (cmds[i][j] == '&')
			{
				is_bg = 1;
				break;
			}
		char** args = parseStr(cmds[i], cmd_delim);
		int x = isAllowed(args[0]), status;
		if (x >= 0)
		{
			is_bg = 0;
			executeCmd(args, allowed_execs[x]);
		}
		else
		{
			pid = fork();
			if (pid == 0)
			{
				execvp(args[0], args);
				printf("Error: command not found\n");
				exit(0);
			}
			else
			{
				if (!is_bg) waitpid(pid, &status, WUNTRACED);
				else 
				{
					strcpy(running[size_running_procs].pname, args[0]);
					running[size_running_procs++].pid = pid;
				}
			}
		}
	}
}