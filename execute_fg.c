#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

void execute_fg (char* str, char** args)
{
	int sz = 0;
	for (int i=0; args[i] != NULL; ++i, ++sz);
	if (sz != 2)
	{
		fprintf(stderr, "Error: invalid format\n");
		return;
	}
	int pid, job_no = atoi(args[1]), status;
	if (job_no > jobs_sz)
	{
		fprintf(stderr, "Error: job number does not exist");
		return;
	}
	pid = atoi(cur_jobs[job_no-1].p_pid);
	kill(pid, SIGCONT);
	waitpid(pid, &status, WUNTRACED);
	return;
}
