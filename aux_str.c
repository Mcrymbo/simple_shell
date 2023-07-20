#include "shell.h"

/**
 * _strcat - concatenates two strings
 * @dest: destination string
 * @src: source string
 * Return: dest
 */
char *_strcat(char *dest, const char *src)
{
	int i, j;

	for (i = 0; dest[i] != '\0'; i++)
		;
	for (j = 0; src[j] != '\0'; j++)
	{
		dest[i] = src[j];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
/**
 * _strcpy - copies string pointed by sorce
 * @dest: destination string
 * @src: source string
 * Return: dest
 */
char *_strcpy(char *dest, char *src)
{
	size_t i;

	for (i = 0; src[i] != '\0'; i++)
		dest[i] = src[i];
	dest[i] = '\0';
	return (dest);
}
/**
 * _strcmp - compares two strings
 * @s1: first string
 * @s2: second string
 * Return: 0 is similar and 1 otherwise
 */
int _strcmp(char *s1, char *s2)
{
	unsigned int i;

	for (i = 0; s1[i] == s2[i] && s1[i]; i++)
		;
	if (s1[i] > s2[i])
		return (1);
	if (s1[i] < s2[i])
		return (-1);
	return (0);
}
/**
 * _strchr - locates a character in string
 * @s: string
 * @c: character
 * Return: pointer to the first occurence of the character
 */
char *_strchr(char *s, char c)
{
	unsigned int i = 0;

	for (; *(s + i) != '\0'; i++)
	{
		if(s[i] == c)
			return (s + i);
	}
	if (s[i] == c)
		return (s + i);
	return ('\0');
}
/**
 * _strspn - calculated the length of a prefix substring
 * @s: segment
 * @accept: accepted bytes
 * Return: number of accepted bytes
 */
int _strspn(char *s, char *accept)
{
	int i, j, bool;

	for (i = 0; s[i]; i++)
	{
		bool = 1;
		for (j = 0; accept[j]; j++)
		{
			if (s[i] == accept[j])
			{
				bool = 0;
				break;
			}
		}
		if (bool == 1)
			break;
	}
	return (i);
}
