#ifndef MAIN_H
#define MAIN_H

#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>

/* Initialization of local data structure */
/**
 * struct local - Data Structure
 * @ac: main function argc
 * @av: main function argv
 * @environ: main function environ
 * @pc: prompt count
 * @argv: array of command line arguments
 * @error_checker: indicates which error to print
 * @fd: file discriptor
 * @alias: array of alias commands
 * @prompt: prompt
 * @active: interactive and non-interactive mode checker
 * @exit_status: exit status of previous command
 * @signal: signal
 */
typedef struct local
{
	int ac;
	char **av;
	char **environ;
	int pc;
	char **argv;
	char **alias;
	int error_checker;
	int fd;
	char *prompt;
	int active;
	int exit_status;
	int signal;
} local_t;
local_t *local_init(int ac, char **av, char **envp);
void int_handler(int sig);

/* environ Functions */
/* Functions related to handling the environment variables */
char *_getenv(const char *name, char *const *environ);
int _setenv(local_t **local);
int _unsetenv(local_t **local);
int cd_env(local_t **local, char *const oldpwd);
char **get_path(char *const *environ);

/* Built-in Functions */
/* Functions related to handling built-in commands */
int handle_builtin(local_t **local, char **prog, char **av);
int handle_exit(local_t **local, char **prog, char **av, int exit_status);
int handle_env(local_t **local);
int handle_setenv(local_t **local);
int handle_unsetenv(local_t **local);
int handle_cd(local_t **local);
int handle_alias(local_t **local, int const exit);
char *_getalias(const char *name, char *const *alias);
/* int set_alias(char **argv, int argc, char ***alias, int *ac); */
/* int set_alias(char **argv, char ***alias, int *ac); */
/* void set_alias(char **alias, char **argv, int argc, int ec, int *ac); */
int set_alias(char ***alias, char **argv, int argc, int ec);
int print_alias(char **alias, char **argv, int argc);
int check_alias(char ***alias, char **argv);

/* Error Functions */
/* Functions related to handling errors */
int error(local_t **local);
void print_error_init(local_t **local);
void handle_builtin_errors(local_t **local);

/* Utility Funtions */
/* helper functions to write neat code */
size_t _strlen(char *const str);
int get_mem(char **ptr, size_t const size);
char *itoa(int const number);

/* Prompt Functions */
/* Functions related to getting command */
int handle_prompt(local_t **local);
ssize_t _getline(char **line, size_t *n, int const fd);
char *get_cmd(local_t **local, int exit_status);
int handle_cmd_error(local_t **local, char *const *cmd, int *exit_status);

/* argv Functions */
/* Functions related to getting argv from command */
char **get_argv(char *const str, char *const delim, int damn);
int handle_argv(char *const str, char *const delim, char ***argv, int *ac,
		int *avc, int *acm, int *n, int damn);
int free_argv(char **argv);
int handle_operator(local_t **local, char **prog, int pc, int *exit_status);
int handle_cls(local_t **local, char **av, int ac, int argc,
	       char **prog, int *exit_status);
int handle_comment(char *const str, char ***argv, int *ac, int *avc, int *sc);
void handle_special(char *const str, int *sc);
int handle_delim(char *const str, char *const delim, char ***argv, int *ac,
		int *avc, int *acm, int *n, int *sc);

/* Executing Functions */
/* Functions related to executing the command */
int execute(local_t **local);
char *get_program(char *const *argv, char *const *environ);
char *handle_path(char *const *argv, char *const *environ);

#endif /* MAIN_H */
