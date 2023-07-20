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
} builtin_cmd;

/**
 * struct var_list - sinply linked list to store variables
 * @len_var: holds length of the variable
 * @val: holds the value of variable
 * @len_val: store length of val
 * @next: next node
 */
typedef struct var_list
{
	int len_var;
	char *val;
	int len_val;
	struct var_list *next;
} var_r;

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
int line_exec(shell_d *data);

/** sh_exit.c **/
int sh_exit(shell_d *data);

/** handle_builtins.c **/
 int (*get_builtin(char *command))(shell_d *);

 /** aux_split.c  **/
 int split_cmd(shell_d *data, char *input);
 void add_node(sep_list **h_sep, line_list **h_line, char *input);
 void go_next(sep_list **lst_s, line_list **lst_l, shell_d *data);
 char *swap_char(char *input, int bool);

 /** handle_environ. c **/
  void env_check(var_r **h, char *input, shell_d *data);
  char *rep_var(char *input, shell_d *data);
  char *replaced_input(var_r **h, char *input, char *new_input, int nlen);
  int check_vars(var_r **h, char *input, char *status, shell_d *data);

  /** var_list.c **/
  void free_varlist(var_r **h);
  var_r *add_var_node(var_r **h, int len_var, char *val, int len_val);

  /** handle_list.c **/
  sep_list *add_node_end_sep(sep_list **h, char s);
  void free_seplist(sep_list **h);
  line_list *add_node_end_line(line_list **h, char *input);
  void free_linelist(line_list **h);

#endif
