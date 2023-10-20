#include "shell.h"

int status;

/**
 * _setenv - This function sets an environmental variable
 * @name: pointer to the name of the variable
 * @value: value to set the variable to
 *
 * Return: 0 on success
 */
int _setenv(const char *name, const char *value)
{
	char **new_env;
	char *buf;
	char *t_buf;
	char *element_ptr;
	int length;

	if (value == NULL)
	{
		write(STDERR_FILENO, "setenv: no value given\n", 23);
		status = 2;
		return (SKIP_FORK);
	}

	buf = str_concat((char *)name, "=");

	element_ptr = get_array_element(environ, buf);

	t_buf = str_concat(buf, (char *)value);
	free(buf);
	buf = t_buf;

	if (element_ptr == NULL)
	{
		length = list_len(environ, NULL);
		new_env = array_cpy(environ, length + 1);
		new_env[length - 1] = buf;
		new_env[length] = NULL;
		free_array(environ);
		environ = new_env;
		return (SKIP_FORK);
	}

	length = list_len(environ, (char *)name);
	free(environ[length]);
	environ[length] = buf;

	status = 0;

	return (SKIP_FORK);
}

/**
 * _unsetenv - This function removes or deletes an environmental variable
 * @name: pointer to the name of variable
 *
 * Return: 0 if successful
 */
int _unsetenv(const char *name)
{
	char **ptr;
	char *buf;
	int length;

	buf = str_concat((char *)name, "=");
	length = list_len(environ, buf);
	free(buf);

	if (length == -1)
	{
		write(STDERR_FILENO, "unsetenv: variable not found\n", 29);
		status = 2;
		return (SKIP_FORK);
	}

	ptr = environ + length;
	free(*ptr);
	while (*(ptr + 1) != NULL)
	{
		*ptr = *(ptr + 1);
		ptr++;
	}
	*ptr = NULL;
	status = 0;

	return (SKIP_FORK);
}

/**
 * change_dir - this fuction changes the current working directory
 * @name: name of directory to change to
 *
 * Return: 0 if successful
 */
int change_dir(char *name)
{
	char *hom;
	char *pwd;
	char old_path_buf[PATH_MAX];
	char new_path_buf[PATH_MAX];
	size_t buf_size = PATH_MAX;
	int index;

	getcwd(old_path_buf, buf_size);

	if (name == NULL)
	{
		hom = get_array_element(environ, "HOME=");
		if (hom == NULL)
		{
			status = 2;
			message_err("cd", name);
			return (SKIP_FORK);
		}

		hom += 5;

		index = chdir((const char *)hom);
		if (index != -1)
			_setenv("PWD", (const char *)hom);
	}
	else if (str_cmp("-", name, MATCH) == TRUE)
	{
		pwd = get_array_element(environ, "OLDPWD=");
		if (pwd == NULL)
		{
			status = 2;
			message_err("cd", name);
			return (SKIP_FORK);
		}

		pwd += 7;

		index = chdir((const char *)pwd);
		if (index != -1)
		{
			write(STDOUT_FILENO, pwd, _strlen(pwd));
			write(STDOUT_FILENO, "\n", 1);
			_setenv("PWD", (const char *)pwd);
		}
	}
	else if (name != NULL)
	{
		index = chdir((const char *)name);
		if (index != -1)
			_setenv("PWD", getcwd(new_path_buf, buf_size));
	}
	if (index == -1)
	{
		status = 2;
		message_err("cd", name);
		return (SKIP_FORK);
	}

	status = 0;
	_setenv("OLDPWD", (const char *)old_path_buf);

	return (SKIP_FORK);
}

/**
 * alias_func - processes command aliases
 * @args: points an arguments from command line
 * @to_free: dictates if aliases need to be freed
 *
 * Return: TRUE if exiting, FALSE if the command is not "alias" or an alias,
 * SKIP_FORK if success
 */
int alias_func(char **args, int to_free)
{
	static alias head = {NULL, NULL, NULL};
	char *c_ptr;
	int no_err = TRUE;

	if (to_free == TRUE)
		return (free_aliases(head.next));

	if (str_cmp("alias", *args, MATCH) != TRUE)
		return (check_alias(args, head.next));

	args++;

	if (*args == NULL)
		return (print_aliases(head.next));

	while (*args != NULL)
	{
		c_ptr = *args;
		while (*c_ptr != '\0' && *c_ptr != '=')
			c_ptr++;

		if (*c_ptr == '\0' || c_ptr == *args)
		{
			if (print_alias_value(*args, &head) == FALSE)
				no_err = FALSE;
		}
		else
		{
			*c_ptr = '\0';
			c_ptr++;
			set_alias(*args, &head, c_ptr);
			*(c_ptr - 1) = '=';
		}
		args++;
	}

	if (no_err == FALSE)
		return (SKIP_FORK);

	status = 0;
	return (SKIP_FORK);
}

/**
 * print_env - this function prints the environment
 *
 * Return: TRUE
 */
int print_env(void)
{
	char **p = environ;

	while (*p != NULL)
	{
		write(STDOUT_FILENO, *p, _strlen(*p));
		write(STDOUT_FILENO, "\n", 1);
		p++;
	}

	status = 0;

	return (SKIP_FORK);
}
