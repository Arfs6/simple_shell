#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>
#include <unistd.h>

#include "main.h"

/**
 * _dprintf - custom dprintf
 * @fd: file descriptor to write to
 * @format: string specifying the format to be printed
 * @...: optional arguments for specifiers
 *
 * Return: 0 success
 * -1 can't write to file
 */
int _dprintf(int fd, char *format, ...)
{
	int i, idx;
	char buf[1024];
	va_list list;

	i = idx = 0;
	_memset(buf, 1024);
	va_start(list, format);

	for (i = 0; format[i]; ++i)
	{
		if (format[i] != '%')
			buf[idx++] = format[i];
		else
		{
			if (format[i + 1] == 'i')
				idx = intcat(va_arg(list, int), buf, idx);
			else if (format[i + 1] == 's')
				idx = _strcat(va_arg(list, char *), buf, idx);
			i++;
		}
	}

	va_end(list);
	return (write(fd, buf, idx));
}
