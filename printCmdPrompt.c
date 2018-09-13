#include "shell.h"
#include <stdio.h>
#include <pwd.h>
#include <unistd.h>
#include <sys/types.h>

void printCmdPrompt ()
{
	char *username = getpwuid(geteuid())->pw_name;
	char hostname[512] = {'\0'};
	gethostname(hostname,511);
	char commandPrompt[1024] = {'\0'};
	getcwd(pwd, 1023);
	char* cwd = setPwd(pwd);
	printf("<%s@%s:%s> ", username, hostname, cwd);
}