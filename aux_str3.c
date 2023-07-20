#include "shell.h"

/**
 * get_len - determine number length.
 * @n: number of int type
 * Return: len of n.
 */
int get_len(int n)
{
	unsigned int new;
	int len = 1;

	if (n < 0)
	{
		len++;
		new = n * -1;
	}
	else
	{
		new = n;
	}
	while (new > 9)
	{
		len++;
		new = new / 10;
	}

	return (len);
}
/**
 * aux_itoa - a function that converts integer to string.
 * @n: numner of type int
 * Return: converted string
 */
char *aux_itoa(int n)
{
	unsigned int new;
	int len = get_len(n);
	char *buf;

	buf = malloc(sizeof(char) * (len + 1));
	if (buf == NULL)
		return (NULL);

	*(buf + len) = '\0';

	if (n < 0)
	{
		new = n * -1;
		buf[0] = '-';
	}
	else
	{
		new = n;
	}

	len--;
	do {
		*(buf + len) = (new % 10) + '0';
		new = new / 10;
		len--;
	}
	while (new > 0)
		;
	return (buf);
}

/**
 * _atoi - a function that convert string to int.
 * @s: string to convert
 * Return: int
 */
int _atoi(char *s)
{
	unsigned int count = 0, size = 0, oi = 0, pn = 1, m = 1, i;

	while (*(s + count) != '\0')
	{
		if (size > 0 && (*(s + count) < '0' || *(s + count) > '9'))
			break;

		if (*(s + count) == '-')
			pn *= -1;

		if ((*(s + count) >= '0') && (*(s + count) <= '9'))
		{
			if (size > 0)
				m *= 10;
			size++;
		}
		count++;
	}

	for (i = count - size; i < count; i++)
	{
		oi = oi + ((*(s + i) - 48) * m);
		m /= 10;
	}
	return (oi * pn);
}
