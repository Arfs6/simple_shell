#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "main.h"

	int setPath(char **cmd, list_t *path);

/**
 * execute - execute an executable
 * @argv: arguments vector called with executable
 * @env: environment variable
 * @execName: name of shell executable
 * @lineNo: current line
 * @path: path to search for executables
 *
 * Return: -1 if fork or execve fails
 */
int execute(char *argv[], char *env[], char *execName,
		int lineNo, list_t *path)
{
	int ret = 0, status = 0;
	pid_t myPid;

	if (execBuiltin(argv, env) == 0)
		return (0);
	if (setPath(argv, path) == -1)
	{
		_dprintf(MEMERR, execName, lineNo);
		return (1);
	}
	ret = checkAccess(argv[0]);
	if (ret == -1)
	{
		_dprintf(NOTFOUNDERR, execName, lineNo, argv[0]);
		return (1);
	}
	else if (ret == -2)
	{
		_dprintf(PERMERR, execName, lineNo, argv[0]);
		return (2);
	}

		myPid = fork();
		if (myPid == -1)
		{
			_dprintf(SYSERR, execName, lineNo);
			perror(NULL);
		}
		if (myPid == 0)
		{
			ret = execve(argv[0], argv, env);
			if (ret == -1)
			{
				_dprintf(SYSERR, execName, lineNo);
				perror(NULL);
				return (ret);
			}
		}
		else
			wait(&status);

		return (status);
	}

/**
 * setPath - set path for executable
 * @cmd: command to search for
 * @path: link list to PATH variable
 *
 * Return: 0: right path set
 * -1: malloc fails
 */
	int setPath(char **cmd, list_t *path)
{
	int i = 0;
	char *buf;
	list_t *temp = path;

	if (isSlash(*cmd) == 0)
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
