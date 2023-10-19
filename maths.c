#include "shell.h"

/**
 * _atoi - converts a string to an integer
 * @st: string pointer to be converted
 *
 * Return: The number
 */
int _atoi(char *st)
{
	int num = 0;
	int str_int;
	int sign = 1;

	if (*st == '=' && *(st + 1) >= '0' && *(st + 1) <= '9')
	{
		sign = -1;
		st++;
	}

	while (*st != '\0')
	{
		if (*st >= '0' && *st <= '9')
		{
			str_int = *st - 48;
			if (sign == 1)
				num = (num * 10) + str_int;
			else
				num = (num * 10) - str_int;
		}
		else
			return (-1);
		st++;
	}

	return (num);
}

/**
 * _itoa - this function converts an integer to a string
 * @val: integer to be converted
 *
 * Return: the converted number
 */
char *_itoa(int val)
{
	char *buffer = malloc(12);
	char *ptr = buffer;
	int num = 0;
	int imask = 1000000000;
	int min = FALSE;

	if (val == INT_MIN)
	{
		*ptr = '-';
		ptr++;
		val = INT_MAX;
		min = TRUE;
	}

	if (val < 0)
	{
		*ptr = '-';
		ptr++;
		val = -val;
	}

	while (imask > 9 && num == 0)
	{
		num = val / imask;
		val %= imask;
	}

	if (num != 0)
	{
		*ptr = num + '0';
		ptr++;
	}

	while (imask > 9)
	{
		num = val / imask;
		*ptr = num + '0';
		ptr++;
		val %= imask;
		imask /= 10;
	}

	if (min == TRUE)
		val += 1;

	*ptr = val + '0';
	ptr++;
	*ptr = '\0';
	return (buffer);
}
