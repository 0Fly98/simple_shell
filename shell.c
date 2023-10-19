#include "shell.h"

int status = 0;

int line_num = 1;

char *shell_name = NULL;

/**
 * main - this function executes commands from the user input
 * @ac: number of inputs from main
 * @av: array of inputs from main
 *
 * Return: 0, or another number if desired
 */
int main(__attribute__((unused))int ac, char **av)
{
	int bytes;
	int is_split = FALSE;
	int index;
	size_t buf_size = 1;
	char *buffer = NULL;
	char *ptr;
	char *tmp;
	char **args = NULL;

	shell_name = _strdup(*av);

	environ = array_cpy(environ, list_len(environ, NULL));

	signal(SIGINT, SIG_IGN);

	buffer = malloc(1);
	if (buffer == NULL)
		exit(EXIT_FAILURE);

	while (1)
	{
		if (is_split == FALSE)
		{
			if (isatty(STDIN_FILENO) == 1)
				write(STDOUT_FILENO, "simple_shell$ ", 14);

			bytes = getline(&buffer, &buf_size, stdin);

			if (bytes == -1)
				break;
			if (bytes == 1)
			{
				line_num++;
				continue;
			}
			buffer[bytes - 1] = '\0';
			buffer = input_path(buffer, &buf_size);
			if (buf_size == 0)
			{
				line_num++;
				continue;
			}
			ptr = buffer;
		}
		else
			ptr = tmp;

		tmp = NULL;
		args = make_array(ptr, ' ', &tmp);
		if (tmp != NULL)
			is_split = TRUE;
		else
			is_split = FALSE;

		index = command_manager(args);

		free(args);

		if (is_split == FALSE)
			line_num++;

		if (index == EXIT_SHELL)
			break;
	}
	free(buffer);
	alias_func(NULL, TRUE);
	free_array(environ);
	free(shell_name);

	return (status % 256);
}
