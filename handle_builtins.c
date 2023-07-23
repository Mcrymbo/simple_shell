#include "shell.h"

/**
 * get_builtin - handle builtins eg. exit, cd, env
 * @command builtin command
 * Return: function pointer to the command
 */
int (*get_builtin(char *command))(shell_d *)
{
	int i;

	builtin_cmd builtin[] = {
		{"exit", sh_exit },
		{"env", _env},
		{"setenv", _setenv},
		{"unsetenv", _unsetenv},
		{ NULL, NULL}
	};

	for (i = 0; builtin[i].name; i++)
	{
		if (_strcmp(builtin[i].name, command) == 0)
			break;
	}
	return (builtin[i].f);
}
