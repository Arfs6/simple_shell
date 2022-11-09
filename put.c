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
 * _puts - prints a null terminated string to a stream
 * @str: string to print
 * @fd: file stream to write to
 *
 * Return: number of bites written (sucess)
 * -1 coudn't write
 */
int _puts(char *str, int fd)
{
	if (str == NULL)
		return (0);
	return (write(fd, str, _strlen(str)));
}
