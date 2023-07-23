#include "shell.h"

/**
 * _cd - changes directory
 * @data: data structure
 * Return: 1 if success
 */
int _cd(shell_d *data)
{
	char *dir;
	int home, tilder, dash;

	dir = data->args[1];
	if (dir)
	{
		home = _strcmp("$HOME", dir);
		tilder = _strcmp("~", dir);
		dash = _strcmp("--", dir);
	}
	if (dir == NULL || !home || !tilder || !dash)
	{
		cd_home(data);
		return (1);
	}
	if (_strcmp("-", dir) == 0)
	{
		cd_dot_dot(data);
		return (1);
	}
	if (_strcmp(".", dir) == 0 || _strcmp("..", dir) == 0)
	{
		cd_dot(data);
		return (1);
	}
	cd_to(data);
	return (1);
}

