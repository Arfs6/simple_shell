#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "main.h"

unsigned int findSize(char *str);

/**
 * getCmd - get command vector. e.g. argv
 *
 * Return: vector of command. format should be supported by execve()
 * NULL if no command was passed or
 * NULL if fails.
 */
char **getCmd(void)
{
	char *cmd, *cmdLine, **cmdVector;
	int ret;
	size_t size = 0, temp = 0, i = 0;

	ret = getline(&cmdLine, &temp, stdin);
	/* since EOF can't be stored in char, can't send the info to execute() yet */
	if (ret == -1)
		exit(0);

	/* remove all whitty characters */
	for (i = 0; temp && i < temp - 1; ++i)
	{
		if (cmdLine[i] == '\t' || cmdLine[i] == '\n')
			cmdLine[i] = ' ';
	}

	size = findSize(_strdup(cmdLine));
	cmd = strtok(cmdLine, " ");
	if (cmd == NULL)
		return (NULL);
	cmdVector = malloc(sizeof(*cmdVector) * (size + 1));
	i = 0;

	do {
		cmdVector[i] = _strdup(cmd);
		if (cmdVector[i] == NULL)
		{
			cmdVector[i + 1] = NULL;/* to confirm it is NULL terminated */
			_free(cmdVector);
			free(cmdLine);
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
 * Return: size of vector
 */
unsigned int findSize(char *str)
{
	unsigned int size = 0;

	if (strtok(str, " ") == NULL)
	{
		free(str);
		return (0);
	}
	size++;
	while (strtok(NULL, " "))
		size++;

	free(str);
	return (size);
}
