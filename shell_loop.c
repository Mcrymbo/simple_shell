#include "shell.h"

/**
 * shell_loop - loops the shell
 * @data: data structure
 */
void shell_loop(shell_d *data)
{
	int loop, line;
	char *input;

	loop = 1;
	while (loop == 1)
	{
		if (isatty(0) == 0)
			loop = 1;
		write(STDIN_FILENO, "$ ", 2);
		input = read_line(&line);
		if (line != -1)
		{
			input = comment(input);

			if (syntax_error_check(data, input) == 1)
			{
				free(input), data->status = 2;
				continue;
			}
			if (input == NULL)
				continue;
			input = rep_var(input, data);
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
