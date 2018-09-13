#include "shell.h"
#include <stdlib.h>
#include <stdio.h>

char* scanCmd ()
{
	char ch;
	int buff_sz = 128, it = 0;
	char* buff = (char*)malloc(buff_sz*sizeof(char));
	if (buff == NULL)
	{
		perror("Allocation Error");
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		ch = getchar();
		if (ch == '\n' || ch == EOF)
		{
			buff[it] = '\0';
			break;
		}
		buff[it] = ch;
		it++;
		if (it >= buff_sz)
		{
			buff_sz <<= 1;
			buff = realloc(buff, buff_sz);
			if (buff == NULL)
			{
				perror("Reallocation Error");
				exit(EXIT_FAILURE);
			}
		}
	}
	return buff;
}