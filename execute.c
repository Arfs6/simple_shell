#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "main.h"

/**
 * execute - execute an executable
 * @argv: arguments vector called with executable
 * @env: environment variable
 * @execveName: name of shell executable
 * @lineNo: current line
 *
 * Return: -1 if fork or execve fails
 */
int execute(char *argv[], char *env[], char *execName, int lineNo)
{
	int ret, status = 0;
	pid_t myPid;

	myPid = fork();
	if (myPid == -1)
	{
		printError(SYSERR, execName, lineNo);
		perror(NULL);
	}
	if (myPid == 0)
	{
		ret = execve(argv[0], argv, env);
		if (ret == -1)
		{
			printError(SYSERR, execName, lineNo);
			perror(NULL);
			return (ret);
		}
	}
	else
		wait(&status);

	return (status);
}
