#include "main.h"

/**
 * handle_prompt - display prompt and gets cmd
 * @local: Data Stucture
 *
 * Return: argv
 */
int handle_prompt(local_t **local)
{
	static int exit_status = EXIT_SUCCESS;
	int i = 0;
	char **prog = NULL, *cmd = NULL;
	int cc = 0;

	cmd = get_cmd(&(*local), exit_status);
	if (*cmd == '\n')
	{
		free(cmd);
		if ((*local)->signal == 0)
			free(*local);
		return (2);
	}
	cc = handle_cmd_error(&(*local), &cmd, &exit_status);
	if (cc != 1)
		return (cc);

	prog = get_argv(cmd, "\n;", 0);
	if (prog == NULL)
		return (-1);
	free(cmd);
	while (prog[i])
	{
		handle_operator(&(*local), prog, i, &exit_status);
		i++;
	}
	free_argv(prog);
	if ((*local)->signal == 0 || (*local)->signal == 20)
		free(*local);

	return (0);
}

/**
 * handle_cmd_error - handles command errors
 * @local: Data Structure
 * @cmd: command
 * @exit_status: exit status of previous command
 *
 * Return: 0 on Success, 1 no error or -1 Failure
 */
int handle_cmd_error(local_t **local, char *const *cmd, int *exit_status)
{
	int cc;

	(*local)->exit_status = (*exit_status);
	if ((*cmd) == NULL || !(**cmd))
	{
		if (!(**cmd))
			free((*cmd));
		return (-1);
	}
	if ((*cmd)[0] == ';')
	{
		(*local)->error_checker = 5;
		goto error;
	}
	for (cc = 0; (*cmd)[cc]; cc++)
	{
		if (!(*cmd)[cc + 1])
			break;
		if ((*cmd)[cc] == ';')
		{
			if ((*cmd)[cc + 1] && (*cmd)[cc + 1] == ';')
			{
				(*local)->error_checker = 6;
				goto error;
			}
		}
	}

	return (1);
error:
	free((*cmd));
	*exit_status = error(&(*local));
	if ((*local)->ac == 2)
	{
		(*local)->exit_status = 2;
		return (-1);
	}
	if ((*local)->signal == 0)
		free(*local);
	return (0);
}

/**
 * get_cmd - Display prompt and get command
 * @local: Data Structure
 * @exit_status: The previous program exit status
 *
 * Return: NULL Terminated Command
 */
char *get_cmd(local_t **local, int exit_status)
{
	char *cmd = NULL;
	size_t cm = 0;
	ssize_t cc = 0;

	/* Check for Interactive or Non-Interactive Mode */
	if ((*local)->active)
		write(STDOUT_FILENO, &(*local)->prompt[0], _strlen((*local)->prompt));

	cc = _getline(&cmd, &cm, (*local)->fd);

	if (cc == -1)
	{
		free(cmd);
		return (NULL);
	}
	/* Check if CTRL_D (EOF) is only captured */
	if (cc == -2)
	{
		free(cmd);
		if ((*local)->active)
			write(STDOUT_FILENO, "\n", 1);
		handle_alias(&(*local), 1);
		if ((*local)->signal == 0)
			free(*local);
		if (errno == 130)
			exit(130);
		else if (errno == 0)
			exit(0);
		exit(exit_status);
	}

	return (cmd);
}

/**
 * _getline - read line from given file stream
 * @line: buffer of read line
 * @n: number of bytes allocated for line
 * @fd: file discriptor
 *
 * Return: number of char read or -1 on Failure
 */
ssize_t _getline(char **line, size_t *n, int const fd)
{
	ssize_t rc;
	size_t lc = 0;

	if (*line == NULL)
	{
		*n = 1024;
		if (get_mem(&(*line), *n) == 1)
			return (-1);
	}

	while (1)
	{
		rc = read(fd, &(*line)[lc], *n - lc);
		if (rc == -1)
			return (-1);
		if (rc == 0)
		{
			if (lc == 0)
				return (-2);
			lc++;
			break;
		}
		lc += rc;
		if ((*line)[lc - 1] != '\n')
		{
			*n += 1024;
			if (get_mem(&(*line), *n) == 1)
				return (-1);
		}
		else
			break;
	}

	if (lc - 1 != 0)
		(*line)[lc - 1] = '\0';
	if (get_mem(&(*line), lc--) == 1)
		return (-1);

	return (lc);
}

