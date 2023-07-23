#include "shell.h"

/**
 * copy_info - copies info to create
 * a new env or alias
 * @name: name (env or alias)
 * @value: value (env or alias)
 *
 * Return: new env or alias.
 */
/**char *infocpy(char *name, char *value)
{
	char *new;
	int len_name, len_value, len;

	len_name = _strlen(name);
	len_value = _strlen(value);
	len = len_name + len_value + 2;
	new = malloc(sizeof(char) * (len));
	_strcpy(new, name);
	_strcat(new, "=");
	_strcat(new, value);
	_strcat(new, "\0");

	return (new);
}**/

/**
 * set_env - sets an environment variable
 *
 * @name: name of the environment variable
 * @value: value of the environment variable
 * @datash: data structure (environ)
 * Return: no return
 */
/**void env_set(char *name, char *value, shell_d *data)
{
	int i;
	char *var_env, *name_env;

	for (i = 0; data->_environ[i]; i++)
	{
		var_env = _strdup(data->_environ[i]);
		name_env = _strtok(var_env, "=");
		if (_strcmp(name_env, name) == 0)
		{
			free(data->_environ[i]);
			data->_environ[i] = infocpy(name_env, value);
			free(var_env);
			return;
		}
		free(var_env);
	}

	data->_environ = _reallocdp(data->_environ, i, sizeof(char *) * (i + 2));
	data->_environ[i] = infocpy(name, value);
	data->_environ[i + 1] = NULL;
}**/

/**
 * _setenv - compares env variables names
 * with the name passed.
 * @datash: data relevant (env name and env value)
 *
 * Return: 1 on success.
 */
/**int _setenv(shell_d *datash)
{

	if (datash->args[1] == NULL || datash->args[2] == NULL)
	{
		handle_error(datash, -1);
		return (1);
	}

	env_set(datash->args[1], datash->args[2], datash);

	return (1);
}**/

/**
 * _unsetenv - deletes a environment variable
 *
 * @datash: data relevant (env name)
 *
 * Return: 1 on success.
 */
/**int _unsetenv(shell_d *datash)
{
	char **realloc_environ;
	char *var_env, *name_env;
	int i, j, k;

	if (datash->args[1] == NULL)
	{
		handle_error(datash, -1);
		return (1);
	}
	k = -1;
	for (i = 0; datash->_environ[i]; i++)
	{
		var_env = _strdup(datash->_environ[i]);
		name_env = _strtok(var_env, "=");
		if (_strcmp(name_env, datash->args[1]) == 0)
		{
			k = i;
		}
		free(var_env);
	}
	if (k == -1)
	{
		handle_error(datash, -1);
		return (1);
	}
	realloc_environ = malloc(sizeof(char *) * (i));
	for (i = j = 0; datash->_environ[i]; i++)
	{
		if (i != k)
		{
			realloc_environ[j] = datash->_environ[i];
			j++;
		}
	}
	realloc_environ[j] = NULL;
	free(datash->_environ[k]);
	free(datash->_environ);
	datash->_environ = realloc_environ;
	return (1);
}**/
