#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "main.h"

int setPath(char **cmd, list_t *path, char *execName, int lineNo, int argc);

/**
 * execute - execute an executable
 * @argv: arguments vector called with executable
 * @env: environment variable
 * @execveName: name of shell executable
 * @lineNo: current line
 * @path: path to search for executables
 * @argc: number of arguments the programme recieved
 *
 * Return: -1 if fork or execve fails
 */
int execute(char *argv[], char *env[], char *execName, int lineNo, list_t *path, int argc)
{
	int ret = 0, status = 0, i = 0;
	pid_t myPid;

	for (i = 0; argv[0][i]; i++)
	{
		if (argv[0][i] == '/')
		{
			if (access(argv[0], F_OK) == 0)
			{
				if (access(argv[0], X_OK) == -1)
				{
					_dprintf(PERMERR, execName, lineNo, argv[0]);
					return (FAIL);
				}
			}
			else
			{
				_dprintf(NOTFOUNDERR, execName, lineNo, argv[0]);
				return (FAIL);
			}
			ret = 1;
		}
	}
		if (ret == 0)
			ret = setPath(argv, path, execName, lineNo, argc);
		if (ret == FAIL)
			return (FAIL);

		if (argc > 1)
		{
			ret = execve(argv[0], argv, env);
			if (ret == -1)
			{
				_dprintf(SYSERR, execName, lineNo);
				perror(NULL);
			}
			return (ret);
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
	 * Return: 0 found executable
	 * -1 executable not found
	 */
	int setPath(char **cmd, list_t *path, char *execName, int lineNo, int argc)
	{
		int i = 0;
		char *buf;
		list_t *temp = path;

		while (temp)
		{
			buf = malloc(sizeof(char) * (_strlen(*cmd) + _strlen(temp->dir) + 2));
			if (buf == NULL)
			{
				_dprintf(MEMERR, execName, lineNo);
				return (FAIL);
			}
			i = 0;
			i = _strcat(temp->dir, buf, i);
			if (buf[i - 1] != '/')
				i = _strcat("/", buf, i);
			i = _strcat(*cmd, buf, i);
			if (access(buf, F_OK) == 0)
			{
				if (access(buf, X_OK) == -1)
				{
					_dprintf(PERMERR, execName, lineNo, *cmd);
					return (-1);
				}
				if (argc == 1)
					free(*cmd);
				*cmd = buf;
				return (0);
			}

			free(buf);
			temp = temp->next;
		}

		_dprintf(NOTFOUNDERR, execName, lineNo, *cmd);
		return (FAIL);
	}
