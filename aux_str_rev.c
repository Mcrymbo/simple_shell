#include "shell.h"

/**
 * str_rev - reverses string
 * @str: input string
 * Return: nothing
 */
void str_rev(char *str)
{
	char temp, *s;
	int i, j, count = 0;

	while (count >= 0)
	{
		if (str[count] == '\0')
			break;
		count++;
	}
	s = str;
	for (i = 0; i < (count - 1); i++)
	{
		for (j = i + 1; j > 0; j--)
		{
			temp = s[j];
			s[j] = s[j - 1];
			s[j - 1] = temp;
		}
	}
}
