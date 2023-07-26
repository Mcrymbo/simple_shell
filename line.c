#include "shell.h"

/**
 * read_line - reads input string
 * @line: returns value of getline dunction
 * Return: readline
 */
char *read_line(int *line)
{
	char *input = NULL;
	size_t size = 0;

	*line = getline(&input, &size, stdin);
	return (input);
}
