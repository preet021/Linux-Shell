#include "shell.h"
#include <string.h>
#include <stdio.h>

int isAllowed (char* cmd)
{
	for (int i=0; i < allwd_cmd_sz; ++i)
	{
		if (strcmp(allowed_cmds[i], cmd) == 0)
			return i;
	}
	return -1;
}