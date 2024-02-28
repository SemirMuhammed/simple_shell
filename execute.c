#include "main.h"
#include <stdlib.h>

/**
 * execute - executes program
 * @local: local
 *
 * Return: 0 On Success or 1 on Error
 */
int execute(local_t **local)
{
	int status;
	char *program = NULL;
	pid_t process;

	if ((int) _strlen((*local)->argv[0]) > 255)
	{
		(*local)->signal = 20;
		return (error(&(*local)));
	}
	program = get_program((*local)->argv, (*local)->environ);
	if (program == NULL)
		return (error(&(*local)));
	process = fork();

	if (process == 0)
	{
		execve(program, (*local)->argv, (*local)->environ);
		exit(error(&(*local)));
	}
	else
		waitpid(process, &status, WCONTINUED);

	free(program);
	return (WEXITSTATUS(status));
}

/**
 * get_program - checks if file exist and is excutable
 * @argv: array of arguemnts
 * @environ: array of environment variables
 *
 * Return: 0 if exist or 1 else
 */
char *get_program(char *const *argv, char *const *environ)
{
	int i = 0;
	char *program = NULL;
	struct stat st;

	(void)environ;
	if (!argv || !(*argv))
		return (NULL);
	if (!(stat(argv[0], &st)))
	{
		get_mem(&program, _strlen(argv[0]) + 1);
		for (i = 0; argv[0][i]; i++)
			program[i] = argv[0][i];
		program[i] = '\0';
	}
	else
		program = handle_path(argv, environ);

	return (program);
}

/**
 * handle_path - gets path
 * @argv: array of arguments
 * @environ: array of environment variables
 *
 * Return: program
 */
char *handle_path(char *const *argv, char *const *environ)
{
	int i = 0, pc = 0, tc = 0;
	char *PATH = NULL, **path = NULL, *program = NULL;
	struct stat st;

	PATH = _getenv("PATH", environ);

	path = get_argv(PATH, ":", 0);
	free(PATH);
	while (path[i])
	{
		get_mem(&program, _strlen(path[i]) + _strlen(argv[0]) + 2);
		for (tc = 0; path[i][tc]; tc++)
			program[pc++] = path[i][tc];
		program[pc++] = '/';
		for (tc = 0; argv[0][tc]; tc++)
			program[pc++] = argv[0][tc];
		program[pc] = '\0';
		if (!(stat(program, &st)))
			break;
		pc = 0;
		i++;
		if (!path[i])
		{
			free(program);
			program = NULL;
		}
	}
	if (path)
		free_argv(path);

	return (program);
}

