#include <stdlib.h>
#include <unistd.h>

#include "main.h"

#define CDERR (STDERR_FILENO, "%s: %i: cd: can't cd to %s\n", \
		execName, lineNo, cdPath)

int cdHOME(char *execName, int lineNo);
int cdOLDPWD(char *execName, int lineNo);
int cdDir(char *argv[], char *execName, int lineNo);
int updatePWD(char *cdPath);
char *setCdPath(char *cdPath);

/**
 * changeDirectory - changes the current directory of the shell
 * @argv: command vector
 * @status: status of last executed command
 * @path: link list for dir in PATH variable
 * @execName: name of executable of the shell
 * @lineNo: current line number in shell
 *
 * Return: 0: success (SUCCESS)
 * 2: coudn't change directory
 * 3: insufficient memory
 */
int changeDirectory(char *argv[], int status,
		path_t **path, char *execName, int lineNo)
{
	/* suppressing unused argument error */
	useArg(NULL, status, path, NULL, 0);

	if (argv[1] == NULL)
		return (cdHOME(execName, lineNo));
	else if (_strncmp(argv[1], "-", 2) == 0)
		return (cdOLDPWD(execName, lineNo));

	return (cdDir(argv, execName, lineNo));
}

/**
 * cdHOME - change current working directory to user home directory
 * @execName: Executable name to use while printing error
 * @lineNo: Line number to print while printing error
 *
 * Return: 0: success (SUCCESS)
 * 2: coudn't change directory
 * 3: insufficient memory
 */
int cdHOME(char *execName, int lineNo)
{
	int ret;
	char *cdPath;

	ret = getVariable("HOME");
	if (ret == -1)
		return (0);

	cdPath = environ[ret];
	cdPath += 5;
	ret = chdir(cdPath);
	if (ret == -1)
	{
		_dprintf(CDERR);
		return (0);
	}

	ret = updatePWD(cdPath);

	return (ret);
}

/**
 * cdOLDPWD - change current working directory to old working directory
 * @execName: name of executable to use while printing error
 * @lineNo: line number to use while printing error
 *
 * Return: 0: success (SUCCESS)
 * 2: coudn't change directory
 * 3: insufficient memory
 */
int cdOLDPWD(char *execName, int lineNo)
{
	int ret;
	char *cdPath, *pwd;

	ret = getVariable("PWD");
	if (ret == -1)
		pwd = "";
	else
	{
		pwd = environ[ret];
		pwd += 4;
	}

	ret = getVariable("OLDPWD");
	if (ret == -1)
	{
		_dprintf(STDOUT_FILENO, "%s\n", pwd);
		return (0);
	}

	cdPath = environ[ret];
	cdPath += 7;
	ret = chdir(cdPath);
	if (ret == -1)
	{
		_dprintf(CDERR);
		return (2);
	}

	_dprintf(STDOUT_FILENO, "%s\n", cdPath);
	ret = updatePWD(cdPath);

	return (ret);
}

/**
 * cdDir - change current working directory to directory passed
 * @argv: command vector containing directory
 * @execName: executable name to use while printing error
 * @lineNo: line number to use while printing error
 *
 * Return: 0: success (SUCCESS)
 * 2: coudn't change directory
 * 3: insufficient memory
 */
int cdDir(char *argv[], char *execName, int lineNo)
{
	int ret;
	char *cdPath = argv[1];

	ret = chdir(cdPath);
		if (ret == -1)
		{
			_dprintf(CDERR);
			return (2);
		}

	ret = updatePWD(cdPath);

	return (ret);
}

/**
 * updatePWD - update PWD and OLDPWD variables in environment variable
 * @_cdPath: current working directory
 *
 * Return: 0: success (SUCCESS)
 * 3: insufficient memory
 */
int updatePWD(char *_cdPath)
{
	int ret;
	char *oldpwd, *cdPath;

	cdPath = setCdPath(_cdPath);
	if (cdPath == NULL)
		return (3);

	ret = getVariable("PWD");
	if (ret == -1)
	{
		ret = _setenv("PWD", cdPath);
		if (ret == -1)
		{
			free(cdPath);
			return (3);
		}
		free(cdPath);
		return (0);
	}

	oldpwd = environ[ret];
	oldpwd += 4;

	ret = _setenv("OLDPWD", oldpwd);
	if (ret == -1)
	{
		free(cdPath);
		return (3);
	}

	ret = _setenv("PWD", cdPath);
			free(cdPath);
	if (ret == -1)
		return (3);

	return (SUCCESS);
}
