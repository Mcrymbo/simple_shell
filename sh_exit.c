#include "shell.h"

/**
 * sh_exit -  exits from the shell
 * @data: relevant is status
 * Return: 0 on success
 */
int sh_exit(shell_d *data)
{
	int is_dig, len, num;
	unsigned int stat;

	if (data->args[1] != NULL)
	{
		stat = _atoi(data->args[1]);
		is_dig = _isdigit(data->args[1]);
		len = _strlen(data->args[1]);
		num = stat > (unsigned int)INT_MAX;
		if (!is_dig || len > 10 || num)
		{
			data->status = 2;
			return (1);
		}
		data->status = (stat % 256);
	}
	return (0);
}
