#include <ctype.h>
#include "shell.h"

void trim (char* s, char* cmd)
{
	int it, i, j, sz = 0;
	for (i=0; s[i] != '\0'; ++i, ++sz);
	for (i=0; i<sz; ++i)
		if (!isspace(s[i]))
			break;
	for (j=sz-1; j>=0; --j)
		if (!isspace(s[j]))
			break;
	for (it=0; i<=j; ++i, ++it)
		cmd[it] = s[i];
	cmd[it] = '\0';
}