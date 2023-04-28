#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

void logAction(char *action)
{
	unsigned int f_log = open("logs/log.txt", O_WRONLY | O_APPEND | O_CREAT, S_IRWXU | S_IRWXG); // S_IRWXU - user has read, write and execute permission, S_IRWXG - group has read, write and execute permission
	time_t t = time(NULL);
	struct tm tStruct = *localtime(&t);
	char currentDate[21];
	sprintf(currentDate, "%02d-%02d-%d %02d:%02d:%02d ", tStruct.tm_mday, tStruct.tm_mon + 1, tStruct.tm_year + 1900, tStruct.tm_hour, tStruct.tm_min, tStruct.tm_sec);
	char *sysArg = calloc(strlen(action) + 22, sizeof(char)); // "<date> <action>\n\0" = 22 + strlen(action) characters
	strcat(sysArg, currentDate);
	strcat(sysArg, action);
	strcat(sysArg, "\n");
	write(f_log, sysArg, strlen(sysArg));
	close(f_log);
	free(sysArg);
}