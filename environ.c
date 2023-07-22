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
