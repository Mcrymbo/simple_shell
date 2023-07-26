#include "shell.h"

/**
 * exit_error - genwrates exit shell error message
 * @data: relevant are av, args and counter
 * Return: Error message
 */
char *exit_error(shell_d *data)
{
	char *error;
	char *cnt;
	int len;

	cnt = aux_itoa(data->counter);
	len = _strlen(data->av[0]) + _strlen(cnt);
	len += _strlen(data->args[0]) + _strlen(data->args[1]) + 23;
	error = malloc(sizeof(char *) * (len + 1));
	if (error == NULL)
	{
		free(cnt);
		return (NULL);
	}
	_strcpy(error, data->av[0]);
	_strcat(error, ": ");
	_strcat(error,  cnt);
	_strcat(error, "; ");
	_strcat(error, data->args[0]);
	_strcat(error, ": Invalid number: ");
	_strcat(error, data->args[0]);
	_strcat(error, "\n\0");
	free(cnt);

	return (error);
}

/**
 * cmd_not_found - generates error message for command not found
 * @data: data structure (args, av, and counter)
 * Return: Error
 */
char *cmd_not_found(shell_d *data)
{
	char *error;
	char *cnt;
	int len;

	cnt = aux_itoa(data->counter);
	len = _strlen(cnt) + _strlen(data->av[0]) + _strlen(data->args[0]) + 17;
	error = malloc(sizeof(char *) * len);
	if (error == NULL)
	{
		free(cnt);
		return (NULL);
	}
	_strcpy(error, data->av[0]);
	_strcat(error, ": ");
	_strcat(error, cnt);
	_strcat(error, ": ");
	_strcat(error, data->args[0]);
	_strcat(error, ": not found\n");
	_strcat(error, "\0");
	free(cnt);
	return (error);
}

/**
 * get_cd_error - geerates error message for illegal cd into non-directory file
 * @data: data structure (av, args, and counter)
 * Return: error
 */
char *get_cd_error(shell_d *data)
{
	char *error;
	char *cnt;
	char *msg;
	int len;
	int len_d;

	if (data->args[1][0] == '-')
	{
		len_d = 2;
		msg = ": Invalid option ";
	}
	else
	{
		len_d = _strlen(data->args[0]);
		msg = ": can't cd to ";
	}
	cnt = aux_itoa(data->counter);
	len = _strlen(data->av[0]) + _strlen(data->args[0]) + 6;
	len += _strlen(msg) + _strlen(cnt) + len_d;
	error = malloc(sizeof(char *) * len);
	if (error == NULL)
	{
		free(cnt);
		return (NULL);
	}
	error = concat_cd_error(data, msg, error, cnt);
	free(cnt);
	return (error);
}

/**
 * concat_cd_error - concatenated error messages for get_cd_error
 * @data: data structure (av,  and args)
 * @msg: message to be printed
 * @error: error message output
 * @cnt: counts of lines
 * Return: (error)
 */
char *concat_cd_error(shell_d *data, char *msg, char *error, char *cnt)
{
	char *flag;

	_strcpy(error, data->av[0]);
	_strcat(error, ": ");
	_strcat(error, cnt);
	_strcat(error, ": ");
	_strcat(error, data->args[0]);
	_strcat(error, msg);
	if (data->args[1][0] == '-')
	{
		flag = malloc(3);
		if (flag == NULL)
			return (NULL);
		flag[0] = '-';
		flag[1] = data->args[1][1];
		flag[2] = '\0';
		_strcat(error, flag);
		free(flag);
	}
	else
		_strcat(error, data->args[1]);
	_strcat(error, "\n");
	_strcat(error, "\0");
	return (error);
}

/**
 * handle_error - call error
 * @data: data structure (args)
 * @val: value of the error
 * Return: error
 */
char handle_error(shell_d *data, int val)
{
	char *error;

	switch (val)
	{
		case 127:
			error = cmd_not_found(data);
			break;
		case 126:
			error = denied_perm(data);
			break;
		case 2:
			if (_strcmp("exit", data->args[0]) == 0)
				error = exit_error(data);
			else if (_strcmp("cd", data->args[0]) == 0)
				error = get_cd_error(data);
			break;
		case -1:
			error = env_error(data);
	}
	if (error != NULL)
	{
		write(2, error, _strlen(error));
		free(error);
	}
	data->status = val;
	return (val);
}
