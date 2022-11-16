#include <stdlib.h>
#include <unistd.h>

#include "main.h"

/**
 * execBuiltin - execute builtin commands
 * @argv: command vector
 * @env: environment variable
 * @status: status of last command
 * @path: link list for directories in PATH variable
 * @execName: name of executable
 * @lineNo: current line number in shell
 *
 * Return: 0: command is builtin and was executed (SUCCESS)
 * -1:command is not builtin (FAIL)
 */
int execBuiltin(char **argv, char **env, int status,
		list_t **path, char *execName, int lineNo)
{
	builtin_t builtinList[] = {
		{"exit", &terminate}, {"env", &printEnv}, {"unsetenv", &unsetEnv},
		{NULL, NULL}
	};
	int i = 0, ret = 0, len;

	for (i = 0; builtinList[i].cmd != NULL; ++i)
	{
		len = _strlen(builtinList[i].cmd);
		ret = _strncmp(builtinList[i].cmd, argv[0], len);
		if (ret == 0)
		{
			ret = builtinList[i].func(argv, env, status, path, execName, lineNo);
			return (ret);
		}
	}

	return (FAIL);
}

/**
 * terminate - terminates the shell
 * @argv: argument vector
 * @env: environment variable to free before exiting shell
 * @status: status to exit with
 * @path: PATH environment variable
 * @execName: name of executable
 * @lineNo: current line in shell
 *
 * Return: 2: illegal number to terminate with
 */
int terminate(char *argv[], char *env[],
		int status, list_t **path, char *execName, int lineNo)
{
	int num = 0;

	if (argv[1] == NULL)
	{
		free_list(path);
		_free(argv, env);
		exit(status);
	}

	if (strToInt(argv[1], &num) == FAIL)
	{
		_dprintf(INVNUMERR, execName, lineNo, argv[1]);
		return 2;
	}

	free_list(path);
	_free(argv, env);
	exit(num);
}

/**
 * printEnv - print environment variable
 * @argv: command vector
 * @env: environment variable
 * @status: status of last executed command
 * @path: link list for dir in PATH variable
 * @execName: name of executable the shell was called with
 * @lineNo: current line number in shell
 */
int printEnv(char *argv[], char *env[], int status,
		list_t **path, char *execName, int lineNo)
{
	int i = 0;

	/* supressing unused arguments warning */
	useArg(argv, NULL, status, path, execName, lineNo);

	if (env == NULL || env[i] == NULL)
	{
		_putchar('\n');
		return (0);
	}

	for (i = 0; env[i]; ++i)
	{
	_puts(STDOUT_FILENO, env[i]);
	_putchar('\n');
	}

	return (0);
}
