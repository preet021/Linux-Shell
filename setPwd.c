#include "shell.h"
#include <string.h>
#include <stdlib.h>

char* setPwd (char* cwd)
{
	int cmp = strcmp(cwd, home);
	if (cmp == 0)
		return "~";
	else if (cmp < 0)
		return cwd;
	else
	{
		if (strncmp(home, cwd, strlen(home)) != 0) return cwd;
		int home_len = strlen(home), cwd_len = strlen(cwd);
		char* ret = (char*)malloc(1024*sizeof(char));
		ret[0] = '~';
		for (int i=home_len; i<cwd_len; ++i)
			ret[i-home_len+1] = cwd[i];
		ret[cwd_len - home_len + 1] = '\0';
		return ret;
	}
}