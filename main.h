#ifndef MAIN_H
#define MAIN_H

#include <stddef.h>

/* macros */
#define TRUE (1)
#define FALSE (0)
#define FAIL (-1)

#define SYSERR STDERR_FILENO, "%s: %i: "
#define MEMERR STDERR_FILENO, "%s: %i: cannot allocate memory\n"
#define NOTFOUNDERR STDERR_FILENO, "%s: %i: %s: not found\n"
#define PERMERR STDERR_FILENO, "%s: %i: %s: Permission denied\n"

/**
 * struct list_s - link list to store PATH variable dirs
 * @dir: string containing directory
 * @next: pointer to next string
 */
struct list_s
{
	char *dir;
	struct list_s *next;
};
typedef struct list_s list_t;

/* comments above prototypes states which files the source code is in */

/* execute.c */
int execute(char *argv[], char *env[], char *execName, int lineNo, list_t
		*path, int argc);

/* functions.c */
void _free(char **);
int intcat(int num, char *dest, int len);
void _memset(char *mem, size_t len);

/* get.c */
char **getCmd(list_t *path);
list_t *getPathList(char **env);

/* put.c */
int _putchar(char c);
int _puts(char *str, int fd);

/* strings.c */
int _strcat(char *dest, char *src, int len);
int _strlen(char *str);
char *_strdup(const char *str);
void strRev(char *str);
int _strncmp(char *str1, char *str2, int index);

/* printerror.c */
void printError(int status, char *execName, int lineNo, ...);

/* linklists.c */
list_t *add_node_end(list_t **head, const char *str);
void free_list(list_t *head);

/* print.c */
int _dprintf(int fd, char *format, ...);

#endif /* MAIN_H */
