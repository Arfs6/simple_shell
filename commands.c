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
int execBuiltin(char **argv, char **env)
{
	char *builtinList[] = {"exit", "env"};

	if (_strncmp(argv[0], builtinList[0], _strlen(builtinList[0]) + 1) == 0)
		terminate(0);
	else if (_strncmp(argv[0], builtinList[1], _strlen(builtinList[1]) + 1) == 0)
	{
		printEnv(env);
		return (SUCCESS);
	}

	return (FAIL);
}

/**
 * terminate - terminates the shell
 * @status: status to exit with
 */
void terminate(int status)
{
	_putchar('\n');
	exit(status);
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
