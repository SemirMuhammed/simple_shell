#include "main.h"
#include <unistd.h>

/**
 * handle_builtin - handles all the built-in functions
 * @local: Data Stucture
 * @prog: array of programs
 * @av: av
 *
 * Return: 0 if nuthi
 */
int handle_builtin(local_t **local, char **prog, char **av)
{
	if (handle_alias(local, 0) == 0)
		return (0);
	if (handle_exit(local, prog, av, (*local)->exit_status) == 0)
		return (0);
	if (handle_env(local) == 0)
		return (0);
	if (handle_setenv(local) == 0)
		return (0);
	if (handle_unsetenv(local) == 0)
		return (0);
	if (handle_cd(local) == 0)
		return (0);

	return (1);
}

/**
 * handle_exit - handles exit builtin
 * @local: Data Stucture
 * @prog: array of programs
 * @av: av
 * @exit_status: exit
 *
 * Return: 0 if nuthi
 */
int handle_exit(local_t **local, char **prog, char **av, int exit_status)
{
	int i, argc = 0, status = exit_status;
	char *exit_cmd = "exit";

	while ((*local)->argv[argc] != NULL)
		argc++;

	for (i = 0; exit_cmd[i]; i++)
		if (exit_cmd[i] != (*local)->argv[0][i])
			return (1);
	if (exit_cmd[i] != (*local)->argv[0][i])
		return (1);
	if (argc == 2)
	{
		status = atoi((*local)->argv[1]);
		if ((status == 0 && (*local)->argv[1][0] != '0') || status < 0)
		{
			(*local)->error_checker = 1;
			error(&(*local));
			return (0);
		}
	}

	handle_alias(&(*local), 1);
	free_argv((*local)->argv);
	free_argv(av);
	free_argv(prog);
	free(*local);

	if (errno == 130 && argc == 1)
		exit(130);
	exit(status);
}

/**
 * handle_env - handles env builtin
 * @local: Data Stucture
 *
 * Return: 0 if nuthi
 */
int handle_env(local_t **local)
{
	int i;
	char *env_cmd = "env";

	for (i = 0; env_cmd[i]; i++)
	{
		if (env_cmd[i] != (*local)->argv[0][i])
			return (1);
	}
	if (env_cmd[i] != (*local)->argv[0][i])
		return (1);

	if ((*local)->environ == NULL)
		return (0);
	for (i = 0; ((*local)->environ)[i]; i++)
	{
		write(STDOUT_FILENO, &(*local)->environ[i][0],
			_strlen((*local)->environ[i]));
		write(STDOUT_FILENO, "\n", 1);
	}
	return (0);
}

/**
 * handle_setenv - handles setenv builtin
 * @local: Data Stucture
 *
 * Return: 0 if nuthi
 */
int handle_setenv(local_t **local)
{
	int i;
	char *setenv_cmd = "setenv";

	for (i = 0; setenv_cmd[i]; i++)
		if (setenv_cmd[i] != (*local)->argv[0][i])
			return (1);
	if (setenv_cmd[i] != (*local)->argv[0][i])
		return (1);

	if ((*local)->environ == NULL)
		return (0);
	for (i = 0; (*local)->argv[i]; i++)
		continue;
	if (i != 3)
	{
		(*local)->error_checker = 2;
		error(&(*local));
		return (0);
	}
	_setenv(&(*local));

	return (0);
}

/**
 * handle_unsetenv - handles unsetenv builtin
 * @local: Data Stucture
 *
 * Return: 0 if nuthi
 */
int handle_unsetenv(local_t **local)
{
	int i;
	char *setenv_cmd = "unsetenv";

	for (i = 0; setenv_cmd[i]; i++)
		if (setenv_cmd[i] != (*local)->argv[0][i])
			return (1);
	if (setenv_cmd[i] != (*local)->argv[0][i])
		return (1);

	if ((*local)->environ == NULL)
		return (0);
	for (i = 0; (*local)->argv[i]; i++)
		continue;
	if (i != 2)
	{
		(*local)->error_checker = 3;
		error(&(*local));
		return (0);
	}
	_unsetenv(&(*local));

	return (0);
}

