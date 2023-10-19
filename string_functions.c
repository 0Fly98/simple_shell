#include "shell.h"

/**
 *  _strlen - this function returns the length of a string
 * @str: string to be evaluated
 *
 * Return: the length of the string
 */
int _strlen(char *str)
{
	int index = 0;

	if (str == NULL)
		return (0);

	while (*str != '\0')
	{
		index++;
		str++;
	}

	return (index);
}

/**
 * _strdup - this function duplicate a string and allocates memory space for the copy of a string
 * @src: a pointer to the string copy
 *
 * Return: a pointer to the copy, or NULL if failure
 */
char *_strdup(char *src)
{
	int s_len = _strlen(src);
	char *p;
	char *des = malloc(s_len + 1);

	if (des == NULL)
		exit(EXIT_FAILURE);

	p = des;

	while (*src != '\0')
	{
		*p = *src;
		p++;
		src++;
	}

	*p = '\0';

	return (des);
}

/**
 * str_concat - this function joins two strings
 * @str1: first string
 * @str2: second string
 *
 * Return: a pointer to the new string, or NULL if failure
 */
char *str_concat(char *str1, char *str2)
{
	int length = _strlen(str1) + _strlen(str2);
	char *des = malloc(length + 1);
	char *p = des;

	if (str1 != NULL)
	{
		while (*str1 != '\0')
		{
			*p = *str1;
			p++;
			str1++;
		}
	}

	if (str2 != NULL)
	{
		while (*str2 != '\0')
		{
			*p = *str2;
			p++;
			str2++;
		}
	}

	*p = '\0';

	return (des);
}

/**
 * str_cmp - this function compares two string
 * @str1: first string to be compared
 * @str2: second string to be compared
 * @prfx_or_match: if string needs to be matched exactly or if just a prefix
 * needs to be matched
 *
 * Return: difference between strings
 */
int str_cmp(char *str1, char *str2, int prfx_or_match)
{
	if (str1 == NULL || str2 == NULL)
		return (FALSE);

	while (*str1 != '\0' && *str2 != '\0')
	{
		if (*str1 != *str2)
			return (FALSE);

		str1++;
		str2++;
	}

	if (prfx_or_match == PREFIX)
		return (TRUE);

	if (*str1 == *str2)
		return (TRUE);

	return (FALSE);
}
