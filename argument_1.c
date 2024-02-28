#include "main.h"

/**
 * handle_comment - handles comments
 * @str: string literal
 * @argv: array of arguments
 * @ac: argument count
 * @avc: argument vector count
 * @sc: string count
 *
 * Return: 0 on Success or 1 on Failure
 */

int handle_comment(char *const str, char ***argv, int *ac, int *avc, int *sc)
{
	int dc;
	char *comment = "#";

	for (dc = 0; (comment)[dc]; dc++)
	{
		if (str[*sc] == (comment)[dc])
		{
			(*argv)[(*ac)++][*avc] = '\0';
			(*argv)[*ac] = NULL;
			return (1);
		}
	}

	return (0);
}

/**
 * handle_special - handles special cases
 * @str: string literal
 * @sc: string count
 *
 * Return: void
 */
void handle_special(char *const str, int *sc)
{
	int dc;
	char *special = " \t";

	for (dc = 0; (special)[dc]; dc++)
		while (str[*sc] == (special)[dc])
			(*sc)++;
}

/**
 * free_argv - frees argument vector
 * @argv: array of arguments
 *
 * Return: Void
 */
int free_argv(char **argv)
{
	int argc = 0;

	while (argv[argc])
	{
		free(argv[argc]);
		argv[argc] = NULL;
		argc++;
	}

	free(argv);
	argv = NULL;
	return (1);
}

