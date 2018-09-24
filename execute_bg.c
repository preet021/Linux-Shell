#include "shell.h"
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <sys/types.h>

void execute_bg (char* str, char** args)
{
	int sz = 0;
	for (int i=0; args[i] != NULL; ++i, ++sz);
	if (sz != 2)
	{
		fprintf(stderr, "Error: invalid format\n");
		return;
	}
	int pid, job_no = atoi(args[1]);
	if (job_no >= jobs_sz)
	{
		fprintf(stderr, "Error: job number does not exist\n");
		return;
	}
	pid = atoi(cur_jobs[job_no-1].p_pid);
	printf("name = %s\n", cur_jobs[job_no-1].p_name);
	printf("pid = %d\n", pid);
	kill(pid, SIGCONT);
	return;
}