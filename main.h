#ifndef MAIN_H
#define MAIN_H

/* macros */
#define TRUE (1)
#define FALSE (0)
#define FAIL (-1)

/* comments above prototypes states which files the source code is in */

/* functions.c */
void _free(char **);

/* getcmd.c */
char **getCmd(char **str);
/* put.c */
int _putchar(char c);
int _puts(char *str);

/* strings.c */
int _strlen(char *str);
char *_strdup(const char *str);

#endif /* MAIN_H */
