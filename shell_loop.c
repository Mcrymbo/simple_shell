#include "shell.h"

/**
 * shell_loop - loops the shell
 * @datash: data structure
 */
void shell_loop(shell_d *data)
{
	int line, loop = 1;
	char *input;

	while (loop == 1)
	{
		write(STDIN_FILENO, "$ ", 2);
		input = read_line(&line);
		if (line != -1)
		{
			if (input == NULL)
				continue;
			data->input = input;
			loop = split_cmd(data, input);
			data->counter += 1;
			free(input);
		}
		else
		{
			loop = 0;
			free(input);
		}
	}
}
