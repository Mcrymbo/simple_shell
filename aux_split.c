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
	if (!tkns)
	{
		perror("Erro:");
		exit(EXIT_FAILURE);
	}
	tkn = _strtok(input, TOK_DEL);
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
		tkn = _strtok(NULL, TOK_DEL);
		tkns[i] = tkn;
	}
	return (tkns);
}

/**
 * split_cmd - splits commands
 * @data: data structure
 * @input: command
 * Return: 0 to exit and 1 otherwise
 */
int split_cmd(shell_d *data, char *input)
{
	int loop;
	sep_list *h_s, *lst_s;
	line_list *h_l, *lst_l;

	h_s = NULL;
	h_l = NULL;
	add_node(&h_s, &h_l, input);
	lst_l = h_l;
	lst_s = h_s;

	while (lst_l != NULL)
	{
		data->input = lst_l->line;
		data-> args= line_tok(data->input);
		loop = line_exec(data);
		free(data->args);

		if (loop == 0)
			break;
		go_next(&lst_s, &lst_l, data);
		if (lst_l != NULL)
			lst_l = lst_l->next;
	}
	free_seplist(&h_s);
	free_linelist(&h_l);
	if (loop == 0)
		return (0);
	return (1);
}

/**
 * add_node - add commands in list
 * @h_sep: head of sep_list
 * @h_line: head of line_list
 * @input: input string
 * Return: no return
 */
void add_node(sep_list **h_sep, line_list **h_line, char *input)
{
	char *in;
	int i;

	input = swap_char(input, 0);
	for (i = 0; input[i]; i++)
	{
		if (input[i] == ';')
			add_node_end_sep(h_sep, input[i]);
		if (input[i] == '|' || input[i] == '&')
		{
			add_node_end_sep(h_sep, input[i]);
			i++;
		}
	}
	in = _strtok(input, ";|&");
	do {
		in = swap_char(in, 1);
		add_node_end_line(h_line, in);
		in = _strtok(NULL, ";|&");
	} while (in != NULL);
}

/**
 * go_next - searches for the next command stored
 * @lst_s: list separator
 * @lst_l: command separator
 * @data: shell_d data structure
 * Return: nothing
 */
void go_next(sep_list **lst_s, line_list **lst_l, shell_d *data)
{
	sep_list *ls_s;
	line_list *ls_l;
	int loop = 1;

	ls_s = *lst_s;
	ls_l = *lst_l;
	while (ls_s != NULL && loop)
	{
		if (data->status == 0)
		{
			if (ls_s->sep ==';' || ls_s->sep == '&')
				loop = 0;
			if (ls_s->sep == '|')
			{
				ls_l = ls_l->next;
				ls_s = ls_s->next;
			}
		}
		else
		{
			if (ls_s->sep == ';' || ls_s->sep == '|')
				loop = 0;
			if (ls_s->sep == '&')
			{
				ls_s = ls_s->next;
				ls_l = ls_l->next;
			}
		}
		if (ls_s && !loop)
			ls_s = ls_s->next;
	}
	*lst_s = ls_s;
	*lst_l = ls_l;
}

/**
 * swap_char - swaps & and |
 * @input: input string
 * @bool: true or false
 * Return: swapped input
 */
char *swap_char(char *input, int bool)
{
	int i;

	if (bool == 0)
	{
		for (i = 0; input[i] == '&'; i++)
		{
			if (input[i] == '&')
			{
				if (input[i + 1] != '&')
					input[i] = 12;
				else
					i++;
			}
			if (input[i] == '|')
			{
				if (input[i + 1] != '|')
					input[i] = 16;
				else
					i++;
			}
		}
	}
	else
	{
		for (i = 0; input[i]; i++)
		{
			input[i] = (input[i] == 16 ? '|' : input[i]);
			input[i] = (input[i] == 12 ? '&' : input[i]);
		}
	}
	return (input);
}
