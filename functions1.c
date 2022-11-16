#include <stdlib.h>

#include "main.h"

/**
 * strToInt - converts a string to an int
 * @str: pointer to string
 * @num: pointer to integer
 *
 * Return: 0: converted successfully (SUCCESS)
 * -1: invalid character in string (FAIL)
 */
int strToInt(char *str, int *num)
{
	int i = 0;
	int mul = 1;

	if (str == NULL)
		return (FAIL);

	for (i = 0; str[i]; ++i)
	{
		if (str[i] < '0' || str[i] > '9')
			return (FAIL);
	}

	strRev(str);
	*num = 0;

	for (i = 0; str[i]; ++i)
	{
		*num += (str[i] - '0') * mul;
		mul *= 10;
	}

	strRev(str);

	return (SUCCESS);
}

/**
 * initEnv - initialize environment variable
 * @ev: environment variable
 *
 * Return: environment variable
 */
char **initEnv(char **ev)
{
	int i = 0;
	char **env;

	if (ev == NULL || ev[0] == NULL)
		return (NULL);

	for (i = 0; ev[i]; ++i)
		;

	env = malloc(sizeof(*env) * (i + 1));
	if (env == NULL)
		return (NULL);

	for (i = 0; ev[i]; ++i)
	{
		env[i] = _strdup(ev[i]);
		if (env[i] == NULL)
		{
			_free(NULL, env);
			return (NULL);
		}
	}
	env[i] = NULL;

	return (env);
}

/**
 * useArg - nullifies unused argument warning
 * @argv: command argument
 * @env: environment variable
 * @status: status of last executed command
 * @path: list of dirs in PATH variable
 * @execName: name of shell executable
 * @lineNo: current line in shell
 */
void useArg(char *argv[], char *env[], int status,
		list_t *path, char *execName, int lineNo)
{
	argv = argv;
	env = env;
	status = status;
	path = path;
	execName = execName;
	lineNo = lineNo;
}
