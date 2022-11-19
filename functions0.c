#include <stdlib.h>
#include <unistd.h>

#include "main.h"

/**
 * _free - free a vector
 * @vector: vector to free
 * @env: environment variable
 */
void _free(char **vector, char **env)
{
	unsigned int i = 0;

	while (vector != NULL && vector[i] != NULL)
	{
		free(vector[i]);
		i++;
		if (vector[i] == NULL)
		{
			free(vector);
			vector = NULL;
			break;
		}
	}

	i = 0;
	while (env && env[i])
	{
		free(env[i]);
		i++;
		if (env[i] == NULL)
		{
			free(env);
			env = NULL;
			break;
		}
	}

}

/**
 * intcat - concatenate an int to a string
 * @dest: string to concatenate to
 * @num: int
 * @len: length of dest
 *
 * Return: length of dest after concatenation
 */
int intcat(int num, char *dest, int len)
{
	char str[20];
	int idx = 0;

	_memset(str, 20);

	if (num == 0)
	{
		str[0] = '0';
		str[1] = '\0';
		len = _strcat(str, dest, len);
		return (len);
	}
	else if (num < 0)
	{
		str[idx] = '-';
		num *= -1;
		idx++;
	}

	while (num > 0)
	{
		str[idx] = num % 10 + '0';
		num /= 10;
		idx++;
	}
	str[idx] = '\0';
	strRev(str);

	len = _strcat(str, dest, len);
	return (len);
}

/**
 * _memset - set all bits
 * @mem: memory to set
 * @len: lenght of memory
 */
void _memset(char *mem, size_t len)
{
	size_t i = 0;

	for (i = 0; i < len; ++i)
		mem[i] = '\0';
}

/**
 * checkAccess - check access status of a file
 * @path: path to file
 *
 * Return: 0: file exists and it is executable
 * -1: file doesn't exist
 *  -2: file is not executable
 */
int checkAccess(char *path)
{
	if (access(path, F_OK) == -1)
		return (-1);
	else if (access(path, X_OK) == -1)
		return (-2);

	return (SUCCESS);
}

/**
 * isSlash - check if string has a slash '/'
 * @str: string to parse
 *
 * Return: 0: str has a slash (SUCCESS)
 * -1: str has no slash (FAIL)
 */
int isSlash(char *str)
{
	int i = 0;

	for (i = 0; str[i]; ++i)
	{
		if (str[i] == '/')
			return (SUCCESS);
	}

	return (FAIL);
}
