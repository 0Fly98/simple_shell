#include "shell.h"

/**
 * shell_exit - Exits the shell
 * @av: arguments passed to the function
 * @ac: number of arguments passed to the function
 * @read: buffer containing the command
 *
 * Return: void
 */
void shell_exit(char ***av, int ac, ssize_t *read)
{
	char *first = NULL;

	if (ac != 2 || *av == NULL)
		return;

	first = (*av)[0];

	if (_strcmp(first, "exit") == 0)
	{
		*read = -1;
		free(*av);
		*av = NULL;
	}
}

/**
 * _env - check if the command is env
 * @av: arguments passed to the function
 * @ac: number of arguments passed to the function
 *
 * Return: void
 */
void _env(char ***av, int ac)
{
	char *first = NULL;
	int i;

	if (ac != 2 || *av == NULL)
		return;

	first = (*av)[0];

	if (_strcmp(first, "env") == 0)
	{
		i = 0;
		while (environ[i])
		{
			_puts(STDOUT_FILENO, environ[i++]);
			_puts(STDOUT_FILENO, "\n");
		}
		free(*av);
		*av = NULL;
	}
}

/**
 * _strcmp - compares two strings
 * @s1: first string
 * @s2: second string
 *
 * Return: int
 */
int _strcmp(char *s1, char *s2)
{
	int i, diff;

	for (i = 0; s1[i] != '\0'; ++i)
	{
		if (s1[i] > s2[i])
		{
			diff = s1[i] - s2[i];
			return (diff);
		}
		else if (s1[i] < s2[i])
		{
			diff = s1[i] - s2[i];
			return (diff);
		}
	}

	return (0);
}

/**This is task 8*/
