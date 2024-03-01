#include "main.h"

/**
 * handle_cd - handles cd builtin
 * @local: Data Stucture
 *
 * Return: 0 if nuthi
 */
int handle_cd(local_t **local)
{
	int check;
	int i;
	char *cd_cmd = "cd\0", *oldpwd = NULL;
	char *path = NULL, *old = "-";

	for (i = 0; cd_cmd[i]; i++)
		if (cd_cmd[i] != (*local)->argv[0][i])
			return (1);
	if (cd_cmd[i] != (*local)->argv[0][i])
		return (1);
	for (i = 0; (*local)->argv[i]; i++)
		continue;
	if (i == 1)
	{
		path = _getenv("HOME", (*local)->environ);
		if (path == NULL)
			path = getcwd(NULL, 0);
	}
	else if ((*local)->argv[1][0] == old[0] && ((*local)->argv[1][1] == '\0'))
	{
		path = _getenv("OLDPWD", (*local)->environ);
		if (path == NULL)
			path = getcwd(NULL, 0);
		write(STDOUT_FILENO, &path[0], _strlen(path));
		write(STDOUT_FILENO, "\n", 1);
	}
	oldpwd = getcwd(NULL, 0);
	if (path)
		check = chdir(path);
	else
		check = chdir((*local)->argv[1]);
	if (check == -1)
	{
		(*local)->error_checker = 4;
		error(&(*local));
		return (0);
	}

	cd_env(&(*local), oldpwd);
	free(path);

	return (0);
}

/**
 * handle_alias - handles alias built-in
 * @local: Data Stucture
 * @exit: exit
 *
 * Return: 0 if nuthi
 */
int handle_alias(local_t **local, int const exit)
{
	int i, argc = 0, ec = 0;
	char **argv = (*local)->argv;
	static char **alias = NULL;
	int ac = 0;

	(void)ec;
	(void)argc;
	(void)i;
	errno = 0;
	if (exit)
		goto free;
	if (check_alias(&alias, argv))
		return (1);
	alias = (char **) malloc(sizeof(char *) * ((size_t) 2));
	alias[0] = NULL;
	for (argc = 1; argv[argc]; argc++)
	{
		for (i = 0; argv[argc][i]; i++)
		{
			if (argv[argc][i] == '=')
			{
				if (set_alias(&alias, argv, argc, ec))
					ec++;
				if (!alias[ec])
					ac++;
			}
		}
		if (argv[argc][i])
			continue;
		print_alias(alias, argv, argc);
	}
	alias = (char **) realloc(alias, sizeof(char *) * ((size_t) ac + 2));
	return (0);
free:
	if (alias)
		free_argv(alias);
	return (0);
}

/**
 * set_alias - set
 * @alias: alias
 * @argv: argv
 * @argc: argc
 * @ec: ec
 *
 * Return: 0
 */
int set_alias(char ***alias, char **argv, int argc, int ec)
{
	int avc, acc = 0, nc;

	if (*alias[0] != NULL)
	{
		for (ec = 0; *alias && *alias[ec]; ec++)
		{
			for (nc = 0; argv[argc][nc] && argv[argc][nc] ==
				*alias[ec][nc] && *alias[ec][nc] != '='; nc++)
				continue;
			if (*alias[ec][nc] == '=')
			{
				free(*alias[ec]);
				break;
			}
		}
	}

	*alias[ec] = NULL;
	*alias[ec] = (char *) malloc(sizeof(char) * (_strlen((argv[argc]) + 3)));
	for (avc = 0; argv[argc][avc]; avc++)
	{
		*alias[ec][acc++] = argv[argc][avc];
		if (argv[argc][avc] == '=')
			*alias[ec][acc++] = '\'';
	}
	*alias[ec][acc++] = '\'';
	*alias[ec++][acc] = '\0';
	*alias[ec] = NULL;

	return (1);

}

/**
 * print_alias - check
 * @alias: alias
 * @argv: argv
 * @argc: argc
 *
 * Return: 0
 */
int print_alias(char **alias, char **argv, int argc)
{
	int i;
	char *temp = NULL;

	if (!alias || !*alias)
		return (0);
	if (argc)
	{
		temp = _getalias(argv[argc], alias);
		if (temp)
		{
			write(STDOUT_FILENO, &temp[0], _strlen(temp));
			write(STDOUT_FILENO, "\n", 1);
		}
		free(temp);
		temp = NULL;
	}
	else
	{
		for (i = 0; alias[i]; i++)
		{
			write(STDOUT_FILENO, &alias[i][0], _strlen(alias[i]));
			write(STDOUT_FILENO, "\n", 1);
		}
		return (0);
	}
	return (1);
}

/**
 * check_alias - check
 * @alias: alias
 * @argv: argv
 *
 * Return: 0
 */
int check_alias(char ***alias, char **argv)
{
	int i;
	char *alias_cmd = "alias";

	for (i = 0; alias_cmd[i]; i++)
		if (alias_cmd[i] != argv[0][i])
			return (1);
	if (alias_cmd[i] != argv[0][i])
		return (1);

	if (argv[1] == NULL)
		print_alias(*alias, argv, 0);

	return (0);
}

