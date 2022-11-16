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
int main(int argc, char **argv, char **ev)
{
	int lineNo = 0, status = 0;
	char **vector = NULL, **env;
	list_t *path;

	env = initEnv(ev);
	path = getPathList(env);

	while (TRUE)
	{
		if (argc == 1)
			_puts(STDOUT_FILENO, "$ ");
		lineNo++;
		vector = getCmd(env, &path, &status, argv[0], lineNo);
		if (vector == NULL)
			continue;
		status = execute(vector, env, argv[0], lineNo, &path, status);
		_free(vector, NULL);
	}

	return (0);
}
