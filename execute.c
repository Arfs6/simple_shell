#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "main.h"

int _execve(char *argv[], char *env[], char *execName, int lineNo);

	int setPath(char **cmd, list_t *path);

/**
 * execute - execute an executable
 * @argv: arguments vector called with executable
 * @env: environment variable
 * @execName: name of shell executable
 * @lineNo: current line
 * @path: path to search for executables
 * @status: status
 *
 * Return: -1 if fork or execve fails
 */
int execute(char *argv[], char *env[], char *execName,
		int lineNo, list_t *path, int status)
{
	int ret = 0;

	ret = execBuiltin(argv, env, status, path, execName, lineNo);
	if (ret >= SUCCESS)
		return (ret);
	if (setPath(argv, path) == -1)
	{
		_dprintf(MEMERR, execName, lineNo);
		return (2);
	}
	ret = checkAccess(argv[0]);
	if (ret == -1)
	{
		_dprintf(NOTFOUNDERR, execName, lineNo, argv[0]);
		return (2);
	}
	else if (ret == -2)
	{
		_dprintf(PERMERR, execName, lineNo, argv[0]);
		return (2);
	}

	status = _execve(argv, env, execName, lineNo);
	return (status);
}

/**
 * _execve - execute an executable
 * @argv: command vector
 * @env: environment variable
 * @execName: esecutable name
 * @lineNo: current line in shell
 *
 * Return: 0 success
 * -1 fail
 */
int _execve(char *argv[], char *env[], char *execName, int lineNo)
{
	pid_t myPid;
	int status = 0, ret = 0;

	myPid = fork();
	if (myPid == -1)
	{
		_dprintf(SYSERR, execName, lineNo);
		perror(NULL);
		return (2);
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
