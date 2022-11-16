#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "main.h"

unsigned int findSize(char *str, char *delm);

/**
 * getCmd - get command vector. e.g. argv
 * @path: clear path if EOF was encountered
 * @status: exit with status if eof was encountered
 *
 * Return: vector of command. format should be supported by execve()
 * NULL if no command was passed or
 * NULL if fails.
 */
char **getCmd(list_t *path, int *status)
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
		return (NULL);
	}
	i = 0;

	do {
		cmdVector[i] = _strdup(cmd);
		if (cmdVector[i] == NULL)
		{
			cmdVector[i + 1] = NULL;/* to confirm it is NULL terminated */
			_free(cmdVector);
			free(cmdLine);
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
unsigned int findSize(char *str, char *delim)
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
	char *temp, *path;
	list_t *head = NULL, *cur;
	int i = 0, tmp = 0;

	if (env == NULL || env[0] == NULL)
		return (NULL);

	path = env[i];
	while (path != NULL)
	{
		tmp = _strncmp(path, "PATH=", 5);
		if (tmp == 0)
		break;
		i++;
		path = env[i];
	}

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
			return (NULL);
		temp = strtok(NULL, ":");
	}

	return (head);
}
