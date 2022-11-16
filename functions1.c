#include <stdlib.h>
#include <unistd.h>

#include "main.h"

/**
 * strToInt - converts a string to an int
 * @str: pointer to string
 * @num: pointer to integer
 *
 * Return: 0: converted successfully (SUCCESS)
 * -1: invalid character in string (FAIL)
 */
int strToInt(char *str, int *num)
{
	int i = 0;
	int mul = 1;

	if (str == NULL)
		return (FAIL);

	for (i = 0; str[i]; ++i)
	{
		if (str[i] < '0' || str[i] > '9')
			return (FAIL);
	}

	strRev(str);
	*num = 0;

	for (i = 0; str[i]; ++i)
	{
		*num += (str[i] - '0') * mul;
		mul *= 10;
	}

	strRev(str);

	return (SUCCESS);
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

	if (path == NULL)
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
