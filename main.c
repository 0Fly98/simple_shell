#include "shell.h"

/**
 * _ctrlc - handles ctrl-c
 * @sig: n
 */
void _ctrlc(int sig)
{
	write(1, "\n($) ", 5);
	(void)sig;
}

/**
 * main - entry point
 * @argc: number of arguments
 * @argv: arguments
 *
 * Return: 0 on success
 */
int main(int argc, char **argv)
{
	int status = 0;

	(void)argc;
	signal(SIGINT, _ctrlc);
	status = loop(argv);

	return (status);
}
