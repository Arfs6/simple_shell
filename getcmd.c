#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "main.h"

unsigned int findSize(char *str);

/**
 * getCmd - get command vector. e.g. argv
 * @str: vector if shell was started with arguments
 *
 * Return: vector of command. format should be supported by execve()
 * NULL if no command was passed or
 * NULL if fails.
 */
char **getCmd(char **str)
{
	char *cmd, *cmdLine, **cmdVector;
	int ret, i = 0;
	unsigned int size;
	unsigned long int temp = 0;

	if (str != NULL)
	{
		*cmdVector = str[1];
		return (cmdVector);
	}

	ret = getline(&cmdLine, &temp, stdin);
	/* since EOF can't be stored in char, can't send the info to execute() yet */
	if (ret == -1)
		exit(0);

	/* remove all whitty characters */
	for (i = 0; i < temp - 1; ++i)
	{
		printf("0x%x ", cmdLine[i]);
		if (cmdLine[i] == '\t' || cmdLine[i] == '\n' || cmdLine[i] == '\0')
			cmdLine[i] = ' ';
		printf("0x%x ", cmdLine[i]);
	}

	cmd = strtok(cmdLine, " ");
	printf("cmd = %s\ncmdLine = %s\n", cmd, cmdLine);
	if (cmd == NULL)
		return (NULL);
	size = findSize(cmdLine);
	cmdVector = malloc(sizeof(*cmdVector) * size);
	i = 0;

	do {
		cmdVector[i] = _strdup(cmd);
		printf("%s : %s\n", cmd, "");
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

	strtok(str, " ");
	size++;
	while (strtok(NULL, " "))
		size++;

	return (size);
}
