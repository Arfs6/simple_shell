#include <stdlib.h>
#include <unistd.h>

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
 * setPath - set path for executable
 * @cmd: command to search for
 * @path: link list to PATH variable
 *
 * Return: 0: right path set
 * -1: malloc fails
 */
	int setPath(char **cmd, path_t *path)
{
	int i = 0;
	char *buf;
	path_t *temp = path;

	if (isSlash(*cmd) == 0)
		return (SUCCESS);

	if (path == NULL)
		return (SUCCESS);

	while (temp)
	{
		buf = malloc(sizeof(char) * (_strlen(*cmd) + _strlen(temp->dir) + 2));
		if (buf == NULL)
			return (FAIL);

		i = 0;
		i = _strcat(temp->dir, buf, i);
		if (buf[i - 1] != '/')
			i = _strcat("/", buf, i);
		i = _strcat(*cmd, buf, i);
		if (access(buf, F_OK) == 0)
		{
			free(*cmd);
			*cmd = buf;
			return (SUCCESS);
		}

		free(buf);
		temp = temp->next;
	}

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
	{
		environ = malloc(sizeof(*environ));
		*environ = NULL;
		return;
	}

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
		path_t **path, char *execName, int lineNo)
{
	argv = argv;
	status = status;
	path = path;
	execName = execName;
	lineNo = lineNo;
}

/**
 * increaseEnv - allocates a space for new variable in environ
 *
 * Return: index of newly allocated memory
 * -1: insufficient memory
 */
int increaseEnv(void)
{
	int i, idx, len;
	char **_env;

	i = idx = 0;

	for (len = 0; environ && environ[len]; ++len)
		;
	len += 2; /* space for null and new space */

	_env = malloc(sizeof(*_env) * len);
	if (_env == NULL)
		return (FAIL);

	idx = len - 2;
	for (i = 0; i < len; ++i)
	{
		if (i < len - 2)
			_env[i] = environ[i];
		else
			_env[i] = NULL;
	}

	free(environ);

	environ = _env;

	return (idx);
}
