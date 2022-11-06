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
}
