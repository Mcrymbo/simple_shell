#include "shell.h"

/**
 * get_len - gets the length of a number
 * @n: number
 * Return: length;
 */
int get_len(int n)
{
	unsigned int n1;
	int len = 1;

	if (n < 0)
	{
		len++;
		n1 = n * -1;
	}
	else
		n1 = n;
	while (n > 9)
	{
		len++;
		n1 = n1 / 10;
	}
	return (len);
}
/**
 * aux_itoa - converts int to string
 * @n: type int number
 * Return: string
 */
char *aux_itoa(int n)
{
	unsigned int n1;
	int len = get_len(n);
	char *buf;

	buf = malloc(sizeof(char) * (len + 1));
	if (buf == 0)
		return (NULL);
	buf[len] = '\0';
	if (n < 0)
	{
		n1 = n * -1;
		buf[0] = '-';
	}
	else
		n1 = n;
	len--;
	do {
		buf[len] = (n1 % 10) + '0';
		n1 = n1 / 10;
		len--;
	} while (n1 > 0);
	return (buf);
}
/**
 * atoi - converts string to integer
 * @s: string to convert
 * Return: integer
 */
int _atoi(char *s)
{
	unsigned int count = 0, size = 0, oi = 0, pn = 0, m = 1, i;

	while (*(s + count))
	{
		if (size > 0 && (*(s + count) < '0' || *(s + count) > '9'))
			break;
		if (s[count] == '-')
			pn *= -1;
		if (s[count] >= '0' && s[count] <= '9')
		{
			if (size > 0)
				m *= 10;
			size++;
		}
		count++;
	}
	for (i = count - size; i < count; i++)
	{
		oi = oi + (s[i] - 48) * m;
		m /= 10;
	}
	return (oi * pn);
}
