#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include "shell.h"

int read_fd = -1, write_fd = -1;

char** redirect_handler (char* arg)
{
	int flag = 0, arg_len = strlen(arg);
	for (int i=0; i<arg_len; ++i)
		if (arg[i] == '<' || arg[i] == '>')
		{
			flag = 1;
			break;
		}
	if (!flag)
	{
		return parseStr(arg, " &\n\t\v\f\r\a");
	}
	char* cmd = (char*)malloc(sizeof(char)*(arg_len+2));
	cmd[0] = '\0';
	int ind = 0, to_append = 0;
	while (arg[ind] != '<' && arg[ind] != '>' && ind < arg_len)
	{
		cmd[ind] = arg[ind];
		ind++;
	}
	cmd[ind] = '\0';
	char* read_from = (char*)malloc(sizeof(char)*(arg_len+2));
	char* write_to = (char*)malloc(sizeof(char)*(arg_len+2));
	read_from[0] = write_to[0] = '\0';
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
	free(s);
	int len_read_from = strlen(read_from), len_write_to = strlen(write_to);
	if (len_write_to == 0 && len_read_from == 0)
	{
		fprintf(stderr, "Error: invalid format\n");
		return NULL;
	}
	struct stat st;
	read_fd = -1, write_fd = -1;
	if (len_read_from > 0)
	{
		if (stat(read_from, &st) == -1)
		{
			fprintf(stderr, "Error: file \"%s\" does not exist\n", read_from);
			return NULL;	
		}
		if (!S_ISREG(st.st_mode))
		{
			fprintf(stderr, "Error: file to read from is not a regular file\n");
			return NULL;
		}
		read_fd = open(read_from, O_RDONLY);
		if (read_fd == -1)
		{
			fprintf(stderr, "Error: failed to open file to read from\n");
			return NULL;
		}
		if (dup2(read_fd, 0) != 0)
		{
			fprintf(stderr, "Error: dup2 fail\n");
			return NULL;
		}
	}
	if (len_write_to > 0)
	{
		if (to_append)
			write_fd = open(write_to, O_WRONLY|O_CREAT|O_APPEND, 0644);
		else write_fd = open(write_to, O_WRONLY|O_CREAT|O_TRUNC, 0644);
		if (dup2(write_fd, 1) != 1)
		{
			fprintf(stderr, "Error: dup2 fail\n");
			return NULL;
		}
	}
	free(write_to);
	free(read_from);
	return parseStr(cmd, " &\n\t\v\f\r\a");
}