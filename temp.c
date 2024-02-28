#include "main.h"

/**
 * handle_operator - handles && and || operater in prompt
 * @local: local
 * @prog: prog
 * @pc: pc
 * @exit_status: exit
 *
 * Return: 0
 */
int handle_operator(local_t **local, char **prog, int pc, int *exit_status)
{
	int ac, argc = 0, i;
	char **av = NULL;

	av = get_argv(prog[pc], " \t", 1);
	if (av == NULL)
		return (-1);
	for (ac = 0; av[ac]; ac++)
		continue;
	(*local)->argv = (char **) malloc(sizeof(char *) * (ac + 1));
	(*local)->exit_status = *exit_status;
	for (ac = 0; av[ac]; ac++)
	{
		/* i = handle_cls(&(*local), av, ac, argc, prog, &(*exit_status));
		if (i == 0)
			break;
		else if (i == 1)
			continue; */

		(*local)->argv[argc] = NULL;
		(*local)->argv[argc] = (char *) malloc(sizeof(char) * (_strlen(av[ac]) + 1));
		for (i = 0; av[ac][i]; i++)
			(*local)->argv[argc][i] = av[ac][i];
		(*local)->argv[argc++][i] = '\0';
	}
	if (!av[ac])
	{
		(*local)->argv[argc] = NULL;
		if (handle_builtin(&(*local), prog, av) != 0)
			*exit_status = execute(&(*local));
	}

	free_argv(av);
	if ((*local)->signal != 5)
		free_argv((*local)->argv);

	return (0);
}

/**
 * handle_cls - handles cls
 * @local: local
 * @av: av
 * @ac: ac
 * @argc: argc
 * @prog: prog
 * @exit_status: exit
 *
 * Return: NULL
 */
int handle_cls(local_t **local, char **av, int ac, int argc,
	       char **prog, int *exit_status)
{
	int vc;
	char *VAR = NULL;

	if (av[ac][0] == '|' && av[ac][1] == '|')
	{
		(*local)->argv[argc] = NULL;
		if (handle_builtin(&(*local), prog, av) != 0)
			*exit_status = execute(&(*local));
		argc = 0;
		if (!*exit_status)
			return (0);

	}
	else if (av[ac][0] == '&' && av[ac][1] == '&')
	{
		(*local)->argv[argc] = NULL;
		if (handle_builtin(&(*local), prog, av) != 0)
			*exit_status = execute(&(*local));
		argc = 0;
		if (*exit_status)
			return (0);
	}
	else if (av[ac][0] == '$' && av[ac][1] == '?')
		(*local)->argv[argc++] = itoa(*exit_status);
	else if (av[ac][0] == '$' && av[ac][1] == '$')
		(*local)->argv[argc++] = itoa((int) getpid());
	else if (av[ac][0] == '$' && av[ac][1])
	{
		get_mem(&VAR, _strlen(av[ac]));
		for (vc = 0; av[ac][vc + 1]; vc++)
			VAR[vc] = av[ac][vc + 1];
		VAR[vc] = '\0';
		(*local)->argv[argc++] = _getenv(VAR, (*local)->environ);
		free(VAR);
	}
	else
		return (2);
	return (1);
}

/**
 * _getalias - gets the value of given env
 * @name: env key
 * @alias: array of aliases
 *
 * Return: alias of given name
 */
char *_getalias(const char *name, char *const *alias)
{
	int ec, nc, vc = 0;
	char *value = NULL;

	if (!name)
		return (NULL);

	for (ec = 0; alias[ec]; ec++)
	{
		for (nc = 0; name[nc] && name[nc] == alias[ec][nc]; nc++)
			continue;
		if (nc == (int) _strlen((char *) name))
		{
			if (get_mem(&value, (_strlen(alias[ec]) + 1)) == 1)
				return (NULL);
			for (nc = 0; alias[ec][nc]; nc++)
				value[vc++] = alias[ec][nc];
			value[vc] = '\0';
			break;
		}
	}

	return (value);
}

