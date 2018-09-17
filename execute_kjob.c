#include "shell.h"
#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

void execute_kjob (char* s, char** args)
{
	int sz = 0;
	for (int i=0; args[i] != NULL; ++i, ++sz);
	if (sz != 3)
	{
		fprintf(stderr, "Error: invalid input\n");
		return;
	}
	int sig = atoi(args[2]), pid, jno = atoi(args[1]);
	pid = atoi(cur_jobs[jno-1].p_pid);
	kill(pid,sig);
	return;
}