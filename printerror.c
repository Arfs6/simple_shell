#include <stdio.h>

#include "main.h"

/**
 * printError - print appropriate error to stdout
 * @status: an int to determine what error to print, macros in main.h
 * @execName: name of shell executable
 * @lineNo: current line
 */
void printError(int status, char *execName, int lineNo)
{
	char buf[200];
	size_t idx = 0;

	_memset(buf, 200);
	idx = _strcat(execName, buf, idx);
	idx = _strcat(" : ", buf, idx);
	idx = intcat(lineNo, buf, idx);
	idx = _strcat(": ", buf, idx);

	if (status == MEMERR)
		idx = _strcat("cannot allocate memory\n", buf, idx);

	_puts(buf, 2);
}
