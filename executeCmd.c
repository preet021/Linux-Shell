#include "shell.h"

void executeCmd (char* str, char** args, void (*exec_fun)(char*, char**))
{
	(*exec_fun)(str, args);
}