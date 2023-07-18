#include "shell.h"

/**
 * get_sigint - handles ctrl + c call in prompt
 * @sig: signal handler
 * Return: no return
 */
void get_sigint(int sig)
{
	(void)sig;

	write(STDOUT_FILENO, "\n$ ", 3);
}
