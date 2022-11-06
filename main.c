#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int execute(char **av, char **env)

/**
 * main - entery code for shell
 * @ac: arguments count
 * @av: arguments vector
 * @env: environment variables vector
 *
 * Return: 0 (sucess)
 */
int main(int ac, char **av, char **env)
{
	char *buf = NULL;
	size_t *bufferSize = 0;
	int ret = 0;

	do{
		ret = getline(buffer, *bufferSize, stdout);
		if (ret == -1)
			exit(1);
		_puts("$ ");
		ret = execute(av, env);
	} while(TRUE);

	return (0);
}

/**
 * execute - execute a command
 * @av: command vector
 * @env: environment variables
 *
 * Return: 0 sucess
 * -1 coudn't execute
 */
int execute(char **av, char **env)
{
	struct stat *info;

	if (
