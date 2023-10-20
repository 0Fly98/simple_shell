#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>
#include <limits.h>
#include <signal.h>

#define FALSE 0
#define TRUE 1
#define NEITHER 2
#define MATCH 3
#define PREFIX 4
#define EXIT_SHELL 5
#define SKIP_FORK 6
#define DO_EXECVE 7

/**
 * struct Alias - singly linked list
 * @name: name of alias
 * @value: command that alias calls
 * @next: points to next node
 */
typedef struct Alias
{
	char *name;
	char *value;
	struct Alias *next;
} alias;

/*Global variables*/
extern int status;
extern int line_num;
extern char *shell_name;
extern char **environ;

int _atoi(char *st);
char *_itoa(int val); 
void message_err(char *arg0, char *arg1);
int err_check(char *ptr);
char *input_path(char *old_buffer, size_t *o_size);
char *check_vars(char *arg);
int _strlen(char *str);
char *_strdup(char *src);
char *str_concat(char *str1, char *str2);
int str_cmp(char *str1, char *str2, int prfx_or_match);
int set_alias(char *arg, alias *alias_ptr, char *new_value);
int print_alias_value(char *arg, alias *alias_ptr);
int print_aliases(alias *alias_ptr);
int free_aliases(alias *alias_ptr);
int check_alias(char **args, alias *alias_ptr);
int alias_func(char **args, int free);
int _setenv(const char *name, const char *value);
int _unsetenv(const char *name);
int change_dir(char *name);
int print_env(void);
char **make_array(char *str_b, char c_delim, char **ssc);
int list_len(char **list, char *entry);
char **array_cpy(char **old_arr, int new_size);
int free_array(char **args);
char *get_array_element(char **arr, char *name);
int command_manager(char **args);
int built_ins(char **args);
int and_or(char **args, char opr, int comp_last);
char *check_command(char **args);
int execute_command(char **args);
/*int print_alias(char *arg, alias *alias_ptr)*/
int free_array(char **args);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);

int _getline(char **line_ptr, size_t *n, int file);
#endif
