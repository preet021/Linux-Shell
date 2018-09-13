#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "shell.h"

int redirect_handler (char* arg)
{
	int flag = 0, arg_len = strlen(arg);
	for (int i=0; i<arg_len; ++i)
		if (arg[i] == '<' || arg[i] == '>')
		{
			flag = 1;
			break;
		}
	if (!flag)
		return 0;
	char* cmd = (char*)malloc(sizeof(char)*(arg_len+2));
	int ind = 0, to_append = 0;
	printf("arg: %s\n", arg);
	while (arg[ind] != '<' && arg[ind] != '>' && ind < arg_len)
	{
		cmd[ind] = arg[ind];
		ind++;
	}
	cmd[ind] = '\0';
	printf("command: %s\n", cmd);
	char* read_from = (char*)malloc(sizeof(char)*(arg_len+2));
	char* write_to = (char*)malloc(sizeof(char)*(arg_len+2));
	for (int i=ind,j,k; i<arg_len;)
	{
		if (arg[i] == '>' && arg[i+1] != '>')
		{
			j = i + 1;
			while (arg[j] != '<' && j < arg_len)
				j++;
			k = j;
			while (arg[k] != '>') k--;
			if (arg[k-1] == '>') to_append = 1;
			for (ind=k+1; ind<j; ++ind)
				write_to[ind-k-1] = arg[ind];
			write_to[j-k-1] = '\0';
			i = j;
			continue;
		}
		if (arg[i] == '>' && arg[i+1] == '>')
		{
			j = i + 2;
			while (arg[j] != '<' && j < arg_len)
				j++;
			k = j;
			while (arg[k] != '>') k--;
			if (arg[k-1] == '>') to_append = 1;
			for (ind=k+1; ind<j; ++ind)
				write_to[ind-k-1] = arg[ind];
			write_to[j-k-1] = '\0';
			i = j;
			continue;
		}
		if (arg[i] == '<')
		{
			j = i + 1;
			while (arg[j] != '>' && j < arg_len)
				j++;
			k = j;
			while (arg[k] != '<') k--;
			for (ind=k+1; ind<j; ++ind)
				read_from[ind-k-1] = arg[ind];
			read_from[j-k-1] = '\0';
			i = j;
			continue;
		}
	}
	char* s = (char*)malloc(sizeof(char)*arg_len);
	strcpy(s, read_from);
	trim(s, read_from);
	strcpy(s, write_to);
	trim(s, write_to);
	printf("read_from: %s\n", read_from);
	printf("write_to: %s\n", write_to);
	free(s);
	free(cmd);
	free(write_to);
	free(read_from);
	return 1;
}