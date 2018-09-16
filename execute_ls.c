#include "shell.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>

void execute_ls (char* str, char** args)
{
	const char *path;
	char* tmp;
	int it1 = 1, is_path = 0, is_flg_l = 0, is_flg_a = 0;
	while (args[it1])
	{
		if (args[it1][0] == '-')
		{
			int j = 1;
			while (args[it1][j])
			{
				if (args[it1][j] == 'l') is_flg_l = 1;
				if (args[it1][j] == 'a') is_flg_a = 1;
				j++;
			}
		}
		else
		{
			if (strcmp("&", args[it1]) != 0)
			{
				is_path = 1;
				tmp = (char*)malloc(sizeof(args[it1]));
				tmp = args[it1];
			}
		}
		it1++;
	}
	path = (char*)malloc(sizeof(char)*1024);
	if (!is_path)
	{
		getcwd(pwd, 1023);
		path = pwd;
	}
	else path = tmp;
	if (path[0] == '~')
	{
		tmp = home;
		strcat(tmp, &path[1]);
		path = tmp;
	}
	struct stat st;
	stat(path, &st);
	if (!S_ISDIR(st.st_mode))
	{
		printf("Error: not a directory\n");
		return;
	}
	DIR *dir = opendir(path);
	struct dirent* dst;
	typedef struct file_data
	{
		char* f_permissions;
		nlink_t f_nhlinks;
		char* f_uown;
		char* f_gown;
		off_t f_size;
		char* f_mtime;
		char* f_name;
	}fdt;
	int it = 0, f_sz = 64;
	fdt* files = (fdt*)malloc(f_sz*sizeof(fdt));
	if (files == NULL)
	{
		printf("Allocation Error\n");
		exit(EXIT_FAILURE);
	}
	while (dst = readdir(dir))
	{
		files[it++].f_name = dst->d_name;
		if (it >= f_sz)
		{
			f_sz <<= 1;
			files = realloc(files, f_sz);
			if (files == NULL)
			{
				printf("Reallocation Error\n");
				exit(EXIT_FAILURE);
			}
		}
	}
	it = 0;
	while (files[it].f_name)
	{
		struct stat st;
		char* s = (char*)malloc((strlen(path)+strlen(files[it].f_name)+5)*sizeof(char));
		strcpy(s, path);
		if (s[(int)strlen(s)-1] != '/') strcat(s,"/");
		strcat(s, files[it].f_name);
		int x = stat(s, &st);
		if (x == -1)
		{
			printf("Error getting file info\n");
			exit(EXIT_FAILURE);
		}
		
		files[it].f_permissions = (char*)malloc(sizeof(char)*11);
		if (S_ISREG(st.st_mode)) files[it].f_permissions[0] = '-';
		else if (S_ISDIR(st.st_mode)) files[it].f_permissions[0] = 'd';
		else if (S_ISCHR(st.st_mode)) files[it].f_permissions[0] = 'c';
		else if (S_ISBLK(st.st_mode)) files[it].f_permissions[0] = 'b';
		else if (S_ISFIFO(st.st_mode)) files[it].f_permissions[0] = 'p';
		else if (S_ISLNK(st.st_mode)) files[it].f_permissions[0] = 'l';
		else files[it].f_permissions[0] = 's';

		if (st.st_mode & S_IRUSR) files[it].f_permissions[1] = 'r';
		else files[it].f_permissions[1] = '-';
		if (st.st_mode & S_IWUSR) files[it].f_permissions[2] = 'w';
		else files[it].f_permissions[2] = '-';
		if (st.st_mode & S_IXUSR) files[it].f_permissions[3] = 'x';
		else files[it].f_permissions[3] = '-';

		if (st.st_mode & S_IRGRP) files[it].f_permissions[4] = 'r';
		else files[it].f_permissions[4] = '-';
		if (st.st_mode & S_IWGRP) files[it].f_permissions[5] = 'w';
		else files[it].f_permissions[5] = '-';
		if (st.st_mode & S_IXGRP) files[it].f_permissions[6] = 'x';
		else files[it].f_permissions[6] = '-';

		if (st.st_mode & S_IROTH) files[it].f_permissions[7] = 'r';
		else files[it].f_permissions[7] = '-';
		if (st.st_mode & S_IWOTH) files[it].f_permissions[8] = 'w';
		else files[it].f_permissions[8] = '-';
		if (st.st_mode & S_IXOTH) files[it].f_permissions[9] = 'x';
		else files[it].f_permissions[9] = '-';

		files[it].f_permissions[10] = '\0';
		files[it].f_nhlinks = st.st_nlink;
		files[it].f_uown = getpwuid(st.st_uid)->pw_name;
		files[it].f_gown = getgrgid(st.st_gid)->gr_name;
		files[it].f_size = st.st_size;
		files[it].f_mtime = (char*)malloc(sizeof(char)*100);
		strftime(files[it].f_mtime, 100, "%b %d %H:%M", localtime(&st.st_mtime));
		it++;
		free(s);
	}
	
	it = 0;
	while (files[it].f_name)
	{
		if (!is_flg_a && files[it].f_name[0] == '.')
		{
			it++;
			continue;
		}
		if (is_flg_l) printf("%s\t%d\t%s\t%s\t%d\t%s\t%s\n", files[it].f_permissions, (int)files[it].f_nhlinks, files[it].f_uown, files[it].f_gown, (int)files[it].f_size, files[it].f_mtime, files[it].f_name);
		else printf("%s\n", files[it].f_name);
		it++;
	}
	free(files);
}