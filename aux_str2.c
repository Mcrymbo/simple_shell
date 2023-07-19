#include "shell.h"

/**
 * _strdup - dublicates string in the heap memory
 * @str: string to dublicate
 * Return: duplicated string
 */
char *_strdup(const char *s)
{
	char *new;
	size_t len;

	len = _strlen(s);
	new = malloc(sizeof(char *) * (len + 1));
	if (new == NULL)
		return (NULL);
	_memcpy(new, s, len + 1);
	return (new);
}
/**
 * _strlen - returns length of string
 * @str: string
 * Return: length of the string
 */
int _strlen(const char *str)
{
	int len;

	for (len = 0; str[len]; len++)
		;
	return (len);
}
/**
 * cmp_char - compares characters of a string
 * @str: string input
 * @delim: delimiter
 * Return: 1 if eqiual and 0 otherwise
 */
int cmp_char(char *str, const char *delim)
{
	unsigned int i, j, k;

	for (i = 0, k = 0; str[i]; i++)
	{
		for (j = 0; delim[j]; j++)
		{
			if (str[i] == delim[j])
			{
				k++;
				break;
			}
		}
	}
	if (i == k)
		return (1);
	return (0);
}
/**
 * _isdigit - determines if a digit is a number
 * @s: string input
 * Return: 1 if number and 0 otherwise
 */
int _isdigit(const char *s)
{
	unsigned int i;

	for (i = 0; *(s + i); i++)
	{
		if (s[i] < 48 || s[i] > 57)
			return (0);
	}
	return (1);
}
/**
 * _strtok - splits a string into tokens
 * @str: input string
 * @delim: delimiter
 * Return: splitted string
 */
char *_strtok(char *str, const char *delim)
{
	static char *splitted, *str_end;
	char *str_start;
	unsigned int i, bool;

	if (str)
	{
		if (cmp_char(str, delim))
			return (NULL);
		splitted = str;
		i = _strlen(str);
		str_end = &str[i];
	}
	str_start = splitted;
	if (str_start == str_end)
		return (NULL);
	for (bool = 0; *splitted; splitted++)
	{
		if (splitted != str_start)
			if (*splitted && *(splitted - 1) == '\0')
				break;
		/** replacing delimiter for null character**/
		for (i = 0; delim[i]; i++)
		{
			if (*splitted == delim[i])
			{
				*splitted = '\0';
				if (splitted == str_start)
					str_start++;
				break;
			}
		}
		if (bool == 0 && *splitted)
			bool = 1;
	}
	if (bool == 0)
		return (NULL);
	return (str_start);
}
