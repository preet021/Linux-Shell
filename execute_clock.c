#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

static volatile int keepRunning = 1;

void intHandler (int dummy)
{
	keepRunning = 0;
}

void execute_clock (char* str, char** args)
{
	if (! args[1] || !args[2] || strcmp(args[1], "-t") != 0)
	{
		printf("Error: invalid input format\n");
		return;
	}
	int t = atoi(args[2]);
	signal(SIGINT, intHandler);
	signal(SIGTSTP, intHandler);
	while (keepRunning)
	{
		int rtc = open("/sys/class/rtc/rtc0/date", O_RDONLY);
		char buff[33];
		buff[0] = '\0';
		read(rtc, buff, 10);
		buff[10] = '\0';
		printf("%s ", buff);
		close(rtc);
		int rtc1 = open("/sys/class/rtc/rtc0/time", O_RDONLY);
		buff[0] = '\0';
		read(rtc1, buff, 8);
		buff[8] = '\0';
		printf("%s\n", buff);
		close(rtc1);
		sleep(t);
	}
	return;
}