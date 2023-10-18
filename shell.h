#ifndef SHELL_H
#define SHELL_H

#include <sys/wait.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>

#define TRUE 1
#define FALSE 0

extern char **environ;

/**
 * struct list_s - singly linked list
 * @str: string - (malloc'ed string)
 * @next: points to the next node
 *
 * Description: singly linked list node structure
 */
typedef struct list_s
{
	char *str;
	struct list_s *next;
} list_t;

/* Main function */
int loop(char **argv);

/*memory*/
int bfree(void **ptr);

/*Delim.c*/
char **strtow(char *str, char *delim);
char **strtow3(char *str, char d);

/* Builtin functions */
void shell_exit(char ***av, int ac, ssize_t *read);
void _env(char ***av, int ac);

/* Parser */
void nl_replace(char **buffer);
ssize_t _readline(char **buffer, char ***tokens);
void process_tokens(char ***tokens, char **buffer, int count_token);
int tokens_len(ssize_t read_len, char **buffer);

/* Executer */
int _exec(char **buffer, char ***av, char *full_path, int *st);
void check_path(char ***tokens, char **path, char **av, int *cnt, int *err);


/* String tools */
int _strlen(const char *s);
char *_strcpy(char *dest, const char *src);
char *_strcat(char *dest, const char *src);
char *_strncat(char *dest, const char *src, size_t n);
char *_strdup(char *str);
int _strcmp(char *s1, char *s2);

/* Print linked list*/
void free_list(list_t *head);
size_t print_list(const list_t *h);

/* Function to get the data in the interactive shell */
int _getchar(void);
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);

/* Get the value of a entorn variable */
char *_getenv(const char *name);
char *_getenv_local(const char *name, char **environ);

/*int _setenv(const char *name, const char *value, int overwrite);*/

/* Get a linked list of a current entorn variable */
list_t *_getpath(char *path, char **path_cpy);

/* Get the path into a linked list */
list_t *list_path(char **path_cpy);

/* Return the path if found an executable */
char *add_path(char ***tokens, list_t *path);

/* Prints */
void pfError(char *av, char *count, char *firstOne, char *message);
void print_err(char *str);
void _puts(int fd, char *str);

/* string-tools-adv */
char *itoa(int value, char *buffer, int base);

/*loop*/

void check_dir(char ***tokens, char **path, char **av, int *count, int *error);
#endif
