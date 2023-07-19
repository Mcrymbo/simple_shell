#include "shell.h"

/**
 * comp_env - comparing names of environment variables
 * @name_env: name of environment variable
 * name:  variable passed
 * Return: 0 if names are not similar, another number otherwise
 */
int comp_env(const char *name_env, const char *name)
{
	int len;

	for ( len = 0; name_env[len] != '='; len++)
	{
		if (name_env[len] != name[len])
			return (0);
	}
	return (1 + len);
}

/**
 * _getenv - obtains the name of an environment variable
 * @name_env: evironment variable name
 * @_env: environment variable
 * Return: env variable if found
 */
char *_getenv(const char *name_env, char **_env)
{
	char *env_ptr = NULL;
	int len, val = 0;

	for (len = 0; _env[len]; len++)
	{
		val = comp_env(_env[len], name_env);
		if (val)
		{
			env_ptr = _env[len];
			break;
		}
	}
	return (env_ptr + val);
}
