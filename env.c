#include "main.h"

/**
 * _getenv - gets the value of given env
 * @variable: env key
 * @environ: array of environment variable
 *
 * Return: Value of env key
 */
char *_getenv(const char *variable, char *const *environ)
{
	int ec, nc, vc = 0;
	char *value = NULL;

	if (!variable)
		return (NULL);

	for (ec = 0; environ[ec]; ec++)
	{
		for (nc = 0; variable[nc] && variable[nc] == environ[ec][nc]; nc++)
			continue;
		if (nc == (int) _strlen((char *) variable))
		{
			if (get_mem(&value, (_strlen(environ[ec]) - nc)) == 1)
				return (NULL);
			for (nc++; environ[ec][nc]; nc++)
				value[vc++] = environ[ec][nc];
			value[vc] = '\0';
			break;
		}
	}

	return (value);
}

/**
 * _setenv - sets env
 * @local: data structure
 *
 * Return: 0
 */
int _setenv(local_t **local)
{
	int ec, nc, vc, ecc = 0;

	for (ec = 0; (*local)->environ[ec]; ec++)
	{
		for (nc = 0; (*local)->argv[1][nc] &&
			(*local)->argv[1][nc] == (*local)->environ[ec][nc]; nc++)
			continue;
		if (nc == (int) _strlen((*local)->argv[1]))
		{
			if (1)
			{
				nc++;
				for (vc = 0; (*local)->argv[2][vc]; vc++)
					(*local)->environ[ec][nc++] = (*local)->argv[2][vc];
				(*local)->environ[ec][nc] = '\0';

			}
			return (0);
		}
	}

	(*local)->environ[ec] = (char *) malloc(sizeof(char) * 1024);
	for (nc = 0; (*local)->argv[1][nc]; nc++)
		(*local)->environ[ec][ecc++] = (*local)->argv[1][nc];
	(*local)->environ[ec][ecc++] = '=';
	for (vc = 0; (*local)->argv[2][vc]; vc++)
		(*local)->environ[ec][ecc++] = (*local)->argv[2][vc];
	(*local)->environ[ec++][ecc] = '\0';
	(*local)->environ[ec] = NULL;

	return (0);
}

/**
 * _unsetenv - sets env
 * @local: data structure
 *
 * Return: 0
 */
int _unsetenv(local_t **local)
{
	int ec, nc, check;

	for (ec = 0; (*local)->environ[ec]; ec++)
	{
		for (nc = 0; (*local)->argv[1][nc] &&
			(*local)->argv[1][nc] == (*local)->environ[ec][nc]; nc++)
			continue;
		if (nc == (int) _strlen((*local)->argv[1]))
			check = 1;

		if (check == 1)
		{
			if ((*local)->environ[ec + 1] == NULL)
				break;
			(*local)->environ[ec] = (*local)->environ[ec + 1];
		}
	}
	(*local)->environ[ec] = NULL;
	return (0);
}

/**
 * cd_env - sets env according to cd
 * @local: data structure
 * @oldpwd: pwd before cd call
 *
 * Return: 0
 */
int cd_env(local_t **local, char *const oldpwd)
{
	int ec, nc, vc;
	char *pwd = "PWD", *old = "OLDPWD";
	char *cwd;

	cwd = getcwd(NULL, 0);
	for (ec = 0; (*local)->environ[ec]; ec++)
	{
		for (nc = 0; pwd[nc] && pwd[nc] == (*local)->environ[ec][nc]; nc++)
			continue;
		if (nc == (int) _strlen(pwd))
		{
			nc++;
			for (vc = 0; cwd[vc]; vc++)
				(*local)->environ[ec][nc++] = cwd[vc];
			(*local)->environ[ec][nc] = '\0';
		}
	}

	for (ec = 0; (*local)->environ[ec]; ec++)
	{
		for (nc = 0; old[nc] && old[nc] == (*local)->environ[ec][nc]; nc++)
			continue;
		if (nc == (int) _strlen(old))
		{
			nc++;
			for (vc = 0; oldpwd[vc]; vc++)
				(*local)->environ[ec][nc++] = oldpwd[vc];
			(*local)->environ[ec][nc] = '\0';
		}
	}
	free(oldpwd);
	free(cwd);

	return (0);
}
