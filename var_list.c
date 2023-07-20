#include "shell.h"

/**
 * add_var_node - adds a node at end of var_r list
 * @h: head node
 * @len_var: length of variable
 * @val: variable value
 * @len_val: length of value
 * Return: address of head node
 */
var_r *add_var_node(var_r **h, int len_var, char *val, int len_val)
{
	var_r *temp, *new;

	new = malloc(sizeof(var_r));
	if (new == NULL)
		return (NULL);
	new->len_var = len_var;
	new->val = val;
	new->len_val = len_val;
	new->next = NULL;
	temp = *h;
	if (temp == NULL)
		*h = new;
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}
	return (*h);
}

/**
 * free_varlist - frees var_r
 * @h: head node
 * Return: no return
 */
void free_varlist(var_r **h)
{
	var_r *cur, *temp;

	if (h)
	{
		cur = *h;
		while((temp = cur) != NULL)
		{
			cur = cur->next;
			free(temp);
		}
		*h = NULL;
	}
}

