#include "shell.h"

void executeCmd (char** args, void (*exec_fun)(char**))
{
	(*exec_fun)(args);
}