#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>
#include <stddef.h>
#include <sys/stat.h>
#include <signal.h>

int g_putchar(char c);
void g_puts(char *str);
int g_strlen(char *s);
char *g_strdup(char *str);
char *gconcat_all(char *name, char *sep, char *gvalue);

char **gsplitstring(char *str, const char *delim);
void gexecute(char **argv);
void *g_realloc(void *ptr, unsigned int old_size, unsigned int new_size);


extern char **environ;

/**
 * struct list_path - This is a Linked list containing PATH directories
 * @dir: This is a directory in path
 * @p: This is a pointer to next node
 */
typedef struct list_path
{
	char *dir;
	struct list_path *p;
} list_path;


char *_getenv(const char *name);
list_path *add_node_end(list_path **head, char *str);
list_path *linkpath(char *path);
char *_which(char *filename, list_path *head);

/**
 * struct mybuild - This points to function with corresponding buildin command
 * @name: This is a  buildin command
 * @func: This execute the buildin command
 */
typedef struct mybuild
{
	char *name;
	void (*func)(char **);
} mybuild;

void(*gcheckbuild(char **arv))(char **arv);
int g_atoi(char *s);
void gexitt(char **arv);
void genv(char **arv);
void g_setenv(char **arv);
void g_unsetenv(char **arv);

void gfreearv(char **arv);
void gfree_list(list_path *head);


#endif
