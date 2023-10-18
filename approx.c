#include "shell.h"

/**
 * _getenv - Gets the value of an environment variable
 * @name: name of the environment variable
 *
 * Return: pointer to the value of the environment variable
 */
char *_getenv(const char *name)
{
	int i, j, status;

	for (i = 0; environ[i] != NULL; i++)
	{
		status = 1;
		for (j = 0; environ[i][j] != '='; j++)
		{
			if (name[j] != environ[i][j])
			{
				status = 0;
				break;
			}
		}

		if (status)
		{
			return (&environ[i][j + 1]);
		}
	}
	return (NULL);
}

/**
 *  _getpath - gets the value of the PATH environment variable
 * @path: name of the environment variable
 * @path_cpy: copy of the path variable
 *
 * Return: pointer to the value of the PATH environment variable
 */
list_t *_getpath(char *path, char **path_cpy)
{
	char *token = NULL, *delim = ":\0";
	list_t *head, *path_node;

	if (path == NULL)
		return (NULL);

	*path_cpy = _strdup(path); /* Free on shellLoop() */

	head = NULL;
	path_node = malloc(sizeof(list_t));
	if (path_node == NULL)
		return (NULL);

	token = strtok(*path_cpy, delim);
	path_node->str = token;
	path_node->next = head;
	head = path_node;
	while (token != NULL)
	{
		token = strtok(NULL, delim);
		if (token == NULL) /* Don't save token NULL in list */
			break;
		path_node = malloc(sizeof(list_t));
		if (path_node == NULL)
			return (NULL);
		path_node->str = token;
		path_node->next = head;
		head = path_node;
	}

	return (head);
}

/**
 * list_path - return a linked list of all directories of path
 * @path_cpy: a
 *
 * Return: linked list (list_t)
 */
list_t *list_path(char **path_cpy)
{
	char *path;
	list_t *head = NULL;

	path = _getenv("PATH");
	if (*path == '\0')
		return (NULL);

	head = _getpath(path, path_cpy);
	if (head == NULL)
		return (NULL);

	return (head);
}

/** Task 5*/
