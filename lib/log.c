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
	unsigned int flog = open("log.txt", O_WRONLY | O_APPEND | O_CREAT, S_IRWXU | S_IRWXG); // S_IRWXU - user has read, write and execute permission, S_IRWXG - group has read, write and execute permission
	time_t t = time(NULL);
	struct tm tStruct = *localtime(&t);
	char currentDate[21];
	sprintf(currentDate, "%02d-%02d-%d %02d:%02d:%02d ", tStruct.tm_mday, tStruct.tm_mon + 1, tStruct.tm_year + 1900, tStruct.tm_hour, tStruct.tm_min, tStruct.tm_sec);
	char *sysArg = calloc(strlen(action) + 22, 1); // "<date> <action>\n\0" = 22 + strlen(action) characters
	strcat(sysArg, currentDate);
	strcat(sysArg, action);
	strcat(sysArg, "\n");
	write(flog, sysArg, strlen(sysArg));
	close(flog);
}

void main(int argc, char *argv[])
{
	char *src = argv[1];
	char *dst = argv[2];

	unsigned int fsrc = open(src, O_RDONLY);
	unsigned int fdst = open(dst, O_WRONLY);

	size_t *buffer = calloc(1, 1);
	size_t buf_read = 1;


	while(buf_read > 0)
	{
		buf_read = read(fsrc, buffer, 1);
		write(fdst, buffer, 1);
	}
	free(buffer);
	close(fsrc);
	close(fdst);

	logAction("copy successful");

	return;
}
