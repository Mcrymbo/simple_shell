#include "shell.h"

/**
 * cd_dot - changes to current directory
 * @data: data structure (_environ)
 * Return: nothing
 */
void cd_dot(shell_d *data)
{
	char *dir, *pwd_dup, *pwd_tkn;
	char pwd[PATH_MAX];

	getcwd(pwd, sizeof(pwd));
	pwd_dup = _strdup(pwd);
	env_set("OLDPWD", pwd_dup, data);
	dir = data->args[1];
	if (_strcmp(".", dir) == 0)
	{
		env_set("PWD", pwd_dup, data);
		free(pwd_dup);
		return;
	}
	if (_strcmp("/", pwd_dup) == 0)
	{
		free(pwd_dup);
		return;
	}
	pwd_tkn = pwd_dup;
	str_rev(pwd_tkn);
	pwd_tkn = _strtok(pwd_tkn, "/");
	if (pwd_tkn)
	{
		pwd_tkn = _strtok(NULL, "\0");
		if (pwd_tkn)
			str_rev(pwd_tkn);
	}
	if (pwd_tkn)
	{
		chdir(pwd_tkn);
		env_set("PWD", "/", data);
	}
	else
	{
		chdir("/");
		env_set("PWD", "/", data);
	}
	data->status = 0;
	free(pwd_dup);
}

/**
 * cd_dot_dot - changes to parent directory
 * @data: data structure (_environ)
 * Retur: nothing
 */
void cd_dot_dot(shell_d *data)
{
	char *pwd_dup, *oldpwd_dup, *pwd_p, *oldpwd_p;
	char pwd[PATH_MAX];

	getcwd(pwd, sizeof(pwd));
	pwd_dup = _strdup(pwd);
	oldpwd_p = _getenv("OLDPWD", data->_environ);
	if (oldpwd_p == NULL)
		oldpwd_dup = pwd_dup;
	else
		oldpwd_dup = _strdup(oldpwd_p);
	env_set("OLDPWD", pwd_dup, data);
	if (chdir(oldpwd_dup) == -1)
		env_set("PWD", pwd_dup, data);
	else
		env_set("PWD", oldpwd_dup, data);
	pwd_p = _getenv("PWD", data->_environ);

	write(1, pwd_p, _strlen(pwd_p));
	write(1, "\n", 1);

	free(pwd_dup);
	if (oldpwd_p)
		free(oldpwd_dup);
	data->status = 0;
	chdir(pwd_p);
}

/**
 * cd_to - change to specified directory
 * @data: data structure (args)
 * Return: nothing
 */
void cd_to(shell_d *data)
{
	char pwd[PATH_MAX];
	char *dir, *pwd_dup, *dir_dup;

	getcwd(pwd, sizeof(pwd));
	dir = data->args[1];
	if (chdir(dir) == -1)
	{
		handle_error(data, 2);
		return;
	}
	pwd_dup = _strdup(pwd);
	env_set("OLDPWD", pwd_dup, data);
	dir_dup = _strdup(dir);
	env_set("PWD", dir_dup, data);

	free(pwd_dup);
	free(dir_dup);
	data->status = 0;

	chdir(dir);
}

/**
 * cd_home - cd to home directory
 * @data: data structure (_environ)
 * Return: nothing
 */
void cd_home(shell_d *data)
{
	char pwd[PATH_MAX];
	char *pwd_dup, *home;

	getcwd(pwd, sizeof(pwd));
	pwd_dup = _strdup(pwd);
	home = _getenv("HOME", data->_environ);
	if (!home)
	{
		env_set("OLDPWD", pwd_dup, data);
		free(pwd_dup);
		return;
	}
	if (chdir(home) == -1)
	{
		handle_error(data, 1);
		free(pwd_dup);
	}
	env_set("OLDPWD", pwd_dup, data);
	env_set("PWD", home, data);
	free(pwd_dup);
	data->status = 0;
}
