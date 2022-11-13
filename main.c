#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "main.h"

/**
 * main - entery code for shell
 * @argc: arguments count
 * @argv: arguments vector
 * @env: environment variables vector
 *
 * Return: shell exited normally 0 (sucess)
 * or status of executed file
 */
int main(int argc, char **argv, char **env)
{
	int lineNo = 0;
	char **vector = NULL;
	list_t *path;

	path = getPathList(env);
	argc = argc;

	while (TRUE)
	{
		_puts(STDOUT_FILENO, "$ ");
		lineNo++;
		vector = getCmd(path);
		if (vector == NULL)
			continue;
		execute(vector, env, argv[0], lineNo, path);
		_free(vector);
	}

	return (0);
}
