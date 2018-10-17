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
	printf("\033[0;33m<%s@%s:\033[0m\033[0;34m%s\033[0m> ", username, hostname, cwd);
}