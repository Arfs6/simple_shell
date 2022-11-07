#include <stdlib.h>

/**
 * _strlen - finds the length of a NULL-terminated string
 * @str: string to find it's length
 *
 * Return: length of the string
 */
int _strlen(char *str)
{
	int len = 0;

	if (str == NULL)
		return (0);

	for (len = 0; str[len]; ++len)
		;

	return (len);
}

/**
 * _strdup - duplicate a string
 * @str: string to duplicate
 *
 * Return: pointer to the duplicated string (on success)
 * NULL if str = null
 * NULL if unsuccessful
*/
char *_strdup(const char *str)
{
	int i, len;
	char *dup;

	if (!str)
		return (NULL);

	for (len = 0; str[len]; ++len)
		;
	dup = malloc(sizeof(char) * (len + 1));
	if (!dup)
		return (NULL);

	/* duplicate str! */
	for (i = 0; i < len; ++i)
		dup[i] = str[i];
	dup[len] = '\0';

	return (dup);
}
