#include "shell.h"

/**
 * env_check - checks if a typed command ia an env variable
 * @h: first node of linked list
 * @input: input string
 * @data: required is _environment
 */
void env_check(var_r **h, char *input, shell_d *data)
{
	char **_envr;
	int j, chr, i, val;

	_envr = data->_environ;
	for (i = 0;_envr[i]; i++)
	{
		for (j = 1, i = 0; _envr[i][chr]; chr++)
		{
			if (_envr[i][chr] == '=')
			{
				val = _strlen(_envr[i] + chr + 1);
				add_var_node(h, j, _envr[i] + chr + 1, val);
				return;
			}
			if (input[j] == _envr[i][chr])
				j++;
			else
				break;
		}
	}
	for (j = 0; input[j]; j++)
	{
		if (input[j] == ' ' || input[j] == ';' || input[j] == '\n' || input[j] == '\t')
			break;
	}
	add_var_node(h, j, NULL, 0);
}

/**
 * rep_var - calls functions to replace string in variables
 * @input: input string
 * @data: data structure
 *
 * Return: string replaced
 */
char *rep_var(char *input, shell_d *data)
{
	var_r *head, *index;
	int nlen, olen;
	char *status, *new_input;

	status = aux_itoa(data->status);
	head = NULL;
	olen = check_vars(&head, input, status, data);
	if (head == NULL)
	{
		free(status);
		return (input);
	}
	index = head;
	nlen = 0;
	while (index != NULL)
	{
		nlen += (index->len_val - index->len_var);
		index = index->next;
	}
	nlen += olen;
	new_input = malloc(sizeof(char) * (nlen + 1));
	new_input[nlen] = '\0';
	new_input = replaced_input(&head, input, new_input, nlen);
	free(status), free(input);
	free_varlist(&head);
	return (new_input);
}
/**
 * replaced_input - used to replace string in variable
 * @h: fhead of li nked list
 * @input: input string
 * @new_input: replaced input
 * nlen: replaced length
 * Return: new_input
 */
char *replaced_input(var_r **h, char *input, char *new_input, int nlen)
{
	var_r *index;
	int i, j, k;

	index = *h;
	for (i = j = 0; i < nlen; i++)
	{
		if (input[j] == '$')
		{
			if (!index->len_var && !index->len_val)
			{
				new_input[i] = input[j];
				j++;
			}
			else if (index->len_var && !(index->len_val))
			{
				for (k = 0; k < index->len_var; k++)
					j++;
				i--;
			}
			else
			{
				for (k =0; k < index->len_val; k++)
				{
					new_input[i] = index->val[k];
					i++;
				}
				j += index->len_var;
				i--;
			}
			index = index->next;
		}
		else
		{
			new_input[i] = input[j];
			j++;
		}
	}
	return (new_input);
}

/**
 * check_vars - checking if var is $ or $$
 * @h: head of linked list
 * @input: input string
 * @status: last shell status
 * @data: shell_d
 * Return: 1 if successfull
 */
int check_vars(var_r **h, char *input, char *status, shell_d *data)
{
	int lstat, lpid, i;

	lstat = _strlen(status);
	lpid = _strlen(data->pid);
	for (i = 0; input[i]; i++)
	{
		if (input[i] == '$')
		{
			if (input[i + 1] == '$')
				add_var_node(h, 2, data->pid, lpid), i++;
			else if (input[i + 1] == '?')
				add_var_node(h, 2,status, lstat), i++;
			else if (input[i + 1] == '\0')
				add_var_node(h, 0, NULL, 0);
			else if (input[i + 1] == '\n')
				add_var_node(h, 0, NULL, 0);
			else if (input[i + 1] == ' ')
				add_var_node(h, 0, NULL, 0);
			else if (input[i + 1] == ';')
				add_var_node(h, 0, NULL, 0);
			else if (input[i + 1] == '\t')
				add_var_node(h, 0, NULL, 0);
			else
				env_check(h, input + 1, data);
		}
	}
	return (i);
}
