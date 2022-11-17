#include <stdlib.h>

#include "main.h"

/**
 * strToInt - converts a string to an int
 * @_str: pointer to string
 * @num: pointer to integer
 *
 * Return: 0: converted successfully (SUCCESS)
 * -1: invalid character in string (FAIL)
 */
int strToInt(char *_str, int *num)
{
	int i = 0;
	int mul = 1;
	char str[20];

	if (str == NULL)
		return (FAIL);

	_strcat(_str, str, 0);
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
 */
void initEnv(void)
{
	int i = 0;
	char **env;

	if (environ == NULL || environ[0] == NULL)
		return;

	for (i = 0; environ && environ[i]; ++i)
		;

	env = malloc(sizeof(*env) * (i + 1));
	if (env == NULL)
	{
		environ = NULL; /* other functions expects a malloc environ */
		return;
	}

	for (i = 0; environ[i]; ++i)
	{
		env[i] = _strdup(environ[i]);
		if (env[i] == NULL)
		{
			/* Not freeing it so we have some variables */
			environ = env;
			return;
		}
	}
	env[i] = NULL;
	environ = env;
}

/**
 * useArg - nullifies unused argument warning
 * @argv: command argument
 * @status: status of last executed command
 * @path: list of dirs in PATH variable
 * @execName: name of shell executable
 * @lineNo: current line in shell
 */
void useArg(char *argv[], int status,
		list_t **path, char *execName, int lineNo)
{
	argv = argv;
	status = status;
	path = path;
	execName = execName;
	lineNo = lineNo;
}
