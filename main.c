#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "main.h"

/**
 * main - entery code for shell
 * @argc: arguments count
 * @iargv: arguments vector
 * @env: environment variables vector
 *
 * Return: shell exited normally 0 (sucess)
 * or status of executed file
 */
int main(int argc, char **argv, char **env)
{
	int ret = 0, lineNo = 0;
	struct stat *statBuf = NULL;
	char **vector = NULL;

	if (argc > 1)
	{
		ret = stat(argv[1], statBuf);
		if (ret == -1)
		{
			printError(NOTFOUNDERR, argv[1], 0);
			exit(2);
		}
		ret = execve(argv[1], &(argv[1]), env);
		printError(SYSERR, argv[0], 0);
		exit(2);
	}

	lineNo = -1;
	while (lineNo < 0)
	{
		_puts("$ ", STDOUT_FILENO);
		lineNo++;
		vector = getCmd();
		printf("%s\n", vector[0]);
		if (vector == NULL)
			continue;
		ret = stat(vector[0], statBuf);
		if (ret == -1)
		{
			printError(NOTFOUNDERR, argv[0], lineNo);
			_free(vector);
			continue;
		}
		execute(vector, env, argv[0], lineNo);
		_free(vector);
	}

	return (0);
}
