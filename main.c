#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include "shell.h"

char home[1024];
char pwd[1024];
char* allowed_cmds[] = {"cd", "quit", "pwd", "ls", "pinfo", "remindme", "clock", "setenv", "unsetenv"};
void (*allowed_execs[])(char*, char**) = {&execute_cd, &execute_quit, &execute_pwd, &execute_ls, &execute_pinfo, &execute_remindme, &execute_clock, &execute_setenv, &execute_unsetenv};
int max_proc = 1024;
int allwd_cmd_sz = sizeof(allowed_cmds)/sizeof(char*);
struct P running[2048];

void sigintHandler (int sig_num)
{
	signal(SIGINT, sigintHandler);
	fflush(stdout);
}

void sigtstpHandler(int sig_num) 
{ 
	signal(SIGTSTP, sigtstpHandler);
}

int main ()
{
	signal(SIGINT, sigintHandler);
	signal(SIGTSTP, sigtstpHandler);
	getcwd(home, 1023);
	while (1)
	{
		int pid, status;
		while ((pid = waitpid(-1, &status, WNOHANG | WUNTRACED)) > 0)
		{
			char* pname;
			if (WIFEXITED(status))
			{
				for (int i=0; i<size_running_procs; ++i)
					if (running[i].pid == pid)
					{
						pname = running[i].pname;
						running[i].pid = -1;
						fprintf(stderr, "%s with pid %d exited normally.\n", pname, (int)pid);
						break;
					}
			}
			if (WIFSIGNALED(status))
			{
				for (int i=0; i<size_running_procs; ++i)
					if (running[i].pid == pid)
					{
						pname = running[i].pname;
						running[i].pid = -1;
						break;
						fprintf(stderr, "%s with pid %d terminated by a signal.\n", pname, (int)pid);
					}
			}
		}
		printCmdPrompt();
		char* s = scanCmd();
		char* cmd = (char*)malloc(strlen(s)*sizeof(char));
		trim(s, cmd);
		free(s);
		interpretCmd(cmd);
		free(cmd);
	}
	return 0;
}