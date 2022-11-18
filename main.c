#include <unistd.h>

#include "main.h"

/**
 * main - entery code for shell
 * @argc: arguments count
 * @argv: arguments vector
 *
 * Return: shell exited normally 0 (sucess)
 * or status of executed file
 */
int main(int argc, char **argv)
{
	int lineNo = 0, status = 0;
	char **vector = NULL;
	list_t *path;

	initEnv();
	path = getPathList();

	while (TRUE)
	{
		if (argc == 1 && isatty(STDIN_FILENO) == 1)
			_puts(STDOUT_FILENO, "($) ");
		lineNo++;
		vector = getCmd(&path, &status, argv[0], lineNo);
		if (vector == NULL)
			continue;
		status = execute(vector, argv[0], lineNo, &path, status);
		_free(vector, NULL);
	}

	return (0);
}
