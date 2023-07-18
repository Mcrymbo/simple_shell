#include "shell.h"

/**
 * line_tok - splits line string into tokens
 * @input: input string
 * Return: splitted string
 */
char **line_tok(char *input)
{
	char **tkns;
	char *tkn;
	size_t i, size;

	size = TOK_SIZE;
	tkns = malloc(sizeof(char) * size);
	if (!tokns)
	{
		perror("Erro:");
		exit(EXIT_FAILURE);
	}
	tkn = strtok(input, TOK_DEL);
	tkns[0] = tkn;
	for (i = 1; tkn != NULL; i++)
	{
		if (i == size)
		{
			size += TOK_SIZE;
			tkns = _reallocdp(tkns, i, sizeof(char) * size);
			if (!tkns)
			{
				perror("Error:");
				exit(EXIT_FAILURE);
			}
		}
		tkn = strtok(NULL, TOK_DEL);
		tkns[i] = tkn;
	}
	return (tkns);
}

