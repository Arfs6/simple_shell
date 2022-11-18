#include <unistd.h>
#include <stdlib.h>

#include "main.h"

/**
 * unsetEnv - delete's an environment variable
 * @argv: command vector
 * @status: status of last executed command
 * @path: link list of dirs in PATH variable
 * @execName: name of executable
 * @lineNo: current line number in shell
 *
 * Return: 0: success
 * -1: malloc fails or coudn't find variable
 */
int unsetEnv(char *argv[], int status, list_t **path,
		char *execName, int lineNo)
{
	int idx = 0;

	if (argv[1] == NULL)
	{
		_dprintf(STDERR_FILENO, "%s: %i: unsetenv: variable not specified\n", execName, lineNo);
		return (2);
	}

	status = status; /* suppress not used parameter error */
	idx = getVariable(argv[1]);
	if (idx == -1)
	{
		_dprintf(STDERR_FILENO, "%s: %i: unsetenv: %s: not found\n", execName, lineNo, argv[1]);
		return (2);
	}

	free(environ[idx]);
	environ[idx] = NULL;

	/* move the NULL to the end */
	while (TRUE)
	{
		if (environ[idx + 1] == NULL)
			break;
		environ[idx] = environ[idx + 1];
		environ[idx + 1] = NULL;
		idx++;
	}

	idx = getVariable("PATH");
	if (idx == -1)/* PATH was deleted */
	{
		free_list(path);
		*path = NULL;
	}

	return (SUCCESS);
}

/**
 * setEnv - command to set an environment variable
 * @argv: command vector
 * @status: status of last executed command
 * @path: link list of directories in PATH variable
 * @execName: executable name of this shell
 * @lineNo: current line inshell
 */
int setEnv(char *argv[], int status,
		list_t **path, char *execName, int lineNo)
{
	int ret = 0;

	useArg(NULL, status, path, NULL, 0);

	if (argv[1] == NULL || argv[2] == NULL)
	{
		_dprintf(STDERR_FILENO, "%s: %i: setenv: usage: setenv variable value\n", execName, lineNo);
		return (2);
	}

	ret= _setenv(argv[1], argv[2]);
	if (ret == FAIL)
	{
		_dprintf(MEMERR, execName, lineNo);
		return (2);
	}

	if (_strncmp(argv[1], "PATH", _strlen("PATH")) == 0)
		*path = getPathList();

	return (SUCCESS);
}
