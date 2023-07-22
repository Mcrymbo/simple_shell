#include "shell.h"

/**
 * is_cdir - checks if the file is in current directory
 * @path: path to search
 * @i: pointer to index
 * Return: 1 for searchable path and 0 otherwise
 */
int is_cdir(char *path, int *i)
{
	if (path[*i] == ':')
		return (1);
	while (path[*i] && path[*i] != ':')
		*i += 1;
	if (path[*i])
		*i += 1;
	return (0);
}

/**
 * _which - used in locating a command from environment variables
 * @command: name of the command
 * @_environ: environment variable
 * Return: location of command
 */
char *_which(char *command, char **_environ)
{
	int len_d, len_cm, i;
	struct stat st;
	char  *dir, *tkn, *path, *path_ptr;

	path = _getenv("PATH", _environ);
	if (path)
	{
		i = 0;
		path_ptr = _strdup(path);
		len_cm = _strlen(command);
		tkn = strtok(path_ptr, ":");
		while (tkn)
		{
			if (is_cdir(path, &i))
			{
				if (stat(command, &st) == 0)
					return (command);
			}
			len_d = _strlen(tkn);
			dir = malloc(len_d + len_cm + 2);
			_strcpy(dir, tkn);
			_strcat(dir, "/");
			_strcat(dir, command);
			_strcat(dir, "\0");
			if (stat(dir, &st) == 0)
			{
				free(path_ptr);
				return (dir);
			}
			free(dir);
			tkn = strtok(NULL, ":");
		}
		free(path_ptr);
		if (stat(command, &st) == 0)
			return (command);
		return (NULL);
	}
	if (command[0] == '/')
	{
		if (stat(command, &st) == 0)
			return (command);
	}
	return (NULL);
}

/**
 * check_error_cmd -  verify whether the user has necessary permission
 * @dir: directory
 * @data: args
 * Return: 1 if error
 */
int check_error_cmd(char *dir, shell_d *data)
{
	if (dir == NULL)
	{
		handle_error(data, 127);
		return (1);
	}
	if (_strcmp(data->args[0], dir) != 0)
	{
		if (access(dir, X_OK) == -1)
		{
			free(dir);
			return (1);
		}
		free(dir);
	}
	else
	{
		if (access(data->args[0], X_OK) == -1)
		{
			return (1);
		}
	}
	return (0);
}

/**
 * _executable - determines if the command passed is executable
 * @data: gives args from data structure
 * Return: 0 if not executables
 */
int is_executables(shell_d *data)
{
	struct stat st;
	char *input;
	int i;

	input = data->args[0];
	for (i = 0; input[i]; i++)
	{
		if (input[i] == '.')
		{
			if (input[i + 1] == '.')
				return (0);
			if (input[i + 1] == '/')
				continue;
			else
				break;
		}
		else if (input[i] == '/' && i != 0)
		{
			if (input[i + 1] == '.')
				continue;
			i++;
			break;
		}
		else
			break;
	}
	if (i == 0)
		return (0);
	if (stat(input + i, &st) == 0)
		return (i);
	return (-1);
}

/**
 * cmd_exec - performs executio of commands
 * @data: takes args and input from data structure
 * Return: 1 on success
 */
int cmd_exec(shell_d *data)
{
	pid_t pd;
	int state;
	char *dir;
	pid_t wait_pid;
	int exec;
	(void) wait_pid;

	exec = is_executables(data);
	if (exec == -1)
		return (1);
	if (exec == 0)
	{
		dir = _which(data->args[0], data->_environ);
		if (check_error_cmd(dir, data) == 1)
			return (1);
	}
	pd = fork();
	if (pd == -1)
	{
		perror(data->av[0]);
		return (1);
	}
	else if (pd == 0)
	{
		if (exec == 0)
			dir = _which(data->args[0], data->_environ);
		else
			dir = data->args[0];
		execve(dir + exec, data->args, data->_environ);
	}
	else
	{
		do {
			wait_pid = waitpid(pd, &state, WUNTRACED);
		} while (!WIFEXITED(state) && !WIFSIGNALED(state));
	}
	data->status = state / 256;
	return (1);
}
