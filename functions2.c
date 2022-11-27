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

/**
 * initPWD - initialized PWD variable in environment variable
 */
void initPWD(void)
{
	char *cwd = NULL;
	int temp = 0;

	temp = getVariable("PWD");
	if (temp >= 0)
		return;

	cwd = getcwd(cwd, 0);
	if (cwd == NULL)
		return;

	_setenv("PWD", cwd);

	free(cwd);
}

/**
 * setCdPath - makes currently set directory absolute path
 * @cdPath: current working directory
 *
 * Return: absolute path
 * NULL: insufficient memory
 */
char *setCdPath(char *cdPath)
{
	char *absPath = NULL, *temp;
	int ret = 0;

	absPath = getcwd(absPath, 0);
		if (absPath != NULL)
			return (absPath);

	if (cdPath[0] == '/')
		return (_strdup(cdPath));

	ret = getVariable("PWD");
	if (ret == -1)
		return (_strdup(cdPath));

	temp = environ[ret];
	absPath = malloc(sizeof(char) * (_strlen(temp) + _strlen(cdPath) + 2));

	ret = 0;
	ret = _strcat(temp, absPath, ret);
	if (absPath[ret - 1] == '/')
		ret = _strcat("/", absPath, ret);
	ret = _strcat(cdPath, absPath, ret);

	return (absPath);
}
