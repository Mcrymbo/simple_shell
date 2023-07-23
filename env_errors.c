#include "shell.h"

/**
 * denied_perm - prints error for denied path or permission
 * @data: data structure (args)
 * Return: error;
 */
char *denied_perm(shell_d *data)
{
	char *error, *str;
	int len;

	str = aux_itoa(data->counter);
	len = _strlen(data->av[0]) + _strlen(data->args[0]);
	len += _strlen(str) + 25;
	error = malloc(sizeof(char) * len);
	if (error == NULL)
	{
		free(str);
		return (NULL);
	}
	_strcpy(error, data->av[0]);
	_strcat(error, ": ");
	_strcat(error, str);
	_strcat(error, ": ");
	_strcat(error, data->args[0]);
	_strcat(error, ":Permission denied\n");
	_strcat(error, "\0");
	free(str);
	return (error);
}
/**
 * env_error - prints message for handling env vars
 * @data: data structure (args and counter)
 * Return: error
 */
char *env_error(shell_d *data)
{
	char *error, *msg, *str;
	int len;

	msg = ": unable to add/remove from environment\n";
	str = aux_itoa(data->counter);
	len = _strlen(data->av[0]) + _strlen(data->args[0]);
	len += _strlen(msg) + _strlen(str) + 5;

	error = malloc(sizeof(char) * len);
	if (error == NULL)
	{
		free(str);
		return (NULL);
	}
	_strcpy(error, data->av[0]);
	_strcat(error, ": ");
	_strcat(error, str);
	_strcat(error, ": ");
	_strcat(error, data->args[0]);
	_strcat(error, msg);
	_strcat(error, "\0");
	free(str);

	return (error);
}
