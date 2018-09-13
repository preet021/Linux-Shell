#include "shell.h"
#include <unistd.h>
#include <stdio.h>

void execute_pwd (char** args)
{
	getcwd(pwd, 1023);
	printf("%s\n", pwd);
}