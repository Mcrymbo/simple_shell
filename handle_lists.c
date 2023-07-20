#include "shell.h"

/**
 * add_node_end_sep - add nodes and end of seplist
 * @h: head node
 * @s; separator
 * Return: addree of head node
 */
sep_list *add_node_end_sep(sep_list **h, char s)
{
	sep_list *new, *temp;

	new = malloc(sizeof(sep_list));
	if (new == NULL)
		return (NULL);
	new->sep = s;
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
 * free_seplist - free a sep list
 * @h: head node
 */
void free_seplist(sep_list **h)
{
	sep_list *temp, *cur;

	if (h)
	{
		cur = *h;
		while ((temp = cur) != NULL)
		{
			cur = cur->next;
			free(temp);
		}
		*h = NULL;
	}
}

/**
 * add_node_end_line - add command at end of line list
 * @h: head node
 * @input: input string
 * Return: pointer to head
 */
line_list *add_node_end_line(line_list **h, char *input)
{
	line_list *new, *temp;

	new = malloc(sizeof(line_list));
	if (new == NULL)
		return (NULL);
	new->line = input;
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
 * free_linelist - frees line list
 * @h: head node
 * Return: no return
 */
void free_linelist(line_list **h)
{
	line_list *cur, *temp;

	if (h != NULL)
	{
		cur = *h;
		while ((temp = cur) != NULL)
		{
			cur = cur->next;
			free(temp);
		}
		*h = NULL;
	}
}




