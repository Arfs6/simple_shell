#ifndef MAIN_H
#define MAIN_H

#include <stddef.h>
#include <stdio.h>

/* macros */
#define TRUE (1)
#define FALSE (0)
#define SUCCESS (0)
#define FAIL (-1)

#define SYSERR STDERR_FILENO, "%s: %i: "
#define MEMERR STDERR_FILENO, "%s: %i: cannot allocate memory\n"
#define NOTFOUNDERR STDERR_FILENO, "%s: %i: %s: not found\n"
#define PERMERR STDERR_FILENO, "%s: %i: %s: Permission denied\n"
#define INVNUMERR STDERR_FILENO, "%s: %i: exit: Illegal number: %s\n"

extern char **environ;

/**
 * struct path_s - link list to store PATH variable dirs
 * @dir: string containing directory
 * @next: pointer to next string
 */
struct path_s
{
	char *dir;
	struct path_s *next;
};
typedef struct path_s path_t;
/**
 * struct builtin_s - struct to store builtin commands
 * @cmd: command string
 * @func: command function
 */
struct builtin_s
{
	char *cmd;
	int (*func)(char *argv[], int status,
			path_t **path, char *execName, int lineNo);
};
typedef struct builtin_s builtin_t;

/* comments above prototypes states which files the source code is in */

/* execute.c */
int execute(char *argv[], char *execName, int lineNo, path_t
		**path, int status);

/* commands.c */
int execBuiltin(char **argv, int status,
		path_t **path, char *execName, int lineNo);
int terminate(char *argv[], int status,
		path_t **path, char *execName, int lineNo);
int printEnv(char *argv[], int status,
		path_t **path, char *execName, int lineNo);

/* setenv.c */
int unsetEnv(char *argv[], int status, path_t **path,
		char *execName, int lineNo);
int setEnv(char *argv[], int status,
		path_t **path, char *execName, int lineNo);

/* cd.c */
int changeDirectory(char *argv[], int status,
		list_t **path, char *execName, int lineNo);

/* functions0.c */
void _free(char **vector, char **env);
int intcat(int num, char *dest, int len);
void _memset(char *mem, size_t len);
int isSlash(char *str);
int checkAccess(char *path);

/* functions1.c */
int strToInt(char *str, int *num);
	int setPath(char **cmd, path_t *path);
void initEnv(void);
void useArg(char *argv[], int status,
		path_t **path, char *execName, int lineNo);
int increaseEnv(void);

/* functions2.c */
int _setenv(char *variable, char *value);
void handleSIGINT(int sigNum);

/* get.c */
char **getCmd(path_t **path, int *status,
		char *execName, int lineNo);
path_t *getPathList(void);
int getVariable(char *variable);

/* put.c */
int _putchar(char c);
int _puts(int fd, char *str);

/* strings.c */
int _strcat(char *dest, char *src, int len);
int _strlen(char *str);
char *_strdup(const char *str);
void strRev(char *str);
int _strncmp(char *str1, char *str2, int index);


/* linklists.c */
path_t *add_node_end(path_t **head, const char *str);
void free_list(path_t **head);

/* print.c */
int _dprintf(int fd, char *format, ...);

/* getline.c */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
void assign_lineptr(char **lineptr, size_t *n, char *buffer, size_t b);
/*ssize_t _getline(char **lineptr, size_t *n, FILE *stream);*/

/* strtok.c */
int _strtok_validate(char *str, char *backup, char *delm);
char *_strtok(char *str, char *delm);

#endif /* MAIN_H */
