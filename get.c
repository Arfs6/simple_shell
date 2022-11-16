#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "main.h"

unsigned int findSize(char *str, char *delm);

/**
 * getCmd - get command vector. e.g. argv
 * @env: clear env if EOF was encountered
 * @path: clear path if EOF was encountered
 * @status: status to exit if EOF was encountered
 *
 * Return: vector of command. format should be supported by execve()
 * NULL if no command was passed or
 * NULL if fails.
 */
char **getCmd(char **env, list_t **path, int *status, char *execName, int lineNo)
{
	char *cmd, *cmdLine, **cmdVector;
	int ret;
	size_t size = 0, temp = 0, i = 0;

	ret = getline(&cmdLine, &temp, stdin);
	/* since EOF can't be stored in char, can't send the info to execute() yet */
	if (ret == -1)
	{
		free(cmdLine);
		free_list(path);
		_free(NULL, env);
		_putchar('\n');
		exit(*status);
	}

	/* remove all whitty characters */
	for (i = 0; temp && i < temp - 1; ++i)
	{
		if (cmdLine[i] == '\t' || cmdLine[i] == '\n')
			cmdLine[i] = ' ';
	}

	size = findSize(_strdup(cmdLine), " ");
	cmd = strtok(cmdLine, " ");
	if (cmd == NULL)
		return (NULL);
	cmdVector = malloc(sizeof(*cmdVector) * (size + 1));
	if (cmdVector == NULL)
	{
		*status = 2;
		_dprintf(MEMERR, execName, lineNo);
		return (NULL);
	}
	i = 0;

	do {
		cmdVector[i] = _strdup(cmd);
		if (cmdVector[i] == NULL)
		{
			cmdVector[i + 1] = NULL;/* to confirm it is NULL terminated */
			_free(cmdVector, NULL);
			free(cmdLine);
		_dprintf(MEMERR, execName, lineNo);
			*status = 2;
			return (NULL);
		}
		cmd = strtok(NULL, " ");
		i++;
	} while (cmd);
	cmdVector[i] = NULL;

	free(cmdLine);

	return (cmdVector);
}

/**
 * findSize - finds the possible number of strings in the vector
 * @str: string to convert to vector
 *
 * @delim: de delmit for the string
 * Return: size of vector
 */
unsigned int findSize(char *str, char* delim)
{
	unsigned int size = 0;

	if (strtok(str, delim) == NULL)
	{
		free(str);
		return (0);
	}
	size++;
	while (strtok(NULL, delim))
		size++;

	free(str);
	return (size);
}

/**
 * getPathList - get PATH variable from environment variable
 * @env: environment variable
 *
 * Return: vector of paths in PATH
 * NULL if fails
 */
list_t *getPathList(char **env)
{
	char *temp, *path = NULL;
	list_t *head = NULL, *cur;
	int i = 0, tmp = 0;

	if (env == NULL || env[0] == NULL)
		return (NULL);

	tmp = getVariable("PATH", env);
	if (tmp == -1)
		return (NULL);
	path = env[tmp];
	path = _strdup(path);
	if (path == NULL)
		return (NULL);
	for (i = 0; i < 5; i++)
		path[i] = ':';

	i = findSize(_strdup(path), ":");
	temp = strtok(path, ":");
	if (temp == NULL)
		return (NULL);

	i = 0;
	while (temp != NULL)
	{
		cur = add_node_end(&head, temp);
		if (cur == NULL)
		{
			free(path);
			free_list(&head);
			return (NULL);
		}
		temp = strtok(NULL, ":");
	}

	free(path);
	return (head);
}

/**
 * getVariable - get a variable in environment variable
 * @variable: variable to search for
 * @env: environment variable
 *
 * Return: >=0: index of variable
 * -1: not found
 */
int getVariable(char *variable, char **env)
{
	int i = 0, temp;

	if (env == NULL || variable == NULL)
		return (-1);

	temp = _strlen(variable);
	for (i = 0; env[i]; i++)
	{
		if (_strncmp(variable, env[i], temp) == 0
				&& env[i][temp] == '=')
		{
			return (i);
		}
	}

	return (-1);/* not found */
}
