#include <stdlib.h>

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
