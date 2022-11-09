#ifndef MAIN_H
#define MAIN_H

#include <stddef.h>

/* macros */
#define TRUE (1)
#define FALSE (0)
#define FAIL (-1)

#define SYSERR (0)
#define MEMERR (1)
#define NOTFOUNDERR (2)

/* comments above prototypes states which files the source code is in */

/* execute.c */
int execute(char *argv[], char *env[], char *execName, int lineNo);

/* functions.c */
void _free(char **);
int intcat(int num, char *dest, int len);
void _memset(char *mem, size_t len);

/* getcmd.c */
char **getCmd(void);
/* put.c */
int _putchar(char c);
int _puts(char *str, int fd);

/* strings.c */
int _strcat(char *dest, char *src, int len);
int _strlen(char *str);
char *_strdup(const char *str);
void strRev(char *str);

/* printerror.c */
void printError(int status, char *execName, int lineNo);

#endif /* MAIN_H */
