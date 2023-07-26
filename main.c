#include "shell.h"

/**
 * set_data - initializes the data required for shell data
 * @data: data structure
 * @av: argument vector
 * Return: no return
 */
void set_data(shell_d *data, char **av)
{
	unsigned int i;

	data->av = av;
	data->input = NULL;
	data->args = NULL;
	data->status = 0;
	data->counter = 1;

	for (i = 0; environ[i]; i++)
		;
	data->_environ = malloc(sizeof(char *) * (i + 1));
	for (i = 0; environ[i]; i++)
		data->_environ[i] = _strdup(environ[i]);
	data->_environ[i] = NULL;
	data->pid = aux_itoa(getpid());
}
/**
 * free_d - frees data structure
 * @data: data structure
 * Return: no return
 */
void free_d(shell_d *data)
{
	size_t i;

	for (i = 0; data->_environ[i]; i++)
		free(data->_environ[i]);
	free(data->_environ);
	free(data->pid);
}

/**
 * main - implements the shell
 * @ac: argument count
 * @av: argument vector
 * Return: 0 always
 */
int main(int ac, char **av)
{
	shell_d data;
	(void)ac;

	signal(SIGINT, get_sigint);
	set_data(&data, av);
	shell_loop(&data);
	free_d(&data);
	if (data.status < 0)
		return (255);
	return (data.status);
}
