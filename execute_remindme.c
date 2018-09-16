#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

void execute_remindme (char* str, char** args)
{
	if (!args[1] || !args[2])
	{
		printf("Error: invalid input format\n");
		return;
	}
	int pid = fork();
	int t = atoi(args[1]);
	if (pid == 0)
	{
		sleep(t);
		printf("%s\n", args[2]);
		exit(0);
	}
	else return;
}