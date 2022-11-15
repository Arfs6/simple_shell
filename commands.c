#include <stdlib.h>
#include <unistd.h>

#include "main.h"

/**
 * execBuiltin - execute builtin commands
 * @argv: command vector
 * @env: environment variable
 *
 * Return: 0: command is builtin and was executed (SUCCESS)
 * -1:acommand is not builtin (FAIL)
 */
int execBuiltin(char **argv, char **env, int status, list_t *path, char *execName, int lineNo)
{
	char *builtinList[] = {"exit", "env"};

	if (_strncmp(argv[0], builtinList[0], _strlen(builtinList[0]) + 1) == 0)
		return (terminate(argv, status, path, execName, lineNo));
	else if (_strncmp(argv[0], builtinList[1], _strlen(builtinList[1]) + 1) == 0)
	{
		printEnv(env);
		return (SUCCESS);
	}

	return (FAIL);
}

/**
 * terminate - terminates the shell
 * @argv: argument vector
 * @status: status to exit with
 * @path: PATH environment variable
 * @execName: name of executable
 * @lineNo: current line in shell
 *
 * Return: 2: illegal number to terminate with
 */
int terminate(char **argv, int status, list_t *path, char *execName, int lineNo)
{
	int num = 0;

	if (argv[1] == NULL)
	{
		free_list(path);
		_free(argv);
		exit(status);
	}

	if (strToInt(argv[1], &num) == FAIL)
	{
		_dprintf(INVNUMERR, execName, lineNo, argv[1]);
		return 2;
	}

	free_list(path);
	_free(argv);
	exit(num);
}

/**
 * printEnv - print environment variable
 * @env: environment variable
 */
void printEnv(char **env)
{
	int i = 0;

	for (i = 0; env[i]; i++)
	{
	_puts(STDOUT_FILENO, env[i]);
	_putchar('\n');
	}

}
