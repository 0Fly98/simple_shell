#include "shell.h"

int status;

char *shell_name;

/**
 * command_manager - this file handles user input and  manages the process through commands that get executed
 * @args: command and arguments
 *
 * Return: TRUE if success, FALSE if failure
 */
int command_manager(char **args)
{
	char **args_p = args;
	char prev_op = 'c';
	char next_op = 'c';
	int p_eval = NEITHER;
	int no_error = TRUE;
	int w;

	while (*args != NULL && p_eval != EXIT_SHELL)
	{
		while (*args_p != NULL && **args_p != '&'
		       && **args_p != '|')
			args_p++;

		if (str_cmp(*args_p, "||", MATCH) == TRUE)
		{
			*args_p = NULL;
			args_p++;
			next_op = '|';
		}
		if (str_cmp(*args_p, "&&", MATCH) == TRUE)
		{
			*args_p = NULL;
			args_p++;
			next_op = '&';
		}
		if (next_op == 'c')
			break;

		p_eval = and_or(args, prev_op, p_eval);
		if (p_eval == FALSE)
			no_error = FALSE;
		prev_op = next_op;
		args = args_p;
	}

	if (next_op == 'c')
	{
		w = execute_command(args);

		if (w == EXIT_SHELL)
			return (EXIT_SHELL);
	}

	if (no_error == FALSE || w == FALSE)
		return (FALSE);

	return (TRUE);
}

/**
 * built_ins - this function checks if a command is a built in before execution
 * @args: command and arguments
 *
 * Return: SKIP_FORK if built in, DO_EXECVE if not a built in, EXIT_SHELL if
 * exit shell, EXIT_SHELL_CODE if exiting with a particular code
 */
int built_ins(char **args)
{
	char **ptr = args;
	int index;

	while (*ptr != NULL)
	{
		if (**ptr == '#')
		{
			*ptr = NULL;
			break;
		}
		if (str_cmp("~", *ptr, MATCH) == TRUE
		    && get_array_element(environ, "HOME=") != NULL)
		{
			*ptr = _strdup(get_array_element(environ, "HOME=") + 5);
			continue;
		}
		if (str_cmp("~/", *ptr, PREFIX) == TRUE && get_array_element(environ, "HOME=") != NULL)
		{
			*ptr = str_concat(get_array_element(environ, "HOME=") + 5, *ptr + 1);
		}
		*ptr = check_vars(*ptr);

		ptr++;
	}
	if (*args == NULL)
		return (SKIP_FORK);

	index = alias_func(args, FALSE);
	if (index == DO_EXECVE || index == SKIP_FORK)
		return (index);

	if (str_cmp("exit", *args, MATCH) == TRUE && args[1] != NULL)
	{
		status = _atoi(args[1]);
		if (status < 0)
		{
			status = 2;
			message_err(args[0], args[1]);
			return (SKIP_FORK);
		}
	}
	if (str_cmp("exit", *args, MATCH) == TRUE)
		return (EXIT_SHELL);
	else if (str_cmp("setenv", *args, MATCH) == TRUE && args[1] != NULL)
		return (_setenv(args[1], args[2]));
	else if (str_cmp("unsetenv", *args, MATCH) == TRUE
		 && args[1] != NULL)
		return (_unsetenv(args[1]));
	else if (str_cmp("cd", *args, MATCH) == TRUE)
		return (change_dir(args[1]));
	else if (str_cmp("env", *args, MATCH) == TRUE)
		return (print_env());

	return (DO_EXECVE);
}

/**
 * and_or - this function handles command line logical operators
 * @args: command and arguments
 * @opr: first char of logical operator
 * @comp_last: checks if last command in logic is true or false
 *
 * Return: if this command evaluates to true or false
 */
int and_or(char **args, char opr, int comp_last)
{
	int index;

	if (comp_last == NEITHER)
	{
		index = execute_command(args);
		if (index == EXIT_SHELL)
			return (EXIT_SHELL);
		if (index == TRUE)
			return (TRUE);

		return (FALSE);
	}
	if (comp_last == TRUE && opr == '&')
	{
		index = execute_command(args);
		if (index == EXIT_SHELL)
			return (EXIT_SHELL);
		if (index == TRUE)
			return (TRUE);

		return (FALSE);
	}

	if (comp_last == FALSE && opr == '|')
	{
		index = execute_command(args);
		if (index == EXIT_SHELL)
			return (EXIT_SHELL);
		if (index == TRUE)
			return (TRUE);

		return (FALSE);
	}

	if (comp_last == TRUE && opr == '|')
		return (TRUE);

	return (FALSE);
}

/**
 * check_command - this function checks if a non-built-in exists
 * @args: argument and commands
 *
 * Return: TRUE if valid command, FALSE if not
 */
char *check_command(char **args)
{
	char *cmd_buf;
	char *f_buf;
	char *str = NULL;
	char *ptr;
	char *tmp;
	char **var = NULL;
	char **var_ptr;

	if (access(*args, X_OK) == 0)
		return (_strdup(*args));

	if (get_array_element(environ, "PATH=") != NULL)
		str = _strdup(get_array_element(environ, "PATH=") + 5);

	ptr = str;

	if (str != NULL)
	{
		if (*str == ':')
		{
			cmd_buf = str_concat("./", *args);
			if (access(cmd_buf, X_OK) == 0)
			{
				free(str);
				return (cmd_buf);
			}
			else
			{
				free(cmd_buf);
				ptr = _strdup(str + 1);
				free(str);
				str = ptr;
			}
		}
		while (*ptr != '\0')
		{
			if (*ptr == ':' && *(ptr + 1) == ':')
			{
				*(ptr + 1) = '\0';
				tmp = (str_concat(str, ".:"));
				ptr = str_concat(tmp, ptr + 2);
				free(str);
				free(tmp);
				str = ptr;
			}
			ptr++;
		}
	}
	if (str != NULL)
		var = make_array(str, ':', NULL);

	var_ptr = var;

	cmd_buf = str_concat("/", *args);

	f_buf = _strdup(cmd_buf);

	if (var != NULL)
	{
		while (*var_ptr != NULL && access(f_buf, X_OK) != 0)
		{
			free(f_buf);
			f_buf = str_concat(*var_ptr, cmd_buf);
			var_ptr++;
		}
	}

	free(cmd_buf);
	free(str);
	free(var);

	if (access(f_buf, X_OK) != 0)
	{
		message_err(args[0], NULL);
		free(f_buf);
		return (NULL);
	}

	return (f_buf);
}

/**
 * execute_command - this function executes a command
 * @args: pointer to command and arguments
 *
 * Return: TRUE or EXIT_SHELL
 */
int execute_command(char **args)
{
	char *ptr = *args;
	char *cmd_name;
	pid_t pid;
	int w = built_ins(args);

	if (w == DO_EXECVE)
	{
		cmd_name = check_command(args);
		if (cmd_name == NULL)
			return (FALSE);

		pid = fork();
		if (pid == -1)
		{
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
		{
			execve(cmd_name, args, environ);
			exit(EXIT_FAILURE);
		}
		wait(&status);
		free(cmd_name);
		fflush(stdin);
		if (status != 0)
		status = 2;
	}

	if (str_cmp("false", *args, MATCH) == TRUE)
		status = 1;

	if (*args != ptr)
		free(*args);
	args++;

	while (*args != NULL)
	{
		while (*ptr != '\0')
		{
			ptr++;
		}
		ptr++;

		if (*args != ptr)
			free(*args);

		args++;
	}

	if (w == EXIT_SHELL)
		return (EXIT_SHELL);

	if (status != 0)
		return (FALSE);

	return (TRUE);
}
