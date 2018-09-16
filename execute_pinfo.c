#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

void execute_pinfo (char* str, char** args)
{
	char* path = (char*)malloc(sizeof(char)*64);
	char* spid = (char*)malloc(sizeof(char)*32);
	char ex_path[64];
	char* buff = (char*)malloc(sizeof(char)*1024);
	buff[0] = '\0';
	if (!args[1] || strcmp(args[1], "&") == 0)
	{
		int pid;
		if (is_bg) pid = getppid();
		else pid = getpid();
		strcpy(path, "/proc/");
		sprintf(spid, "%d", pid);
		strcat(path, spid);
		strcat(path, "/status");
	}
	else
	{
		strcpy(spid, args[1]);
		strcpy(path, "/proc/");
		strcat(path, spid);
		strcat(path, "/status");
	}
	FILE* file = fopen(path, "r");
	if (file != NULL)
	{
		printf("pid: %s\n", spid);
		size_t sz = 0;
		while (getline(&buff, &sz, file) != -1)
		{
			if (strncmp("St", buff, 2) == 0) printf("%s", buff);
			else if (strncmp("VmSize", buff, 6) == 0) printf("%s", buff);
		}
		strcpy(path, "/proc/");
		strcat(path, spid);
		strcat(path, "/exe");
		if (readlink(path, ex_path, 63) == -1)
		{
			printf("Error: can't get executable\n");
			return;
		}
		printf("Executable Path: %s\n", setPwd(ex_path));
	}
	else
	{
		perror(path);
		return;
	}
	free(path);
	free(buff);
	free(spid);
	fclose(file);
}