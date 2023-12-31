#include "shell.h"

/**
 * _env - prints environment variables
 * @data: data structure (_environ)
 * Return: no return
 */
int  _env(shell_d *data)
{
	int i, j;

	for (i = 0; data->_environ[i]; i++)
	{
		for (j = 0; data->_environ[i][j]; j++)
			;
		write(1, data->_environ[i], j);
		write(1, "\n", 1);
	}
	data->status = 0;
	return (1);
}

/**
 * _setenv - update or add environment variable
 * @data: data structure (name and val)
 * Return: 1 if success
 */
int _setenv(shell_d *data)
{
	if (data->args[1] == NULL || data->args[2] == NULL)
	{
		handle_error(data, -1);
		return (1);
	}
	env_set(data->args[1], data->args[2], data);
	return (1);
}

/**
 * env_set - a function that set env variable
 * @name: env variable's name
 * @val: value of env var
 * @data: data structure (provide _environ)
 * Return: nothing
 */
void env_set(char *name, char *val, shell_d *data)
{
	char *env_var, *env_name;
	int i;

	for (i = 0; data->_environ[i]; i++)
	{
		env_var = _strdup(data->_environ[i]);
		env_name = _strtok(env_var, "=");
		if (_strcmp(env_name, name) == 0)
		{
			free(data->_environ[i]);
			data->_environ[i] = infocpy(env_name, val);
			free(env_var);
			return;
		}
		free(env_var);
	}
	data->_environ = _reallocdp(data->_environ, i, sizeof(char) * (i + 2));
	data->_environ[i] = infocpy(name, val);
	data->_environ[i + 1] = NULL;
}

/**
 * infocpy - used to copy info needed.
 * @name: name of env var
 * @val: value of env var
 * Return: new env
 */
char *infocpy(char *name, char *val)
{
	char *env;
	int len;

	len = _strlen(name) + _strlen(val);
	env = malloc(sizeof(char) * (len + 2));
	if (env == NULL)
		return (NULL);
	_strcpy(env, name);
	_strcat(env, "=");
	_strcat(env, val);
	_strcat(env, "\0");

	return (env);
}

/**
 * _unsetenv - deletes and env var
 * @data: data structure (name of env var)
 * Return: 1 for success
 */
int _unsetenv(shell_d *data)
{
	char **new_env;
	char *env_var, *env_name;
	int a, i, j;

	if (!data->args[1])
	{
		handle_error(data, -1);
		return (1);
	}
	a = -1;
	for (i = 0; data->_environ[i]; i++)
	{
		env_var = _strdup(data->_environ[i]);
		env_name = _strtok(env_var, "=");
		if (_strcmp(env_name, data->args[1]) == 0)
			a = i;
		free(env_var);
	}
	if (a == -1)
	{
		handle_error(data, -1);
		return (1);
	}
	new_env = malloc(sizeof(char *) * (i));
	for (i = j = 0; data->_environ[i]; i++)
	{
		if (i != a)
		{
			new_env[j] = data->_environ[i];
			j++;
		}
	}
	new_env[j] = NULL;
	free(data->_environ[a]);
	free(data->_environ);
	data->_environ = new_env;
	return (1);
}
