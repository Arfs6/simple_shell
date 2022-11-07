#include <unistd.h>
#include <stdio.h>

#include "main.h"

/**
 * _putchar - print a character to standard output
 * @c: character to print
 *
 * Return: 1 sucess
 * -1 coudn't write
 */
int _putchar(char c)
{
	return (write(STDOUT_FILENO, &c, 1));
}

/**
 * _puts - prints a null-terminated string to standard output
 * @str: string to print
 *
 * Return: number of bites written (sucess)
 * -1 coudn't write
 */
int _puts(char *str)
{
	if (str == NULL)
		return (0);
	return (write(STDOUT_FILENO, str, _strlen(str)));
}
