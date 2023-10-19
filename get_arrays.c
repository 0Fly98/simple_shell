#include "shell.h"

/**
 * get_array_element - this funtion gets an element of an array
 * @arr: pointer to an array to be searched
 * @name: name of element to be found
 *
 * Return: the array element, or NULL if it is not found
 */
char *get_array_element(char **arr, char *name)
{
	while (*arr != NULL)
	{
		if (str_cmp(*arr, name, PREFIX) == TRUE)
			return (*arr);

		arr++;
	}

	return (NULL);
}

/**
 * make_array - makes a list from a buffer
 * @str_b: the buffer string
 * @c_delim: character delimeter to mark the end of a list entry
 * @ssc: if the string has semicolons, if_sep becomes the location after the
 * semicolon
 *
 * Return: a pointer to the list
 */
char **make_array(char *str_b, char c_delim, char **ssc)
{
	char *str_p = str_b;
	unsigned int index = 2;
	char **arr = NULL;

	while (*str_p != '\0')
	{
		if (*str_p == ';')
			break;
		if (*str_p == c_delim && *(str_p + 1) != '\0')
			index++;

		str_p++;
	}

	arr = malloc(index * sizeof(char **));
	if (arr == NULL)
		exit(EXIT_FAILURE);

	arr[0] = str_b;
	str_p = str_b;
	index = 1;

	while (*str_p != '\0')
	{
		if (*str_p == c_delim)
		{
			*str_p = '\0';
			str_p++;
			if (*str_p == ';')
			{
				arr[index] = NULL;
				if (*(str_p + 1) != '\0' && *(str_p + 2) != '\0')
					*ssc = str_p + 2;
				break;
			}
			if (*str_p != '\0')
			{
				arr[index] = str_p;
				index++;
			}
		}
		str_p++;
	}
	arr[index] = NULL;

	return (arr);
}

/**
 * list_len - this function finds the length of a list, or the index of an entry
 * @list: list to be evaluated
 * @entry: entry to be indexed
 *
 * Return: length or index if success, -1 if failure
 */
int list_len(char **list, char *entry)
{
	int index = 0;

	if (entry == NULL)
	{
		while (*list != NULL)
		{
			index++;
			list++;
		}
		index++;
		return (index);
	}
	else
	{
		while (*list != NULL)
		{
			if (str_cmp(*list, entry, PREFIX) == TRUE)
				return (index);

			index++;
			list++;
		}
	}

	return (-1);
}

/**
 * array_cpy - this function copies an array
 * @old_arr: pointer to array that will be copied
 * @new_size: size of new array
 *
 * Return: the new array
 */
char **array_cpy(char **old_arr, int new_size)
{
	char **new_arr = NULL;
	char **ptr_arr;

	new_arr = malloc(sizeof(char **) * new_size);

	ptr_arr = new_arr;
	while (*old_arr != NULL)
	{
		*ptr_arr = _strdup(*old_arr);
		ptr_arr++;
		old_arr++;
	}
	*ptr_arr = NULL;

	return (new_arr);
}

/**
 * free_array - this function frees two dimensional array
 * @args: array to be freed
 *
 * Return: TRUE
 */
int free_array(char **args)
{
	char **p = args;

	while (*p != NULL)
	{
		free(*p);
		p++;
	}

	free(args);

	return (TRUE);
}
