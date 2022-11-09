#include <stdlib.h>

#include "main.h"

/**
 * _free - ree the vector
 * @vector: vector to free
 */
void _free(char **vector)
{
	unsigned int i = 0;

	while (vector[i])
	{
		free(vector[i]);
		i++;
	}

	free(vector);
	vector = NULL;
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
