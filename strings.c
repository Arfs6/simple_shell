#include <stdlib.h>
#include <stdio.h>

#include "main.h"

/**
* _strcat - concactenate two strings
* @src: String to concactinate
* @dest: concactenate here
* @len: index to start concatenating
*
* Return: concatenated string
*/
int _strcat(char *src, char *dest, int len)
{
	int j = 0;

	for (j = 0; src[j]; j++, len++)
	dest[len] = src[j];
	dest[len] = '\0';
	return (len);
}

/**
 * _strlen - finds the length of a NULL terminated string
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

/**
 * strRev - reverse a string
 * @str: string to reverse
*/
void strRev(char *str)
{
	int start, half, stop;
	char tmp;

	stop = start = half = 0;
	for (stop = 0; str[stop]; ++stop)
		;
	stop--;
	half = stop / 2;
	for (start = 0; start <= half; ++start, --stop)
	{
		tmp = str[start];
		str[start] = str[stop];
		str[stop] = tmp;
	}
}

/**
 * _strncmp - checks if two strings are equal
 * @str1: first string
 * @str2: second string
 * @index: index to stop searching
 *
 * Return: 0 success
 * negative value: str1 > str2
 * positive value: str2 > str1
 */
int _strncmp(char *str1, char *str2, int index)
{
	int i = 0;

	while (i < index)
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		if (str1[i] == '\0' || str2[i] == '\0')
			break;
		i++;
	}
	i--;

	return (str1[i] - str2[i]);
}
