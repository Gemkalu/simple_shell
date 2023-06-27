#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* This is to read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* This is for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* This convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* This results to 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - This is a singly linked list
 * @num: This is the number field
 * @str: This is a string
 * @next: This points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct passinfo - This contains pseudo-arguements to pass into a function,
 * allowing uniform prototype for function pointer struct
 * @arg: This is a string generated from getline containing arguements
 * @argv: This is an array of strings generated from arg
 * @path: This is a string path for the current command
 * @argc: This is the argument count
 * @line_count: This is the error count
 * @err_num: This is the error code for exit()s
 * @linecount_flag: This if on count this line of input
 * @fname: This is the program filename
 * @env: This is linked list local copy of environ
 * @environ: This is the custom modified copy of environ from LL env
 * @history: the history node
 * @alias: This is the alias node
 * @env_changed: This is on if environ was changed
 * @status: This is the return status of the last exec'd command
 * @cmd_buf: This is address of pointer to cmd_buf, on if chaining
 * @cmd_buf_type: This is CMD_type ||, &&, ;
 * @readfd: This is the fd from which to read line input
 * @histcount: This is the history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
 * struct builtin - This contains a builtin string and related function
 * @type: This is the builtin command flag
 * @func: This is the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


/* This is toem_shloop.c */
int _hsh(info_t *, char **);
int _find_builtin(info_t *);
void _find_cmd(info_t *);
void _fork_cmd(info_t *);

/* This is toem_parser.c */
int _is_cmd(info_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(info_t *, char *, char *);

/* loophsh.c */
int _loophsh(char **);

/* toem_errors.c */
void g_eputs(char *);
int g_eputchar(char);
int g_putfd(char c, int fd);
int g_putsfd(char *str, int fd);

/* toem_string.c */
int g_strlen(char *);
int g_strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

/* toem_string1.c */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void g_puts(char *);
int g_putchar(char);

/* toem_exits.c */
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/* toem_tokenizer.c */
char **strtow(char *, char *);
char **strtow2(char *, char);

/* toem_realloc.c */
char *_memset(char *, char, unsigned int);
void _ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* toem_memory.c */
int _bfree(void **);

/* toem_atoi.c */
int _interactive(info_t *);
int _is_delim(char, char *);
int g_isalpha(int);
int g_atoi(char *);

/* toem_errors1.c */
int g_erratoi(char *);
void _print_error(info_t *, char *);
int _print_d(int, int);
char *convert_number(long int, int, int);
void _remove_comments(char *);

/* toem_builtin.c */
int g_myexit(info_t *);
int g_mycd(info_t *);
int g_myhelp(info_t *);

/* toem_builtin1.c */
int g_myhistory(info_t *);
int g_myalias(info_t *);

/*toem_getline.c */
ssize_t _get_input(info_t *);
int g_getline(info_t *, char **, size_t *);
void _sigintHandler(int);

/* toem_getinfo.c */
void _clear_info(info_t *);
void _set_info(info_t *, char **);
void _free_info(info_t *, int);

/* toem_environ.c */
char *_getenv(info_t *, const char *);
int g_myenv(info_t *);
int g_mysetenv(info_t *);
int g_myunsetenv(info_t *);
int _populate_env_list(info_t *);

/* toem_getenv.c */
char **get_environ(info_t *);
int g_unsetenv(info_t *, char *);
int g_setenv(info_t *, char *, char *);

/* toem_history.c */
char *get_history_file(info_t *info);
int _write_history(info_t *info);
int _read_history(info_t *info);
int _build_history_list(info_t *info, char *buf, int linecount);
int _renumber_history(info_t *info);

/* toem_lists.c */
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t _print_list_str(const list_t *);
int _delete_node_at_index(list_t **, unsigned int);
void _free_list(list_t **);

/* toem_lists1.c */
size_t _list_len(const list_t *);
char **list_to_strings(list_t *);
size_t _print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t _get_node_index(list_t *, list_t *);

/* toem_vars.c */
int _is_chain(info_t *, char *, size_t *);
void _check_chain(info_t *, char *, size_t *, size_t, size_t);
int _replace_alias(info_t *);
int _replace_vars(info_t *);
int _replace_string(char **, char *);

#endif


