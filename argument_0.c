#include "main.h"

/**
 * get_argv - parse the string with delim
 * @str: string to be parsed
 * @delim: string delimiter
 * @damn: damn
 *
 * Return: Parsed string on Success or NULL on Failure
 */
char **get_argv(char *const str, char *const delim, int damn)
{
	int avc = 0, ac = 0, n = 16, acm = 2;
	int checker;
	char **argv = NULL;

	if (str == NULL)
		return (NULL);

	argv = (char **) malloc(sizeof(char *) * acm);
	if (argv == NULL)
	{
		free_argv(argv);
		return (NULL);
	}
	argv[ac] = (char *) malloc(sizeof(char) * (n + 1));
	if (argv[ac] == NULL)
	{
		free_argv(argv);
		return (NULL);
	}

	checker = handle_argv(str, delim, &argv, &ac, &avc, &acm, &n, damn);
	if (checker == 1)
		return (NULL);

	return (argv);
}

/**
 * handle_argv - handles arguments
 * @str: string literal
 * @delim: string delimiter
 * @argv: array of arguments
 * @ac: argument count
 * @avc: argument vector count
 * @acm: argument number of bytes
 * @n: number of bytes
 * @damn: damn
 *
 * Return: 0 on Success or 1 on Failure
 */
int handle_argv(char *const str, char *const delim, char ***argv, int *ac,
		int *avc, int *acm, int *n, int damn)
{
	int sc = 0, check = 0;

	handle_special(str, &sc);
	for (; str[sc]; sc++)
	{
		if ((*avc) == *n)
		{
			*n *= 2;
			(*argv)[(*ac)] = (char *) realloc((*argv)[*ac], sizeof(char) * (*n + 1));
			if ((*argv)[(*ac)] == NULL)
				return (free_argv(*argv));
		}
		if (check == 0)
		{
			/*if (handle_comment(str, &(*argv), &(*ac), &(*avc), &sc))
				return (0);*/
			if (handle_delim(str, delim, &(*argv), &(*ac),
				&(*avc), &(*acm), &(*n), &sc))
				return (1);
			if (sc == -1)
				break;
		}
		if (str[sc] == '\'')
		{
			if (check == 1)
				check = 0;
			else
				check = 1;
			/* if (str[sc + 1] && damn == 1) */
				/* sc++; */
		}
		if (str[sc] == '\'' && damn)
			continue;
		(*argv)[(*ac)][(*avc)++] = str[sc];
	}
	(*argv)[(*ac)++][*avc] = '\0';
	(*argv)[*ac] = NULL;
	return (0);
}

/**
 * handle_delim - handles delimiter
 * @str: string literal
 * @delim: string delimiter
 * @argv: array of arguments
 * @ac: argument count
 * @avc: argument vector count
 * @acm: argument number of bytes
 * @n: number of bytes
 * @sc: string count
 *
 * Return: 0 on Success or 1 on Failure
 */
int handle_delim(char *const str, char *const delim, char ***argv, int *ac,
		int *avc, int *acm, int *n, int *sc)
{
	int dc;

	for (dc = 0; delim[dc]; (dc)++)
	{
		if (str[(*sc)] == delim[(dc)])
		{
			(*argv)[(*ac)][(*avc)] = '\0';
			(*sc)++;
			for (dc = 0; delim[dc]; dc++)
				while (str[*sc] == delim[dc])
					(*sc)++;
			if ((int) _strlen(str) == *sc)
			{
				*sc = -1;
				break;
			}
			(*ac)++;
			(*argv) = (char **) realloc(*argv, sizeof(char *) * (size_t) ++(*acm));
			if ((*argv) == NULL)
				return (free_argv(*argv));
			(*avc) = 0;
			*n = 16;
			(*argv)[(*ac)] = (char *) malloc(sizeof(char) * *n);
			if ((*argv)[(*ac)] == NULL)
				return (free_argv(*argv));
			break;
		}
	}
	return (0);
}

