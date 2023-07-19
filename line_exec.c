#include "shell.h"

/**
 * line_exec - find builins and command
 * @data: relevant data is args
 * Return: 1 on success
 */
int line_exec(shell_d *data)
{
	int (*builtin)(shell_d *data);

	if (data->args[0] == NULL)
		return (1);
	builtin = get_builtin(data->args[0]);
	if (builtin != NULL)
		return (builtin(data));
	return(cmd_exec(data));
}
