#include "shell.h"

/**
 * loop - main loop of the shell
 * @argv: pointer to array of arguments
 *
 * Return: error status
 */
int loop(char **argv)
{
	ssize_t read = 1;
	char **tokens = NULL, *buffer = NULL, *full_path = NULL, *path_cpy = NULL;
	char *prompt = "($) ";
	list_t *path = NULL;
	int status = 1, error = 0, count = 1;

	path = list_path(&path_cpy);
	isatty(STDIN_FILENO) == 0 ? status = 0 : status;
	while (TRUE)
	{
		status == 1 ? write(1, prompt, 5) : status; /* Print the promt */
		fflush(stdout);
		read = _readline(&buffer, &tokens);
		if (read == EOF) /* Check if it's EOF */
			break;
		error = 0;
		full_path = add_path(&tokens, path);
		check_path(&tokens, &full_path, argv, &count, &error);
		check_dir(&tokens, &full_path, argv, &count, &error);
		_exec(&buffer, &tokens, full_path, &error);
		count++;
	}
	free_list(path); /* This is a linked list with all the paths */
	free(path_cpy);	 /* This is on _getpathdir() environ.c */
	free(buffer);	 /* This is the main buffer */
	return (error);
}
