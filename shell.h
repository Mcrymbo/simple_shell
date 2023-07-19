#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <limits.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <limits.h>
#include <errno.h>
#include <sys/stat.h>

#define BUFSIZE 1024
#define TOK_SIZE 128
#define TOK_DEL " \t\r\n\a"

extern char **environ; /** environment variable**/

/**
 * struct data - contains relevant data on runtime
 * @av: argument vector
 * @input: comand written by user
 * @args: tokens of command line
 * @counter: counts of line
 * @status: last status of the shell
 * @_environ: environment variable
 * @pid: process ID of shell
 */
typedef struct dat
{
	char **av;
	char *input;
	char **args;
	int counter;
	int status;
	char **_environ;
	char *pid;
} shell_d;

/**
 * struct builtins - data structure for handling command arguments
 * @name: built-in command name
 * @f: function pointer
 */
typedef struct builtins
{
	char *name;
	int (*f)(shell_d *data);
} builtins_cmd;

/**
 * struct lin_list - singly linked list to store command
 * @line: command line
 * @next: next node
 */
typedef struct lin_list
{
	char *line;
	struct lin_list *next;
} line_list;

/**
 * struct sep_lis - list to store separator
 * @sep: separator
 * @next: next node
 */
typedef struct sep_lis
{
	char sep;
	struct sep_lis *next;
} sep_list;

/** get_sigint.c **/
void get_sigint(int sig);

/**aux_stdlib.c **/
int get_len(int n);
char *aux_itoa(int n);
int _atoi(char *s);

/** aux_str.c **/
char *_strcat(char *dest, char *src);
char *_strcpy(char *dest, char *src);
int _strcmp(char *s1, char *s2);
char *_strchr(char *s, char c);
int _strspn(char *s, char *accept);

/** aux_str2.c **/
char *_strdup(const char *s);
int _strlen(const char *str);
int _isdigit(const char *s);

/** aux_mem.c **/
void _memcpy(void *dest, const void *src, unsigned int size);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char **_reallocdp(char **ptr, unsigned int old_size, unsigned int new_size);

/** read_line.c **/
char *read_line(int *line);

/** shell_loop.c **/
void shell_loop(shell_d *datash);
/** cmd_exec.c **/
int check_error_cmd(char *dir, shell_d *data);
int _executables(shell_d *data);
int cmd_exec(shell_d *data);
int is_cdir(char *path, int *i);
char *_which(char *command, char **_environ);

/** aux_environment.c **/
char *_getenv(const char *name_env, char **_env);
int comp_env(const char *name_env, const char *name);

/** aux_split.c **/
char **line_tok(char *input);
int split_cmd(shell_d *data, char *input);

/** sh_exit.c **/
int sh_exit(shell_d *data);

/** handle_builtin.c **/
int (*get_builtin(char *command))(shell_d *);

/** line_exec.c **/
int line_exec(shell_d *data);

#endif
