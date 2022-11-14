#include <stdio.h>
#include <unistd.h>

/**
 * _getline - reads an entire line from stream
 * @line: address of buffer containing text
 * @n: number of bytes read
 *
 * Return: number of read bytes on success, -1 on failure
 */
ssize_t _getline(char **line, size_t *n)
{
	ssize_t rbytes;

	*line = malloc(n);
	if (*line == NULL)
	{
		perror("_getline failed");
		return (-1);
	}

	rbytes = read(STDIN_FILENO, *line, n);
	if (rbytes == -1)
	{
		free(*line);
		perror("read failed");
		return (-1);
	}
	free(*line);
	return (rbytes);
}
