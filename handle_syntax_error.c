#include "shell.h"

/**
 * syntax_error_check - checks and print syntax error
 * @data: data structure
 * @input: input string
 * Return: 1 if there is error and 0 otherwise
 */
int syntax_error_check(shell_d *data, char *input)
{
	int a, b, i;

	a = b = i = 0;
	b = f_char(input, &a);
	if (b == -1)
	{
		syntax_error_print(data, input, a, 0);
		return (1);
	}
	i = error_sep(input + a, 0, input[i]);
	if (i != 0)
	{
		syntax_error_print(data, input, a + i, 1);
		return (1);
	}
	return (0);
}

/**
 * error_sep - searches for syntax error
 * @input: input string
 * @i: index of error
 * @lchar: last character read
 * Return: index of error, 0 for no error
 */
int error_sep(char *input, int i, char lchar)
{
	int cnt = 0;

	if (*input == '\0')
		return (0);
	if (*input == ' ' || *input == '\t')
		return (error_sep(input + 1, i + 1, lchar));
	if (*input == ';')
	{
		if (lchar == '&' || lchar == '|' || lchar == ';')
			return (i);
	}
	if (*input == '&')
	{
		if (lchar == '|' || lchar == ';')
			return (i);
		if (lchar == '&')
		{
			cnt = char_repeated(input,0);
			if (cnt == 0 || cnt > 1)
				return (i);
		}
	}
	if (*input == '|')
	{
		if (lchar == '&' || lchar == ';')
			return (i);
		if (lchar == '|')
		{
			cnt = char_repeated(input, 0);
			if (cnt == 0 || cnt > 1)
				return (i);
		}
	}
	return (error_sep(input + 1, i + 1, *input));
}

/**
 * char_repeated - captures number of repetitions in a char
 * @input: input string
 * Return: number of repetitions
 */
int char_repeated(char *input, int i)
{
	if (*(input - 1) == *input)
		return (char_repeated(input - 1, i + 1));
	return (i);
}

/**
 * syntax_error_print - prints syntax error
 * @data: relevant are counter and av
 * @input: input string
 * @i: index
 * @bool: used to control erro msg
 * Return: nothing
 */
void syntax_error_print(shell_d *data, char *input, int i, int bool)
{
	int len;
	char *error, *cnt, *msg1, *msg2;

	if (input[i] == ';')
	{
		if (bool == 0)
			msg1 = (input[i + 1] == ';' ? ";;" : ";");
		else
			msg1 = (input[i - 1] == ';' ? ";;" : ";");
	}
	if (input[i] == '|')
		msg1 = (input[i + 1] == '|' ? "||" : "|");
	if (input[i] == '&')
		msg1 = (input[i + 1] == '&' ? "||" : "&");
	msg2 = ": syntax error near unexpected token \'";
	cnt = aux_itoa(data->counter);
	len = _strlen(msg1) + _strlen(msg2);
	len += _strlen(data->av[0]) + _strlen(cnt) + 3;
	error = malloc(sizeof(char) * len);
	if (error == NULL)
	{
		free(cnt);
		return;
	}
	_strcpy(error, data->av[0]);
	_strcat(error, ": ");
	_strcat(error, msg2);
	_strcat(error, msg1);
	_strcat(error, "\'");
	_strcat(error, "\0");

	write(2, error, len);
	write(2, "\n", 1);
	free(cnt);
	free(error);
}

/**
 * f_char - index of first char
 * @input: input string
 * @i: index of error
 * Return: 1 for error and 0 otherwise
 */
int f_char(char *input, int *i)
{
	for (*i = 0; input[*i]; *i += 1)
	{
		if (input[*i] == ' ' || input[*i] == '\t')
			continue;
		if (input[*i] == '|' || input[*i] == ';' || input[*i] == '&')
			return (-1);
		break;
	}
	return (0);
}
