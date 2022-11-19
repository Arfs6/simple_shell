#include <stdlib.h>
#include <unistd.h>

#include "main.h"

/**
 * _setenv - initialize or modify a variable in environment variable
 * @variable: variable to initialize
 * @value: value to set variable to
 *
 * Return: 0: success (SUCCESS)
 * -1: malloc fails (FAIL)
 */
int _setenv(char *variable, char *value)
{
	int i, idx, len;

	idx = i = 0; /* initializing variables */

	idx = getVariable(variable);
	if (idx == FAIL)
	{
		idx = increaseEnv();
		if (idx == FAIL)
			return (FAIL);
	}
	else
		free(environ[idx]);

	len = _strlen(variable);
	len += _strlen(value);
	len++;/* space for '=' */

	environ[idx] = malloc(sizeof(char) * (len + 1));
	if (environ[idx] == NULL)
		return (FAIL);

	i = 0;
	i = _strcat(variable, environ[idx], i);
	i = _strcat("=", environ[idx], i);
	i = _strcat(value, environ[idx], i);

	return (SUCCESS);
}

/**
 * handleSIGINT - handels the iinterupt signal
 * @sigNum: signal number
 */
void handleSIGINT(int sigNum)
{
	sigNum = sigNum;
	_puts(STDOUT_FILENO, "\n$ ");
}
