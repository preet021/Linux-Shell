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
	for (int i=0, pid, status; cmds[i] != NULL; ++i)
	{
		char* s = (char*)malloc(sizeof(char)*(strlen(cmds[i])+2));
		strcpy(s, cmds[i]);
		trim(s, cmds[i]);
		strcpy(s, cmds[i]);
		is_bg = 0;
		if (pipe_handler(cmds[i]) != -1) continue;
		for (int j=0; cmds[i][j]; ++j)
			if (cmds[i][j] == '&')
			{
				cmds[i][j] = '\0';
				is_bg = 1;
				break;
			}
		char** args;
		if (strncmp(cmds[i], "quit", 4) == 0)
			execute_quit(cmds[i], args);
		else if (strncmp(cmds[i], "cd", 2) == 0)
		{
			execute_cd(cmds[i], parseStr(cmds[i], cmd_delim));
			continue;
		}
		else if (strncmp(cmds[i], "setenv", 6) == 0)
		{
			execute_setenv(cmds[i], parseStr(cmds[i], cmd_delim));
			continue;
		}
		else if (strncmp(cmds[i], "unsetenv", 8) == 0)
		{
			execute_unsetenv(cmds[i], parseStr(cmds[i], cmd_delim));
			continue;
		}
		else if (strncmp(cmds[i], "jobs", 4) == 0)
		{
			execute_jobs(1);
			continue;
		}
		else if (strncmp(cmds[i], "kjob", 4) == 0)
		{
			execute_jobs(0);
			execute_kjob(cmds[i], parseStr(cmds[i], cmd_delim));
			continue;
		}
		else if (strncmp(cmds[i], "fg", 2) == 0)
		{
			execute_jobs(0);
			execute_fg(cmds[i], parseStr(cmds[i], cmd_delim));
			continue;
		}
		else if (strncmp(cmds[i], "bg", 2) == 0)
		{
			execute_jobs(0);
			execute_bg(cmds[i], parseStr(cmds[i], cmd_delim));
			continue;
		}
		else if (strncmp(cmds[i], "overkill", 8) == 0)
		{
			for (int j=0; j<size_running_procs; ++j)
			{
				kill(running[j].pid, 9);
				running[j].pid = -1;
			}
			continue;
		}
		pid = fork();
		if (pid == 0)
		{
			if (is_bg) setpgid(0, 0);
			args = redirect_handler(cmds[i]);
			if (!args) exit(0);
			if (strncmp("echo", s, 4) == 0)
			{
				int no_of_quotes = 0;
				for (int j=4; s[j]; ++j)
					if (s[j] == '"') no_of_quotes++;
				if (no_of_quotes % 2)
					fprintf(stderr, "Error: invalid syntax\n");
				else execute_echo(s+4);
			}
			else
			{	
				int x = isAllowed(args[0]);
				if (x >= 0)
				{
					is_bg = 0;
					executeCmd(cmds[i], args, allowed_execs[x]);
				}
				else
				{
					execvp(args[0], args);
					fprintf(stderr, "Error: command not found\n");
				}
			}
			exit(0);
		}
		else
		{
			if (!is_bg) waitpid(pid, &status, WUNTRACED);
			else 
			{
				args = parseStr(cmds[i], cmd_delim);
				strcpy(running[size_running_procs].pname, args[0]);
				running[size_running_procs++].pid = pid;
			}
		}
	}
}